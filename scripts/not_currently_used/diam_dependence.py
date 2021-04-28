
diams = [1, 2, 4]

######################################################################
from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
import numpy as np
import os
import pickle
from instrumentation import *
from hpca_config import *

work_dir = params['working_dir']
if not os.path.exists(work_dir):
    os.makedirs(work_dir)

#------------------------INITIALIZTION-----------------------
econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = select_section(eval(params['Simulation']['section'].value))
#ad = eval(params['Simulation']['section'].value)

ad.uninsert('mykca')
ad.uninsert('kca')
ad.uninsert('cad')
ad.insert('hpca2')
ad.uninsert('calH')
ad.insert('cal')

for seg in ad:
    seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value
    seg.cat.gcatbar = params['CaT']['gcatbar_dendrite'].value

h.TotalHPCA_hpca2 = params['HPCA']['Buffer0'].value
h.k7HPCA_hpca2 = params['HPCA']['k7HPCA'].value
h.TotalPump_hpca2 = params['HPCA']['Pump0'].value
h.Bufer0_hpca2 = params['HPCA']['Buffer0'].value
h.k1bufer_hpca2 = params['HPCA']['k1B'].value
h.k2bufer_hpca2 = params['HPCA']['k2B'].value
h.k1Pump_hpca2 = params['HPCA']['k1P'].value
h.k2Pump_hpca2 = params['HPCA']['k2P'].value
h.cai0_hpca2 = params['HPCA']['Ca_i'].value
h.tau_d_hpca2 = params['HPCA']['tau_d'].value
ad.diam = params['Neuron']['diam'].value
ad.L = params['Neuron']['length'].value

print(ad.psection()['density_mechs'].keys())
sc = seclamp_stim( eval(params['Simulation']['dep_loc'].value) )


t = h.Vector().record(h._ref_t)
ica = h.Vector().record(ad(.5)._ref_ica)
ica_pmp = h.Vector().record(ad(0.5)._ref_ica_pmp_hpca2)
cai = h.Vector().record(ad(0.5)._ref_cai)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
clamp_v = h.Vector().record(sc._ref_vc)


################################################################
fig, axs = plt.subplots(2, 1, dpi=100, figsize=(12, 12))

for d in diams:
    ad.diam = d # um
    run()
    axs[0].plot(t/1000, cai*10**6 )
    axs[1].plot(t/1000, 100*hpca/tot_hpca, label=d)


axs[0].set(ylabel='nM')
axs[1].set(xlabel='time [s]', ylabel='%')
axs[1].legend(title='Diam, um:', fontsize=15)
axs[0].set_title('$[Ca^{2+}]_i$')
axs[1].set_title('$HPCA_m/HPCA_T$')

fig.tight_layout()

plt.show()

#fig.savefig(work_dir + params['filename'])

