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
if not os.path.exists(work_dir):
    os.makedirs(work_dir)
#_________________________________INITIALIZATION___________________________________________

econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = eval(params['Simulation']['section'].value)

for s in h.allsec():
    mechs = s.psection()['density_mechs'].keys()
    s.uninsert('kca')
    if h.ismembrane('hha2'):
        seg.hha2.gkbar *= 5
    if 'hha_old' in mechs:
        for seg in s:
            seg.hha_old.gkbar *= 5
    if 'apical_dendrite' in str(s) or 'soma' in str(s):
        s.uninsert('cad')
        s.insert('hpca2')
        s.uninsert('car')
        s.insert('cal')
        for seg in s:
            seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value


h.cai0_hpca2 = params['HPCA']['Ca_i'].value
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
iclamp = h.Vector().record(ic._ref_i)
v = h.Vector().record(h.soma[0](.5)._ref_v)
v_dend = h.Vector().record(h.apical_dendrite[23](.5)._ref_v)
v_dend2 = h.Vector().record(h.apical_dendrite[55](.5)._ref_v)

apc = h.APCount(h.soma[0](0.5))
apc.thresh = -15 * mV
fig, ax = plt.subplots(1, 1, dpi=150, figsize=(12, 16))

##PARAMETERS##############

h.C_hpca2 = 0.2
h.TotalHPCA_hpca2 = 0.03

##########################

run(dur=1000, v_init=-62)

ax.plot(t, v, color='black')
ax.set_ylabel('mV', fontsize=16)
ax.set_xlabel('Time (ms)', fontsize=16)
#ax[2].plot(t, (hpca/tot_hpca)*100, color='red')
#ax[2].set(xlabel='time [s]', ylabel='%')
#plt.savefig(params['working_dir'] + 'fp5_0p1_62mV.pdf')
#plt.savefig('../../Diplom/images/fp2.png')
plt.show()
