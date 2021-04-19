NEURON {
	SUFFIX hpca2
	USEION ca READ cao, ica, cai  WRITE cai, ica
	USEION k READ ek WRITE ik
	RANGE HPCA_m_z, ca, ica_pmp, ica_basal, gbar, ik
	GLOBAL Ra, cai0,  Rb, q10, temp, tadj
	THREADSAFE
}

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
	k1HPCA = 15 (/mM-ms)
	k2HPCA = 0.01 (/ms) : 0.01
	k3HPCA = 16.67 (/mM-ms)
	k4HPCA = 0.01 (/ms) : 0.01
	k_out = 0.002 (/ms) : uninsertion from the membrane
	TotalHPCA = 0.03821 (mM)

	D = 40 (um2/s)
	
	Bufer0 = 0.180 (mM) : initial concentration of the buffer
	k1bufer = 142 (/mM-ms)
	k2bufer = 0.1 (/ms)
	
	k1Pump = 1 (/mM-ms)
	k2Pump = 0.0003 (/ms)
	k3Pump = 1 (/ms)
	k4Pump = 0.0003 (/mM-ms)
	TotalPump = 3.33e-12 (mol/cm2)
	cai0 = 50e-6 (mM) : initial [Ca2+]_i, 110 * 10^(-6) mM = 110 nM.
	delta = 0.1 (um)
	C = 1	    (1) :tranfer coefficient for HPCAm to current
	
	gbar = 600   	(pS/um2) : where does this come from? = 60 mS / cm2 = 0.06 S/cm2
	Ra   = 0.01	(cm2/mol-ms)
	Rb   = 0.02	(/ms)
	temp = 36	(degC)
	q10  = 2.3        : temperature adjustment parameter
}

ASSIGNED {
    diam	    (um)
    ica		    (mA/cm2)
    drive_channels  (mM/ms)
    cai		    (mM)
    Vol		    (um2)
    k_ins           (/ms) : insertion of the HPCA to the membrane
    ica_balance	    (mA/cm2)
    B0		    (mM)
    HP0		    (mM)
    cao		    (mM)
    ica_pmp	    (mA/cm2)
    ica_basal	    (mA/cm2)
    ica_pmp_last    (mA/cm2) 
    parea (um)
    a		    (/ms)
    b		    (/ms)
    ik		    (mA/cm2) 
    gk		    (pS/um2) 
    ek		    (mV)
    ninf
    ntau 	    (ms)	
    tadj
}

CONSTANT { volo = 1e10 (um2) }

STATE {
	ca 		(mM)	    <1e-6>
	HPCA  		(mM)
	CaHPCA  	(mM)
	Ca2HPCA 	(mM)
	HPCA_m		(mol/cm2)   <1e-16>
	HPCA_z          (mM)
    	CaHPCA_z        (mM)
    	Ca2HPCA_z       (mM)
    	HPCA_m_z        (mM)
    	HPCA_tot_z      (mM)
	
	pump		(mol/cm2)   <1e-16>
	pumpca		(mol/cm2)   <1e-16>
	n
	
	
	Bufer           (mM)
	CaBufer         (mM)
}

INITIAL {
	cai = cai0
	B0 =  Bufer0/(1 + (cai*k1bufer/k2bufer))
	ca = cai
	HPCA = TotalHPCA
	Bufer = B0
	CaBufer = Bufer0 - B0
	parea = PI*diam
	pump = TotalPump/(1 + (cai*k1Pump/k2Pump))
	pumpca = TotalPump - pump
	ica_pmp_last = 0
	rates()
	n = ninf
}
BREAKPOINT { 
	SOLVE scheme1 METHOD sparse
	ica_pmp_last = ica_pmp
	ica = ica_pmp 
	SOLVE states1 METHOD cnexp
	IF ((HPCA_m_z/HPCA_tot_z) > 0.05){
	    gk = tadj*gbar*C*((HPCA_m_z/ HPCA_tot_z) - 0.0497)
	}
	ELSE {gk = 0}
	ik = (1e-4) * gk * (v - ek) : (1e-4) converts pS/um2 to S/cm2
}


DERIVATIVE states1 {
	cai = ca  
	rates()
	n' =  (ninf-n)/ntau
}


LOCAL dsq, dsqvol, r
LOCAL ica_basal 

KINETIC scheme1 {
    r = diam/2
    Vol = PI*r*r
    ica_basal = 2*FARADAY*(k3Pump*TotalPump*cai0*(1e5)/(k2Pump/k1Pump))
    k_ins = (1e-3)*(D * 0.07)/(r^2)

    :multiplies right hand-sides of diff. equations by the volume
    COMPARTMENT (1e10)*parea {pump pumpca HPCA_m}
    COMPARTMENT volo {cao}
    COMPARTMENT Vol {ca HPCA CaHPCA Ca2HPCA Bufer CaBufer}
    
    : kinetic equations for the Ca2+-ATPase
    ~ ca + pump <-> pumpca (k1Pump*parea*(1e10), k2Pump*parea*(1e10))
    ~ pumpca <-> pump + cao (k3Pump*parea*(1e10), k4Pump*parea*(1e10))
    CONSERVE pump + pumpca = TotalPump * parea * (1e10)
    ica_pmp = 2*FARADAY*(f_flux - b_flux)/parea

    :all currents except pump
    ~ ca << (-(ica - ica_basal - ica_pmp_last)*PI*diam/(2*FARADAY))

    ~ ca + HPCA <-> CaHPCA (k1HPCA*Vol, k2HPCA*Vol)
    ~ ca + CaHPCA <-> Ca2HPCA (k3HPCA*Vol, k4HPCA*Vol)
    ~ ca + Bufer <-> CaBufer (k1bufer*Vol, k2bufer*Vol)
    ~ Ca2HPCA <-> HPCA_m (k_ins*Vol, k_out*parea*(1e10)) 

    HPCA_z = HPCA*Vol
    CaHPCA_z = CaHPCA*Vol
    Ca2HPCA_z = Ca2HPCA*Vol
    HPCA_m_z = HPCA_m*parea*(1e10)
    HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z
}


PROCEDURE rates() {  
	a = Ra * HPCA_m * parea 
	b = Rb
	tadj = q10^((celsius - temp)/10)
	ntau = 1/tadj/(a+b)
	ninf = a/(a+b)
}



