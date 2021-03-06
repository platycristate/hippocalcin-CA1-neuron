from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
import numpy as np
import os
import pickle
from instrumentation import *
from hpca_config import *
plt.style.use('seaborn-whitegrid')

#------------------------INITIALIZTION----------------------- 
econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003

ad = eval(params['Simulation']['section'].value)

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


h.C_hpca2 = params['HPCA']['C'].value
h.cai0_hpca2 = params['HPCA']['Ca_i'].value

#print(ad.psection()['density_mechs'].keys())
sc = seclamp_stim( h.soma[0](.5) )
sc.dur1 = 1000
sc.dur2 = 4000

t = h.Vector().record(h._ref_t)
ik_sahp = h.Vector().record(ad(0.5)._ref_ik_hpca2)
cai = h.Vector().record(ad(0.5)._ref_cai)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
#clamp_v = h.Vector().record(sc._ref_vc)

run(dur=12000, v_init=-62)

fig, axs = plt.subplots(3, 1, dpi=150, figsize=(16, 7))
axs[0].plot(t/1000, cai*10**6)
axs[0].set_title('$[Ca^{2+}]$ (nM)', fontsize=14)
#axs[0].set_ylabel('нМ', fontsize=12)
axs[1].plot(t/1000, hpca*100/tot_hpca, color='red')
axs[1].set_title('$[HPCA]_m/[HPCA]_T$ (%)', fontsize=14)
axs[2].plot(t/1000, ik_sahp, color='green')
axs[2].set_title('$I_{K, \ HPCA}$ (mA/cm$^2$)', fontsize=14)
axs[2].set_xlabel('Time (s)', fontsize=14)
fig.tight_layout()
plt.show()
#fig.savefig('../../Diplom/images/example_response.png')
