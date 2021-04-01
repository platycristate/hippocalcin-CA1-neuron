COMMENT
/**
 * @file TsodyksMarkramAMPA_NMDA.mod
 * @brief An AMPA and NMDA glutamate receptor model
 * @author emuller
 * @date 2017-05-11
 */
ENDCOMMENT

TITLE AMPA and NMDA glutamate receptor

COMMENT
AMPA and NMDA glutamate receptor conductance using the dual exponential profile
ENDCOMMENT

: Definition of variables which may be accessed by the user
NEURON {
    THREADSAFE

    POINT_PROCESS SimpleAMPA_NMDA
    RANGE tau_r_AMPA, tau_d_AMPA
    RANGE tau_r_NMDA, tau_d_NMDA
    RANGE gmax_AMPA
    RANGE gmax_NMDA
    RANGE mg
    RANGE tau_rec, tau_facil, U1
    RANGE i, i_AMPA, i_NMDA, g_NMDA, g_AMPA, g, e
    NONSPECIFIC_CURRENT i
}

: Definition of constants which may be set by the user
PARAMETER {

    tau_r_AMPA = 0.2    (ms) : Dual-exp conductance profile
    tau_d_AMPA = 1.7    (ms) : Note that tau_d >> tau_r

    tau_r_NMDA = 0.29   (ms)
    tau_d_NMDA = 43     (ms)

    e = 0               (mV) : AMPA and NMDA reversal potential
    mg = 1              (mM)
    mggate

    gmax_AMPA = 0.001   (uS) : maximal conductance of synapse
    gmax_NMDA = 0.001   (uS) : maximal conductance of synapse
}

: Declaration of state variables
STATE {
    A_AMPA    : AMPA state variable to construct the dual-exponential profile
              : rise kinetics with tau_r_AMPA
    B_AMPA    : AMPA state variable to construck the dual exponential profile
              : decay kinetics with tau_d_AMPA
    A_NMDA

    B_NMDA
}

: Declaration of variables that are to be computed, e.g in the BREAKPOINT block
ASSIGNED {
    v (mV)
    i (nA)
    i_AMPA (nA)
    i_NMDA (nA)
    g_AMPA (uS)
    g_NMDA (uS)
    g (uS)
    factor_AMPA
    factor_NMDA
}

: Declaration of initial conditions
INITIAL {

    LOCAL tp_AMPA, tp_NMDA   : Declaration of some local variables

    : Zero receptor rise and decay kinetics variables
    A_AMPA = 0
    B_AMPA = 0

    A_NMDA = 0
    B_NMDA = 0

    : Compute constants needed to normalize the double-exponential receptor dynamics

    : Expression for time to peak of the AMPA conductance
    tp_AMPA = (tau_r_AMPA * tau_d_AMPA) / (tau_d_AMPA - tau_r_AMPA) * log(tau_d_AMPA / tau_r_AMPA)
    tp_NMDA = (tau_r_NMDA * tau_d_NMDA) / (tau_d_NMDA - tau_r_NMDA) * log(tau_d_NMDA / tau_r_NMDA)

    : AMPA normalization factor - so that when t = tp_AMPA, gsyn = gpeak
    factor_AMPA = -exp(-tp_AMPA / tau_r_AMPA) + exp(-tp_AMPA/tau_d_AMPA)
    factor_AMPA = 1 / factor_AMPA

    : NMDA normalization factor - so that when t = tp_NMDA, gsyn = gpeak
    factor_NMDA = -exp(-tp_NMDA / tau_r_NMDA) + exp(-tp_NMDA/tau_d_NMDA)
    factor_NMDA = 1 / factor_NMDA
}

: Declare method to propagate the state variables in time
BREAKPOINT {

    : Specify to solve system of ODEs, declared  below (DERIVATIVE block)
    : 'cnexp' specifies the integration method, it is
    : an implicit integration method that is stable even for stiff systems
    SOLVE odes METHOD cnexp

    : Compute and assign quantities which depend on the state variables

    : Compute the time varying AMPA receptor conductance as
    : the difference of state variables B_AMPA and A_AMPA
    g_AMPA = gmax_AMPA * (B_AMPA - A_AMPA)
    mggate = 1 / (1 + exp(0.062 (/mV) * -(v)) * (mg / 3.57 (mM)))
    g_NMDA = mggate * gmax_NMDA * (B_NMDA - A_NMDA)

    : Total conductace
    g = g_AMPA + g_NMDA

    : Compute the AMPA and NMDA specific currents
    i_AMPA = g_AMPA * (v - e)
    i_NMDA = g_NMDA * (v - e)

    : Compute the total current
    i = i_AMPA + i_NMDA
}

: Declaration of ODEs solved in the BREAKPOINT block
DERIVATIVE odes {

    A_AMPA' = -A_AMPA / tau_r_AMPA
    B_AMPA' = -B_AMPA / tau_d_AMPA
    A_NMDA' = -A_NMDA / tau_r_NMDA
    B_NMDA' = -B_NMDA / tau_d_NMDA

}

: Block to be executed for a pre-synaptic spike event
NET_RECEIVE (weight) {

    A_AMPA = A_AMPA + weight * factor_AMPA
    B_AMPA = B_AMPA + weight * factor_AMPA
    A_NMDA = A_NMDA + weight * factor_NMDA
    B_NMDA = B_NMDA + weight * factor_NMDA
}
