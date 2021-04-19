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
#____________________________________________________________________________________________
ic = h.IClamp(h.soma[0](.5))
ic.delay = 50 * ms
ic.dur = 1000 * ms
ic.amp = 0.2 # nA  = 100 pa


t = h.Vector().record(h._ref_t)
v = h.Vector().record(h.soma[0](.5)._ref_v)
v_dend = h.Vector().record(h.apical_dendrite[23](.5)._ref_v)
v_dend2 = h.Vector().record(h.apical_dendrite[55](.5)._ref_v)



fig, ax = plt.subplots(1, 2, dpi=150, figsize=(8, 16))

run(dur=1100)
ax[0].plot(t, v, lw=0.7, color='black')
ax[1].plot(t, v_dend, lw=0.7, color='red')

plt.show()
    
#fig.savefig(work_dir + d + 'firing_patterns_%s_seed_conc.pdf' % rand_seed)
