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
ad.uninsert('car')

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
h.k3Pump_hpca2 = params['HPCA']['k3P'].value
h.k4Pump_hpca2 = params['HPCA']['k4P'].value
h.cai0_hpca2 = params['HPCA']['Ca_i'].value
ad.diam = params['Neuron']['diam'].value
ad.L = params['Neuron']['length'].value

print(ad.psection()['density_mechs'].keys())
sc = seclamp_stim( eval(params['Simulation']['dep_loc'].value) )
sc.dur1 = 1000
sc.dur2 = 4000


t = h.Vector().record(h._ref_t)
#ica_t = h.Vector().record(ad(.5)._ref_iCa_cat)
ica_l = h.Vector().record(ad(.5)._ref_ica_cal)
CaB = h.Vector().record(ad(.5)._ref_CaBufer_hpca2)
ica_pmp = h.Vector().record(ad(0.5)._ref_ica_pmp_hpca2)
ik_sahp = h.Vector().record(ad(0.5)._ref_ik_hpca2)
cai = h.Vector().record(ad(0.5)._ref_cai)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
ica_basal = h.Vector().record(ad(.5)._ref_ica_basal_hpca2)
clamp_v = h.Vector().record(sc._ref_vc)


run(dur=12000)

print(cai[-1]*10**6, 'nM')
diameter = str(ad.diam)
ik_sahp = np.array(ik_sahp)
actual_sahp =  ik_sahp[np.where( np.array(t) > sc.dur2 )[0][0]:] 
half_decay =  np.array(t)[np.array(t) > sc.dur2][ np.where( actual_sahp < actual_sahp[0]/np.e )[0][0] ]

tau_sahp = (half_decay - sc.dur2)/1000
print('tau_sAHPk = ',round(tau_sahp, 1), ' s')

fig, axs = hpca_plot(t,
        #(clamp_v, 'Voltage clamp, mV'),
        #(ica*1000, 'ICa (pA/pF)'),
        (cai*10**6, 'Ca (nM)'),
        (hpca/tot_hpca, 'hpca/tot_hpca'),
        #(ica_t*10*ad(.5).area(), 'T, pA'),
        #(ica_l, 'L, mA/cm2'),
        (ik_sahp*10*ad(.5).area(), 'ik (sahp) pA'),
        #(CaB*10**3, 'CaB (uM)'),
#       (ica_basal, 'Ica_basal (mA/cm2)'),
        title="diameter=%s um" % diameter
                    )
fig.savefig(work_dir + 'test.pdf')
