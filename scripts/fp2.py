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

h.TotalHPCA_hpca2 = params['HPCA']['HPCA0'].value
h.cai0_hpca2 = params['HPCA']['Ca_i'].value
h.C_hpca2 = params['HPCA']['C'].value



ic = h.IClamp(h.soma[0](.5))
ic.delay = 100 * ms
ic.dur = 800 * ms
ic.amp = 0.460 # nA  = 100 pa


t = h.Vector().record(h._ref_t)
ica = h.Vector().record(ad(.5)._ref_ica)
ica_pmp = h.Vector().record(ad(0.5)._ref_ica_pmp_hpca2)
cai = h.Vector().record(ad(0.5)._ref_cai)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
ik_sahp = h.Vector().record(ad(.5)._ref_ik_hpca2)
v = h.Vector().record(h.soma[0](.5)._ref_v)
v_dend = h.Vector().record(h.apical_dendrite[23](.5)._ref_v)
v_dend2 = h.Vector().record(h.apical_dendrite[55](.5)._ref_v)

apc = h.APCount(h.soma[0](0.5))
apc.thresh = -15 * mV
fig, ax = plt.subplots(2, 1, dpi=150, figsize=(8, 16))

h.C_hpca2 = 0.1
h.TotalHPCA_hpca2 = 0.03

run(dur=8000, v_init=-66)

ax[0].plot(t, v, lw=1, color='black')
ax[1].plot(t, (hpca/tot_hpca)*100, color='red')
ax[1].set(xlabel='time [s]', ylabel='%')
print(apc.n)


plt.show()
    
#fig.savefig(work_dir + d + 'firing_patterns_%s_seed_conc.pdf' % rand_seed)
