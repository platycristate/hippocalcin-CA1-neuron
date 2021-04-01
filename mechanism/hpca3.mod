NEURON {
	SUFFIX hpca3
	USEION ca READ cao, ica, cai  WRITE cai, ica
	USEION k READ ek WRITE ik
	RANGE HPCA_m_z, ca, ca1, ca2, ca3, ca_avg, ica_pmp, gbar, ik
	GLOBAL Volume,Ra, cai0,  Rb, caix,q10, temp, tadj, vmin, vmax
	THREADSAFE
}

DEFINE N 4 : no. of shells 

UNITS {
	(molar) = (1/liter)
	(mol) = (1)
	(mM) = (millimolar)
	(um) = (micron)
	(mA) = (milliamp)
	FARADAY = (faraday) (10000 coulomb)
	PI = (pi) (1)
	(pS) = (picosiemens)
}

PARAMETER {
	DCa = 0.22 (um2/ms) Dhpca = 0.05(um2/ms)
	Dcahpca = 0.05 (um2/ms)
	Dca2hpca = 0.05 (um2/ms) Dhpca_m = 0.001 (um2/ms)
	k1HPCA = 40 (/mM-ms)
	k2HPCA = 0.01 (/ms)
	k3HPCA = 40 (/mM-ms)
	k4HPCA = 0.01 (/ms)
	k7HPCA = 0.01 (/mM-ms) : insertion to the membrane
	k8HPCA = 0.002 (/ms) : uninsertion from the membrane
	TotalHPCA = 0.03821 (mM)
	
	D_Bufer = 0.05 (um2/ms)
	Bufer0 = 20 (mM) : initial concentration of the buffer
	k1bufer = 10 (/mM-ms)
	k2bufer = 1 (/ms)
	
	k1Pump = 1 (/mM-ms)
	k2Pump = 0.0003 (/ms)
	TotalPump = 1e-11 (mol/cm2)
	cai0 = 100e-6 (mM) : initial [Ca2+]_i, 110 * 10^(-6) mM = 110 nM.
    tau_d = 200 (ms)
	delta = 0.1 (um)
	
	gbar = 600   	(pS/um2) : where does this come from? = 60 mS / cm2 = 0.06 S/cm2
	caix = 1
	Ra   = 0.01	(/ms)
	Rb   = 0.02	(/ms)
	temp = 36	(degC)
	q10  = 2.3        : temperature adjustment parameter
	vmin = -120	(mV)
	vmax = 100	(mV)
}

ASSIGNED {
	diam	(um)
	ica		(mA/cm2)
	cai		(mM)
    ca1 (mM)
    ca2 (mM)
    ca3 (mM)
    ca_avg (mM)
	Volume[N] (um2)
	B0      (mM)
	HP0   (mM)
	cao (mM)
	ica_pmp (mA/cm2)
    ica_pmp_last (mA/cm2) 
	parea (um)
	a		(/ms)
	b		(/ms)
	ik 		(mA/cm2)
	gk		(pS/um2)
	ek		(mV)
	ninf
	ntau 		(ms)	
	tadj
}

CONSTANT { volo = 1e10 (um2) }

STATE {
	ca [N]			(mM)	 <1e-6>
	HPCA [N] 		(mM)
	CaHPCA [N] 		(mM)
	Ca2HPCA[N] 		(mM)
	HPCA_m         (mol/cm2)
	
	pump (mol/cm2)          <1e-16>
	pumpca (mol/cm2)        <1e-16>
	n
	
	HPCA_z (mM)
	CaHPCA_z (mM)
	Ca2HPCA_z (mM)
	HPCA_m_z (mM)
	HPCA_tot_z (mM)
	
	Bufer[N] (mM)
	CaBufer[N] (mM)
}
LOCAL factors_done, nexp

INITIAL {
	MUTEXLOCK
	if (factors_done == 0) {
		factors_done = 1
		factors()
	}
	MUTEXUNLOCK
	cai = cai0
	B0 =  Bufer0/(1 + (cai*k1bufer/k2bufer))
	FROM i=0 TO N-1 {
		ca[i] = cai
        ca1 = cai
        ca2 = cai
        ca3 = cai
		HPCA[i] = TotalHPCA
		Bufer[i] = B0
		CaBufer[i] = Bufer0 - B0
	}
	parea = PI*diam
	pump = TotalPump/(1 + (cai*k1Pump/k2Pump))
	pumpca = TotalPump - pump
    ica_pmp_last = 0
	rates()
	n = ninf
}
BREAKPOINT { 
	SOLVE scheme METHOD sparse
    ica_pmp_last = ica_pmp
	ica = ica_pmp
	SOLVE states METHOD cnexp
	gk = tadj*gbar*n
	ik = (1e-4) * gk * (v - ek) : (1e-4) converts pS/um2 to S/cm2
}


