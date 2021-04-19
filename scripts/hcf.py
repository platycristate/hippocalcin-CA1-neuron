from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
import numpy as np
import os
import pickle
from instrumentation import *
from hpca_config import *

#work_dir = params['working_dir']
#if not os.path.exists(work_dir):
#    os.makedirs(work_dir)

#------------------------INITIALIZTION-----------------------
econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = eval(params['Simulation']['section'].value)
ad.insert('cal')

for seg in ad:
    seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value

for s in h.allsec():
    if 'apical_dendrite' in str(s):
        s.uninsert('mykca')
        s.uninsert('kca')
        s.uninsert('cad')
        s.insert('hpca2')
        s.uninsert('car')
        s.insert('cal')



h.TotalHPCA_hpca2 = 0.03 #params['HPCA']['HPCA0'].value
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

#print(ad.psection()['density_mechs'].keys())
#sc = seclamp_stim( h.soma[0](.5) )
#sc.dur1 = 1000
#sc.dur2 = 4000

ic = h.IClamp( h.soma[0](.5) )
ic.delay = 100 * ms
ic.dur = 4000 * ms
ic.amp = 0.7 # nA  = 100 pa


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
v = h.Vector().record(ad(.5)._ref_v)
#clamp_v = h.Vector().record(sc._ref_vc)

print(ad(.5).g_pas)
run(dur=12000)

fig, axs = hpca_plot(t,
        #(clamp_v, 'Voltage clamp, mV'),
        #(ica*1000, 'ICa (pA/pF)'),
        (v, 'mV'),
        (cai*10**6, 'Ca (nM)'),
        (hpca/tot_hpca, 'hpca/tot_hpca'),
        #(ica_t*10*ad(.5).area(), 'T, pA'),
        #(ica_l, 'L, mA/cm2'),
        (ik_sahp*10*ad(.5).area(), 'ik (sahp) pA'),
        #(CaB*10**3, 'CaB (uM)'),
#       (ica_basal, 'Ica_basal (mA/cm2)'),
        title="diameter=%s um" % ad.diam
                    )
#fig.savefig(work_dir + 'test.pdf')
