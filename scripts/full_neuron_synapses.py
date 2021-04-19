from random import randint, uniform, seed
from neuron import h from neuron.units import ms, mV import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
import os
import pickle
from instrumentation import *
from hpca_config import *
from Synapse import Synapse
plt.style.use('seaborn-whitegrid')

work_dir = params['working_dir']
if not os.path.exists(work_dir):
    os.makedirs(work_dir)
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
synapses = Synapse.create_synapses(seed_value=444, num_rand_locs=20)
Synapse.play_stimulation(spike_times)
Synapse.plot_synapses_locs(var='gcalbar_cal')


train_stim = trains_stim( h.soma[0](.5), per=20, delay=200,  n=params['Simulation']['#spikes'].value,
        amp=12, dur=10)
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
h.TotalHPCA_hpca2 = 0.03

run(dur=300)

n_spikes = str(params['Simulation']['#spikes'].value)
diameter = str(params['Neuron']['diam'].value)
fig, axs = hpca_plot(t,
        (v, 'mV'),
        #(cai*10**6, 'Cai (nM)'),
        (hpca/tot_hpca, 'HPCAm/HPCAtot')
        #(ik_sahp*10*ad(.5).area(), 'pA'),
        #title= '%s current pulses, f = 25 Hz, amp=10 nA, dur=15 ms, diam = %s um' % (n_spikes, diameter),
                    )


Synapse.plot_synapses_locs()
#fig.savefig(work_dir + '444seed_stim_freq10Hz_50Hz_0uM.pdf')