DERIVATIVE states {
	cai = ca[0]
    ca1 = ca[1]
    ca2 = ca[2]
    ca3 = ca[3]

	rates()
	n' =  (ninf-n)/ntau
}

LOCAL dsq, dsqvol
LOCAL frat[N] : scales the rate constants for model geometry

KINETIC scheme {
	dsq = diam*diam
    : multiplies right hand-sides of diff. equations by the volume
	COMPARTMENT (1e10)*parea {pump pumpca HPCA_m}
	COMPARTMENT volo {cao}
	COMPARTMENT i, dsq*Volume[i] {ca HPCA CaHPCA Ca2HPCA Bufer CaBufer}
    
    : diffusion between segments
	LONGITUDINAL_DIFFUSION i, DCa*dsq*Volume[i] {ca}
	LONGITUDINAL_DIFFUSION i, Dhpca*dsq*Volume[i] {HPCA}
	LONGITUDINAL_DIFFUSION i, Dcahpca*dsq*Volume[i] {CaHPCA}
	LONGITUDINAL_DIFFUSION i, Dca2hpca*dsq*Volume[i] {Ca2HPCA}
	LONGITUDINAL_DIFFUSION  Dhpca_m*parea*(1e10) {HPCA_m}
	LONGITUDINAL_DIFFUSION i, D_Bufer*dsq*Volume[i] {Bufer}
	
	: kinetic equations for the Ca2+-ATPase
	~ ca[0] + pump <-> pumpca (k1Pump*parea*(1e10), k2Pump*parea*(1e10))
	~ pumpca <-> pump + cao (k1Pump*parea*(1e10), k2Pump*parea*(1e10))
	CONSERVE pump + pumpca = TotalPump * parea * (1e10)
	ica_pmp = 2*FARADAY*(f_flux - b_flux)/parea
    : ica_pmp is the "new" value, but cashell must be 
    : computed using the "old" value, i.e. ica_pmp_last
	: all currents except pump
	~ ca[0] << (-(ica - ica_pmp_last)*PI*diam/(2*FARADAY))
	
	FROM i=0 TO N-2 {
		~ ca[i] <-> ca[i+1] (DCa*frat[i+1], DCa*frat[i+1])
		~ HPCA[i] <-> HPCA[i+1] (Dhpca*frat[i+1], Dhpca*frat[i+1])
		~ CaHPCA[i] <-> CaHPCA[i+1] (Dcahpca*frat[i+1], Dcahpca*frat[i+1])
		~ Ca2HPCA[i] <-> Ca2HPCA[i+1] (Dca2hpca*frat[i+1], Dca2hpca*frat[i+1])
		~ Bufer[i] <-> Bufer[i+1] (D_Bufer*frat[i+1], D_Bufer*frat[i+1])
	}
	FROM i=0 TO N-1 {
		dsqvol = dsq*Volume[i]
		~ ca[i] + HPCA[i] <-> CaHPCA[i] (k1HPCA*dsqvol, k2HPCA*dsqvol)
		~ ca[i] + CaHPCA[i] <-> Ca2HPCA[i] (k3HPCA*dsqvol, k4HPCA*dsqvol)
		~ ca[i] + Bufer[i] <-> CaBufer[i] (k1bufer*dsqvol, k2bufer*dsqvol)
	}
	~ Ca2HPCA[0] <-> HPCA_m (k7HPCA*dsq*Volume[0], k8HPCA*parea*(1e10)) 
    : Absolute amounts of substances (moles)	

	HPCA_z = dsq*(HPCA[0]*Volume[0]+HPCA[1]*Volume[1] + HPCA[2]*Volume[2] + HPCA[3]*Volume[3])
	
	CaHPCA_z = dsq*(CaHPCA[0]*Volume[0] + CaHPCA[1]*Volume[1] + CaHPCA[2]*Volume[2] + CaHPCA[3]*Volume[3])
	
	Ca2HPCA_z = dsq*(Ca2HPCA[0]*Volume[0] + Ca2HPCA[1]*Volume[1] + Ca2HPCA[2]*Volume[2] + Ca2HPCA[3]*Volume[3])
	HPCA_m_z = HPCA_m*parea*(1e10)
	HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z
}

PROCEDURE rates() {  
	a = Ra * HPCA_m
	b = Rb
	tadj = q10^((celsius - temp)/10)
	ntau = 1/tadj/(a+b)
	ninf = a/(a+b)
}


PROCEDURE factors() {
	LOCAL r, dr2
	r = 1/2
	dr2 = r/(N-1)/2
	Volume[0] = 0 frat[0] = 2*r FROM i=0 TO N-2 {
		Volume[i] = Volume[i] + PI*(r-dr2/2)*2*dr2
		r = r - dr2
		frat[i+1] = 2*PI*r/(2*dr2)
		r = r - dr2
		Volume[i+1] = PI*(r+dr2/2)*2*dr2
	}
}
