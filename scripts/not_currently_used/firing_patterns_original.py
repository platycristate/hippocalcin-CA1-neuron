rand_seed = 1254

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
d = 'firing_patterns_%s/' % rand_seed
if not os.path.exists(work_dir + d):
    print(work_dir + d)
    os.makedirs(work_dir + d)
#_________________________________INITIALIZATION___________________________________________

econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = eval(params['Simulation']['section'].value)
#____________________________________________________________________________________________
#spike_times = list(range(950, 3000, 100))
#synapses = Synapse.create_synapses(seed_value=rand_seed, num_rand_locs=20)
#Synapse.play_stimulation(spike_times)
#Synapse.plot_synapses_locs()

train_stim = trains_stim( h.soma[0](.5), per=20, delay=200,  n=params['Simulation']['#spikes'].value,
        amp=20, dur=1) 
train_stim.num = 25
ipulses = h.Vector().record(train_stim._ref_i)


t = h.Vector().record(h._ref_t)
ica = h.Vector().record(ad(.5)._ref_ica)
cai = h.Vector().record(ad(0.5)._ref_cai)
v = h.Vector().record(ad(.5)._ref_v)

fig, ax = plt.subplots(1, 1, dpi=150)

run(dur=3000)
ax.plot(t, v)

fig.tight_layout()
plt.show()
