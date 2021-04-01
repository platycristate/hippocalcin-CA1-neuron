#________________________________________INPUT___________________________________
freqs = [10, 20, 50] # Hz
N = [1, 3, 10, 20, 50, 100] # number of current pulses
diameters = [2] # um



#______________________________BEGINNING OF THE SCRIPT______________________________
from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
from matplotlib import rc
import numpy as np
import os
import pickle
from instrumentation import *
from hpca_config import *

font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 16}

rc('font', **font)

work_dir = params['working_dir']
if not os.path.exists(work_dir):
    os.makedirs(work_dir)

#_______________________________INITIALIZATION_____________________________________

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

# Setting of the parameters
h.TotalHPCA_hpca2 = params['HPCA']['HPCA0'].value
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

# Creating generator of current pulses
train_stim = trains_stim( ad(0.5), per=20, delay=3000,  n=params['Simulation']['#spikes'].value,
        amp=10, dur=1 )

#_______________________________CREATING RECORDING's VECTORS____________________________

t = h.Vector().record(h._ref_t)

# Calcium currents
ICa = h.Vector().record(ad(.5)._ref_ica)
ICa_pmp = h.Vector().record(ad(0.5)._ref_ica_pmp_hpca2)


ipulses = h.Vector().record(train_stim._ref_i)

# [CaB] and [Ca2+]
Cai = h.Vector().record(ad(0.5)._ref_cai)
CaBuffer = h.Vector().record(ad(0.5)._ref_CaBufer_hpca2)
CaHPCA = h.Vector().record(ad(0.5)._ref_CaHPCA_hpca2)
Ca2HPCA = h.Vector().record(ad(0.5)._ref_Ca2HPCA_hpca2)
HPCA_m = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
HPCA_tot = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
HPCA = h.Vector().record(ad(0.5)._ref_HPCA_hpca2)

# RUN THE SIMULATIONS!
for diam in diameters:
    ad.diam = diam
    for f in freqs:
        train_stim.per = 1000/f
        for no_pulses in N:
            train_stim.num = no_pulses # number of current pulses

            run()

            CaB_tot =  CaBuffer #+ (HPCA_tot - HPCA) + Ca2HPCA
            # converting Vectors() from NEURON to numpy vectors
            HPCA, HPCA_tot = np.array(HPCA), np.array(HPCA_tot)
            HPCA_m_base = np.min(HPCA/HPCA_tot)
            fig, axs = plt.subplots(3, 2, figsize=(20, 15), dpi=150)
            axs[0, 0].plot(t/1000, ipulses, label='Injected current')
            axs[0, 0].set(ylabel='nA')
            axs[0, 0].legend()
            axs[1, 0].plot(t/1000, Cai*10**6, color='green', label='$[Ca^{2+}]_i$')
            axs[1, 0].set(ylabel='nM')
            axs[1, 0].legend()
            axs[0, 1].plot(t/1000, 100*HPCA_m/HPCA_tot, color='red', label='$HPCA/HPCA_T$')
            axs[0, 1].legend()
            axs[0, 1].set(ylabel='%')
            axs[1, 1].plot(t/1000, ICa_pmp*1000, color='black', label='$Ca^{2+}$-Pump current ')
            axs[1, 1].set(ylabel='pA/pF')
            axs[1, 1].legend()
            axs[2, 0].plot(t/1000, CaB_tot*10**3, color='green', label='$[CaB]$')
            axs[2, 0].set(ylabel='$\mu$M', xlabel = 'time [s]')
            axs[2, 0].legend()
            axs[2, 1].plot(t/1000, ICa*1000, color='black', label='$Ca^{2+}$-Total current ')
            axs[2, 1].set(ylabel='pA/pF', xlabel='time [s]')
            axs[2, 1].legend()

            freq = int(f) # ms
            diam = int(ad.diam) # um
            #plt.show()
            filename = "ipulses_%sHz_n%s_diam%sum.pdf" % (freq, no_pulses, diam)
            fig.savefig(work_dir + filename)

