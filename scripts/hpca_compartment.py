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

h.TotalHPCA_hpca2 = params['HPCA']['HPCA0'].value
h.k7HPCA_hpca2 = params['HPCA']['k7HPCA'].value
h.TotalPump_hpca2 = params['HPCA']['Pump0'].value
h.Bufer0_hpca2 = params['HPCA']['Buffer0'].value
h.k1bufer_hpca2 = params['HPCA']['k1B'].value
h.k2bufer_hpca2 = params['HPCA']['k2B'].value
h.k1Pump_hpca2 = params['HPCA']['k1P'].value
h.k2Pump_hpca2 = params['HPCA']['k2P'].value
h.k3Pump_hpca2 = params['HPCA']['k3P'].value
h.k4Pump_hpca2 = params['HPCA']['k4P'].value
h.cai0_hpca2 = params['HPCA']['Ca_i'].value
h.tau_d_hpca2 = params['HPCA']['tau_d'].value 
ad.diam = params['Neuron']['diam'].value
ad.L = params['Neuron']['length'].value

print(ad.psection()['density_mechs'].keys())
sc = seclamp_stim( eval(params['Simulation']['dep_loc'].value) )
sc.dur1 = 1000
sc.dur2 = 4000


t = h.Vector().record(h._ref_t)
ica = h.Vector().record(ad(.5)._ref_ica)
ica_pmp = h.Vector().record(ad(0.5)._ref_ica_pmp_hpca2)
ik_sahp = h.Vector().record(ad(0.5)._ref_ik_hpca2)
cai = h.Vector().record(ad(0.5)._ref_cai)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
ica_basal = h.Vector().record(ad(.5)._ref_ica_basal_hpca2)
clamp_v = h.Vector().record(sc._ref_vc)

print(ad.nseg)
run(dur=10000)

print(cai[1]*10**6, 'nM')
print(hpca[-1], 'mol/cm2')
diameter = str(ad.diam)
#plt.plot(t/1000, ica*1000, color='black')
#plt.ylabel('pA/pF')
#plt.show()
print(ica_basal[3], 'mA/cm2')
fig, axs = hpca_plot(t,
        #(clamp_v, 'Voltage clamp, mV'),
        #(ica*1000, 'ICa (pA/pF)'),
        (cai*10**6, 'Ca (nM)'),
        (hpca/tot_hpca, 'hpca/tot_hpca'),
        (ik_sahp*10*ad(.5).area(), 'I_sAHP (pA)'),
#        (ica_basal, 'Ica_basal (mA/cm2)'),
        title="diameter=%s um" % diameter
                    )
#fig.savefig(work_dir + params['filename'])
