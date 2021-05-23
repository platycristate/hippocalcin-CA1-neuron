from random import seed, randint
from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
import os
import pickle
from instrumentation import *
from hpca_config import *
from Synapse import Synapse
from scipy.integrate import simps
import sys
plt.style.use('seaborn-whitegrid')

# reading value of stimulation period
per = 150 # ms
c = 0.3 / 10
dt = 0.1

# seed value for generating random numbers 
seed(34567)

econ = initialize()
for s in h.allsec():
    mechs = s.psection()['density_mechs'].keys()
    s.uninsert('kca')
    # changin density of potassium channels in order
    # to decrease spike half-width to 1 ms
    if h.ismembrane('hha2'):
        for seg in s:
            seg.hha2.gkbar = params['HH_IK']['gkbar_soma'].value
    if 'hha_old' in mechs:
        for seg in s:
            seg.hha_old.gkbar = params['HH_IK']['gkbar_dend'].value
    if 'apical_dendrite' in str(s) or 'soma' in str(s):
        s.uninsert('cad')
        # adding hippocalcin to the model
        s.insert('hpca2')

        s.uninsert('car')
        s.insert('cal')
        for seg in s:
            seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value

h.cai0_hpca2 = params['HPCA']['Ca_i'].value
h.C_hpca2 = c
h.TotalHPCA_hpca2 = params['HPCA']['HPCA0'].value

# settting up recording variables for 
# membrane potential and time
t = h.Vector().record(h._ref_t)
v = h.Vector().record(h.soma[0](.5)._ref_v)
v_dend = h.Vector().record(h.apical_dendrite[60](.5)._ref_v)

# setting up recording variable for currents
i_na = h.Vector().record(h.soma[0](.5)._ref_ina)
i_ca = h.Vector().record(h.soma[0](.5)._ref_ik)
i_k  = h.Vector().record(h.soma[0](.5)._ref_ica)
i_na_dend = h.Vector().record(h.apical_dendrite[60](.5)._ref_ina)
i_ca_dend = h.Vector().record(h.apical_dendrite[60](.5)._ref_ik)
i_k_dend  = h.Vector().record(h.apical_dendrite[60](.5)._ref_ica)

# setting locations of synapses
#apical_dendrite[50]

central_locs = [6, 4, 0, 2, 5, 7, 2, 1]
distal_locs = [randint(80, 100) for i in range(10)]

# Dividing total conductance among all
# proximal synapses
Synapse.setup_gmax(
    gmax_AMPA_new=0.001 * 30,
    gmax_NMDA_new = 0.001 * 0.7 * 30
)
Synapse.gmax_AMPA /= len(central_locs)
Synapse.gmax_NMDA /= len(central_locs)


# Setting up central synapses
central_synapses = []
for i in central_locs:
    central_synapses.append( Synapse(h.apical_dendrite[i](.5)) )

# Create new maximal conductance
Synapse.setup_gmax(
    gmax_AMPA_new=0.001 * 80,
    gmax_NMDA_new = 0.001 * 0.7 * 80
)

Synapse.gmax_AMPA /= len(distal_locs)
Synapse.gmax_NMDA /= len(distal_locs)

# Setting up distal synapses
distal_synapses = []
for i in distal_locs:
    distal_synapses.append( Synapse(h.apical_dendrite[i](.5)) )


#---------------------------------------------------------------------
central_times = [i for i in range(2000, 2600, per)]
distal_times = [i for i in range(100, 4400, 200)]

stim_central = Synapse.create_stim(central_synapses)
stim_distal = Synapse.create_stim(distal_synapses)

Synapse.play_stimulation(stim_central, central_times)
Synapse.play_stimulation(stim_distal, distal_times)

Synapse.plot_synapses_locs([central_synapses, distal_synapses],
        colors=['g', 'r'])

plt.show()
no_pres_ap = len( central_times )

#---------------------------COUNTER OF AP----------------------------
apc = h.APCount(h.soma[0](.5))
apc.thresh = -15

#---------------------------RUN THE SIMULATION------------------------
run(5000, v_init=-62)
t = np.array(t)
t0 = 100
t1 = 1900
t2 = 2700
t3 = 4500

# calculating the total currrent
i_soma = np.array(i_na) + np.array(i_ca) + np.array(i_k)
i_dend = np.array(i_na_dend) + np.array(i_ca_dend) + np.array(i_k_dend)

# Calculating charge transferred before and after 
# proximal stimulation
i_soma0 = i_soma[ np.where(t > t0)[0][0] : np.where(t > t1)[0][0] ]
i_soma1 = i_soma[ np.where(t > t2)[0][0] : np.where(t > t3)[0][0] ]
Q0 = simps(i_soma0, dx=dt)
Q1 = simps(i_soma1, dx=dt)

print('%s,%s,%s,%s' % (apc.n, Q1/Q0, c, no_pres_ap))

fig, axs = plt.subplots(2, 2, dpi=150)

axs[0, 0].plot(t, v_dend, color='black')
axs[0, 1].set_title("Distal dendrite" , fontsize=14)
axs[0, 0].set_ylabel('mV', fontsize=14)
axs[1, 0].plot(t, i_dend, color='red')
axs[1, 0].set_ylabel('$mA/cm^2$')

axs[0, 1].plot(t, v, color='black')
axs[0, 1].set_title("Soma", fontsize=14)
axs[0, 1].set_ylabel('mV', fontsize=14)
axs[1, 1].plot(t, i_soma, color='red')
axs[1, 1].set_ylabel('$mA/cm^2$')

fig.tight_layout()
plt.show()
