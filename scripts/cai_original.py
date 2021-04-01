from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
import numpy as np
import os
import pickle
from instrumentation import *
from hpca_config import *

work_dir = 'reproducing-experiments/9Feb2021/'
if not os.path.exists(work_dir):
        os.makedirs(work_dir)

#------------------------INITIALIZTION-----------------------
econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = eval(params['Simulation']['section'].value)

#ad.uninsert('somacar')

sc = seclamp_stim( ad(.5) )
t = h.Vector().record(h._ref_t)
cai = h.Vector().record(ad(.5)._ref_cai)
clamp_v = h.Vector().record(sc._ref_vc)
ik_sahp = h.Vector().record(ad(.5)._ref_ik_kca)

run()

fig, axs = hpca_plot(t,
        (clamp_v, 'Clamp Voltage (mV)'),
        (cai*1000, 'Ca_i (uM)'),
        (ik_sahp*1000, 'pA/pF')
                    )
#fig.savefig(work_dir + 'original_cai_without_somacar_taur1400ms.pdf')

