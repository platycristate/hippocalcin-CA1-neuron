INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}

NEURON {
	SUFFIX hpca2 
    USEION ca READ ica, cai WRITE cai	
    RANGE ca, HPCA_m_z, gbar, ik 
    GLOBAL depth,cainf,taur, Volume, Ra, Rb, q10, tadj, vmin, vmax
	THREADSAFE
}

DEFINE N 4

UNITS {
	(molar) = (1/liter)			: moles do not appear in units
	(mM)	= (millimolar)
	(um)	= (micron)
	(mA)	= (milliamp)
	(msM)	= (ms mM)
	FARADAY = (faraday) (coulomb)
	PI = (pi) (1)
	(pS) = (picosiemens)

}
LOCAL factors_done

PARAMETER {
    DCa  = 0.22 (um2/ms)
	Dhpca = 0.05(um2/ms)
	Dcahpca = 0.05 (um2/ms)
	Dca2hpca = 0.05 (um2/ms)
	Dhpca_m = 0.001 (um2/ms)
	k1HPCA = 40 (/mM-ms)
	k2HPCA = 0.01 (/ms)
	k3HPCA = 40 (/mM-ms)
	k4HPCA = 0.01 (/ms)
	k7HPCA = 0.01 (/mM-ms) : insertion to the membrane
	k8HPCA = 0.002 (/ms) : uninsertion from the membrane
	TotalHPCA = 0.03821 (mM)

	depth	= .1	(um)		: depth of shell
	taur	= 200	(ms)		: rate of calcium removal
	cainf	= 100e-6(mM)
	cai		(mM)
	
	gbar = 600  (pS/um2) 
	Ra   = 0.01	(/ms) 
	Rb   = 0.02	(/ms)
	temp = 36	(degC)
	q10  = 2.3        
	vmin = -120	(mV)
	vmax = 100	(mV)

}

STATE {
	ca	            (mM)   
	HPCA [N] 		(mM)
	CaHPCA [N] 		(mM)
	Ca2HPCA[N] 		(mM)
	HPCA_m          (mol/cm2)
	n
	HPCA_z (mM)
	CaHPCA_z (mM)
	Ca2HPCA_z (mM)
	HPCA_m_z (mM)
	HPCA_tot_z (mM)

}
INITIAL {
    cai = cainf
	MUTEXLOCK
	if (factors_done == 0) {
		factors_done = 1
		factors()
	}
	MUTEXUNLOCK
	HP0 = TotalHPCA/(1 + (cai*k1HPCA/k2HPCA))
	FROM i=0 TO N-1 {
		HPCA[i] = HP0
		CaHPCA[i] = TotalHPCA - HP0
	}
	parea = PI*diam
	rates()
	n = ninf
}


ASSIGNED {
	ica		(mA/cm2)
	drive_channel	(mM/ms)
	Volume[N] (um2)
    B0        (mM)
    HP0       (mM)
	a		(/ms)
	b		(/ms)
	ik 		(mA/cm2)
	gk		(pS/um2)
    parea   (um)
	ek		(mV)
	ninf
	ntau 		(ms)	
	tadj

}
	
BREAKPOINT {
	SOLVE state METHOD sparse
	SOLVE states METHOD derivimplicit
	gk = tadj*gbar*n
	ik = (1e-4) * gk * (v - ek) : (1e-4) converts pS/um2 to S/cm2

}

DERIVATIVE states { 
	drive_channel = - (10000) * ica / (2 * FARADAY * depth)
	if (drive_channel <= 0.) { drive_channel = 0.  }   : cannot pump inward 

    ca' = drive_channel/18 + (cainf - ca)/taur
	cai = ca
	rates()
	n' =  (ninf-n)/ntau

}
LOCAL frat[N]

PROCEDURE factors() {
	LOCAL r, dr2
	r = 1/2
	dr2 = r/(N-1)/2
	Volume[0] = 0
	frat[0] = 2*r
	FROM i=0 TO N-2 {
		Volume[i] = Volume[i] + PI*(r-dr2/2)*2*dr2
		r = r - dr2
		frat[i+1] = 2*PI*r/(2*dr2)
		r = r - dr2
		Volume[i+1] = PI*(r+dr2/2)*2*dr2
	}
}


PROCEDURE rates() {  
	a = Ra * HPCA_m
	b = Rb
	tadj = q10^((celsius - temp)/10)
	ntau = 1/tadj/(a+b)
	ninf = a/(a+b)
}

LOCAL dsq, dsqvol

KINETIC state {
    dsq = diam*diam
	COMPARTMENT i, dsq*Volume[i] {HPCA CaHPCA Ca2HPCA HPCA_m ca}

	LONGITUDINAL_DIFFUSION i, Dhpca*dsq*Volume[i] {HPCA}
	LONGITUDINAL_DIFFUSION i, Dcahpca*dsq*Volume[i] {CaHPCA}
	LONGITUDINAL_DIFFUSION i, Dca2hpca*dsq*Volume[i] {Ca2HPCA}
	LONGITUDINAL_DIFFUSION  Dhpca_m*parea*(1e10) {HPCA_m}
	
	FROM i=0 TO N-2 {
		~ HPCA[i] <-> HPCA[i+1] (Dhpca*frat[i+1], Dhpca*frat[i+1])
		~ CaHPCA[i] <-> CaHPCA[i+1] (Dcahpca*frat[i+1], Dcahpca*frat[i+1])
		~ Ca2HPCA[i] <-> Ca2HPCA[i+1] (Dca2hpca*frat[i+1], Dca2hpca*frat[i+1])
		
	}

	FROM i=0 TO N-1 {
		dsqvol = dsq*Volume[i]
		~ ca + HPCA[i] <-> CaHPCA[i] (k1HPCA*dsqvol, k2HPCA*dsqvol)
		~ ca + CaHPCA[i] <-> Ca2HPCA[i] (k3HPCA*dsqvol, k4HPCA*dsqvol)
	}
	
	~ Ca2HPCA[0] <-> HPCA_m (k7HPCA*dsq*Volume[0], k8HPCA*parea*(1e10)) 
    : Absolute amounts of substances (moles)	

	HPCA_z = dsq*(HPCA[0]*Volume[0]+HPCA[1]*Volume[1] + HPCA[2]*Volume[2] + HPCA[3]*Volume[3])
	
	CaHPCA_z = dsq*(CaHPCA[0]*Volume[0] + CaHPCA[1]*Volume[1] + CaHPCA[2]*Volume[2] + CaHPCA[3]*Volume[3])
	
	Ca2HPCA_z = dsq*(Ca2HPCA[0]*Volume[0] + Ca2HPCA[1]*Volume[1] + Ca2HPCA[2]*Volume[2] + Ca2HPCA[3]*Volume[3])
	HPCA_m_z = HPCA_m*parea*(1e10)
	HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z

}
