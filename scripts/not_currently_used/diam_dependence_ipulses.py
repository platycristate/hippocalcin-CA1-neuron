
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
train_stim = trains_stim( ad(0.5), per=20, delay=1000,  n=params['Simulation']['#spikes'].value,
        amp=10, dur=1 )
train_stim.num = 100

t = h.Vector().record(h._ref_t)
ica = h.Vector().record(ad(.5)._ref_ica)
ica_pmp = h.Vector().record(ad(0.5)._ref_ica_pmp_hpca2)
cai = h.Vector().record(ad(0.5)._ref_cai)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
ipulses = h.Vector().record(train_stim._ref_i)


################################################################
fig, axs = plt.subplots(1, 1, dpi=100, figsize=(12, 6))

for d in diams:
    ad.diam = d # um
    run()
    axs.plot(t/1000, 100*hpca/tot_hpca,lw=1.2, label=d)


axs.set(xlabel='time [s]', ylabel='%')
axs.legend(title='Diam, um:', fontsize=15)
axs.set_title('$HPCA_m/HPCA_T$')

fig.tight_layout()

plt.show()

#fig.savefig(work_dir + params['filename'])

