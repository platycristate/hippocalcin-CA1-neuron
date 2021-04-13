rand_seed = 888

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
d = 'firing_patterns %s/' % rand_seed
if not os.path.exists(work_dir):
    os.makedirs(work_dir)
    os.makedirs(d)
#_________________________________INITIALIZATION___________________________________________

econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = eval(params['Simulation']['section'].value)
ad.uninsert('mykca')
ad.uninsert('kca')
ad.uninsert('cad')
ad.insert('hpca2')
ad.uninsert('calH')
ad.insert('cal')

for seg in ad:
    seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value
    #seg.cat.gcatbar = params['CaT']['gcatbar_dendrite'].value

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
spike_times = list(range(950, 3000, 100))
synapses = Synapse.create_synapses(seed_value=rand_seed, num_rand_locs=20)
Synapse.play_stimulation(spike_times)
Synapse.plot_synapses_locs()

train_stim = trains_stim( h.soma[0](.5), per=20, delay=200,  n=params['Simulation']['#spikes'].value,
        amp=12, dur=1)
train_stim.num = 25
ipulses = h.Vector().record(train_stim._ref_i)

t = h.Vector().record(h._ref_t)
ica = h.Vector().record(ad(.5)._ref_ica)
ica_pmp = h.Vector().record(ad(0.5)._ref_ica_pmp_hpca2)
cai = h.Vector().record(ad(0.5)._ref_cai)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
ik_sahp = h.Vector().record(ad(.5)._ref_ik_hpca2)
v = h.Vector().record(ad(.5)._ref_v)

fig, ax = plt.subplots(3, 1, dpi=150)

for idx, conc in enumerate([0, 0.01, 0.03]):
    h.TotalHPCA_hpca2 = conc
    run(dur=3000)
    ax[idx].plot(t, v)
    ax[idx].set_title('[HPCA] = %s' % conc)

fig.tight_layout()
plt.show()
fig.savefig(work_dir + d + 'firing_patterns_%s_seed_conc.pdf' % rand_seed)

fig, ax = plt.subplots(3, 1, dpi=150)
for idx, per in enumerate([100, 200, 300]):
    spike_times = list(range(950, 3000, per))
    Synapse.play_stimulation(spike_times)
    run(dur=3000)
    ax[idx].plot(t, v)
    ax[idx].set_title('ISI = %s ms' % per)

fig.tight_layout()
plt.show()
fig.savefig(work_dir + d + 'firing_patterns_%s_seed_period.pdf' % rand_seed)
