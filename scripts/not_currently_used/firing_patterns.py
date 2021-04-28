seed_val = int(input())
#______________________________________________________________
from random import randint, uniform, seed
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

plt.style.use('seaborn-whitegrid')

work_dir = params['working_dir']
#d = 'firing_patterns_%s/' % rand_seed
#if not os.path.exists(work_dir + d):
#    print(work_dir + d)
#    os.makedirs(work_dir + d)
#_________________________________INITIALIZATION___________________________________________

econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = eval(params['Simulation']['section'].value)
ad.insert('cal')

for seg in ad:
    seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value

for s in h.allsec():
    if 'apical_dendrite' in str(s):
        s.uninsert('mykca')
        s.uninsert('kca')
        s.uninsert('cad')
        s.insert('hpca2')
        #s.uninsert('calH')
        #s.uninsert('car')
        s.insert('cal')

h.TotalHPCA_hpca2 = params['HPCA']['HPCA0'].value
h.k_out_hpca2 = params['HPCA']['k_out'].value
h.TotalPump_hpca2 = params['HPCA']['Pump0'].value
h.Bufer0_hpca2 = params['HPCA']['Buffer0'].value
h.k1bufer_hpca2 = params['HPCA']['k1B'].value
h.k2bufer_hpca2 = params['HPCA']['k2B'].value
h.k1Pump_hpca2 = params['HPCA']['k1P'].value
h.k2Pump_hpca2 = params['HPCA']['k2P'].value
h.cai0_hpca2 = params['HPCA']['Ca_i'].value

#____________________________________________________________________________________________


t = h.Vector().record(h._ref_t)
ica = h.Vector().record(ad(.5)._ref_ica)
ica_pmp = h.Vector().record(ad(0.5)._ref_ica_pmp_hpca2)
cai = h.Vector().record(ad(0.5)._ref_cai)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
ik_sahp = h.Vector().record(ad(.5)._ref_ik_hpca2)
v = h.Vector().record(h.soma[0](.5)._ref_v)


fig, ax = plt.subplots(2, 1, dpi=150)
spike_times = list(range(50, 1500, 100))
synapses = Synapse.create_synapses(seed_value=seed_val, num_rand_locs=20)
Synapse.play_stimulation(spike_times)
print('seed = %s' % seed_val)
h.TotalHPCA_hpca2 = 0.0
run(dur=2000)

ax[0].plot(t, v)
h.TotalHPCA_hpca2 = 0.03
run(dur=2000)

ax[1].plot(t, v)
plt.show()
ax[0].clear()
ax[1].clear()
    
#fig.savefig(work_dir + d + 'firing_patterns_%s_seed_conc.pdf' % rand_seed)
