from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
import numpy as np
import os
import pickle
from instrumentation import *
from hpca_config import *

work_dir = 'reproducing-experiments/3Feb2021/'
if not os.path.exists(work_dir):
    os.makedirs(work_dir)

#------------------------INITIALIZTION-----------------------
econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = select_section(eval(params['Simulation']['section'].value))

ad.uninsert('mykca')
ad.uninsert('kca')
ad.uninsert('cad')
ad.uninsert('somacar')
ad.insert('hpca2')
ad.uninsert('calH')
ad.insert('cal')
for seg in ad:
    seg.cal.gcalbar = 0.014 * 0.1

ad.diam = params['Neuron']['diam'].value
ad.L = params['Neuron']['length'].value
h.taur_hpca2 = params['HPCA']['tau_r'].value

sc = seclamp_stim( eval(params['Simulation']['dep_loc'].value) )

t = h.Vector().record(h._ref_t)
hpca = h.Vector().record(ad(.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
cai = h.Vector().record(ad(0.5)._ref_cai)
cal = h.Vector().record(ad(0.5)._ref_ica_cal)
clamp_v = h.Vector().record(sc._ref_vc)

run() #run simulation

fig, axs = hpca_plot(t,
        (clamp_v, 'Clamp Voltage (mV)'),
        (cai*1000, 'Ca_i (uM)'),
        (hpca/tot_hpca, 'hpca_m/tot_hpca')
                    )
fig.savefig(work_dir + params['filename'])

