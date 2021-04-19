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
work_dir = params['working_dir'] #d = 'firing_patterns_%s/' % rand_seed
#if not os.path.exists(work_dir + d):
#    print(work_dir + d)
#    os.makedirs(work_dir + d)
#_________________________________INITIALIZATION___________________________________________

econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = eval(params['Simulation']['section'].value)

for s in h.allsec():
    s.uninsert('kca')
    s.uninsert('mykca')
    if 'apical_dendrite' in str(s):
        s.uninsert('cad')
        s.insert('hpca2')
        s.uninsert('car')
        s.insert('cal')
        for seg in s:
            seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value

h.cai0_hpca2 = params['HPCA']['Ca_i'].value
h.C_hpca2 = 0.1
h.TotalHPCA_hpca2 = 0.03

print(h.topology())
central = [0, 1, 2, 3, 4, 5]
distal = [116, 78, 56]

central_synapses = []
for i in central:
    central_synapses.append( Synapse(h.apical_dendrite[i](.5)) )

distal_synapses = []
for i in distal:
    distal_synapses.append( Synapse(h.apical_dendrite[i](.5)) )

central_times = list(range(100, 1500, 100))
start_times = [i for i in range(100, 3000, 100)]

for start in start_times:
    distal_times = list(range(start, 1500, 100))
    Synapse.play_stimulation(distal_times)
    run(dur=3000, v_init=-66)


t = h.Vector().record(h._ref_t)
cai = h.Vector().record(ad(0.5)._ref_cai)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
ik_sahp = h.Vector().record(ad(.5)._ref_ik_hpca2)
v = h.Vector().record(h.soma[0](.5)._ref_v)
v_dend = h.Vector().record(h.apical_dendrite[23](.5)._ref_v)
v_dend2 = h.Vector().record(h.apical_dendrite[55](.5)._ref_v)


#ax[0].plot(t, v, lw=1, color='black')
#ax[1].plot(t, (hpca/tot_hpca)*100, color='red')
#ax[1].set(xlabel='time [s]', ylabel='%')
