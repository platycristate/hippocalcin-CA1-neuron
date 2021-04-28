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
per = int(sys.argv[1])
c = 0.2

central = [6, 4, 0, 2, 5, 7, 2, 1]
seed(2489)

dt = 0.1
econ = initialize() 
for s in h.allsec():
    mechs = s.psection()['density_mechs'].keys()
    s.uninsert('kca')
    if h.ismembrane('hha2'):
        for seg in s:
            seg.hha2.gkbar = params['HH_IK']['gkbar_soma'].value
    if 'hha_old' in mechs:
        for seg in s:
            seg.hha_old.gkbar = params['HH_IK']['gkbar_dend'].value
    if 'apical_dendrite' in str(s) or 'soma' in str(s):
        s.uninsert('cad')
        s.insert('hpca2')
        s.uninsert('car')
        s.insert('cal')
        for seg in s:
            seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value

h.cai0_hpca2 = params['HPCA']['Ca_i'].value
h.C_hpca2 = c
h.TotalHPCA_hpca2 = params['HPCA']['HPCA0'].value

t = h.Vector().record(h._ref_t)
v = h.Vector().record(h.soma[0](.5)._ref_v)
i_na = h.Vector().record(h.soma[0](.5)._ref_ina) 
i_ca = h.Vector().record(h.soma[0](.5)._ref_ik) 
i_k  = h.Vector().record(h.soma[0](.5)._ref_ica) 


distal = [randint(50, 80) for i in range(10)]
Synapse.gmax_AMPA /= len(central)
Synapse.gmax_NMDA /= len(central)
central_synapses = []
for i in central:
    central_synapses.append( Synapse(h.apical_dendrite[i](.5)) )

Synapse.setup_gmax(
    gmax_AMPA_new=0.001 * 80, 
    gmax_NMDA_new = 0.001 * 0.7 * 80
    )

Synapse.gmax_AMPA /= len(distal)
Synapse.gmax_NMDA /= len(distal)
distal_synapses = []
for i in distal:
    distal_synapses.append( Synapse(h.apical_dendrite[i](.5)) )

central_times = [i for i in range(2200, 2500, per)]
distal_times = [i for i in range(100, 4400, 200)]
stim_central = Synapse.create_stim(central_synapses)
stim_distal = Synapse.create_stim(distal_synapses)
Synapse.play_stimulation(stim_central, central_times)
Synapse.play_stimulation(stim_distal, distal_times)

#---------------------------COUNTER OF AP----------------------------
apc = h.APCount(h.soma[0](.5))
apc.thresh = -15

#---------------------------RUN THE SIMULATION------------------------
run(5000, v_init=-62)

t = np.array(t)
i_soma = np.array(i_na) + np.array(i_ca) + np.array(i_k)
i_soma0 = i_soma[ np.where(t > 100)[0][0] : np.where(t > 2000)[0][0] ]
i_soma1 = i_soma[ np.where(t > 2700)[0][0] : np.where(t > 4600)[0][0] ]
Q0 = simps(i_soma0, dx=dt) 
Q1 = simps(i_soma1, dx=dt)

print('%s,%s,%s' % (apc.n, Q1/Q0,c))

#fig, axs = plt.subplots(2, 1, dpi=150)
#axs[0].plot(t, v, color='black')
#axs[0].set_ylabel('мВ', fontsize=14)
#axs[1].plot(t, i_soma, color='red')
#axs[1].set_ylabel('мА/см$^2$')
#
#fig.tight_layout()
#plt.show()
    
