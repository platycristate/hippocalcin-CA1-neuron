#________________________________________INPUT___________________________________
depolar_durations = [100, 250, 500, 1000, 2000, 4000] # ms
freqs = [10, 20, 50] # Hz
diameters = [1, 2, 4] # um



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

font = {'family' : 'Helvetica',
        'weight' : 'normal',
        'size'   : 12}

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

# Creating SEClamp (ideal voltage clamp) object
sc = seclamp_stim( eval(params['Simulation']['dep_loc'].value) )
sc.dur2 = 4000 # ms
sc.dur1 = 1000

#_______________________________CREATING RECORDING's VECTORS____________________________

t = h.Vector().record(h._ref_t)

# Calcium currents
ICa = h.Vector().record(ad(.5)._ref_ica)
ICa_pmp = h.Vector().record(ad(0.5)._ref_ica_pmp_hpca2)

clamp_v = h.Vector().record(sc._ref_vc)

# [CaB] and [Ca2+]
Cai = h.Vector().record(ad(0.5)._ref_cai)
CaBuffer = h.Vector().record(ad(0.5)._ref_CaBufer_hpca2)
CaHPCA = h.Vector().record(ad(0.5)._ref_CaHPCA_hpca2)
Ca2HPCA = h.Vector().record(ad(0.5)._ref_Ca2HPCA_hpca2)
HPCA_m = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
HPCA_tot = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
HPCA_tot_mM = params['HPCA']['HPCA0'].value
HPCA = h.Vector().record(ad(0.5)._ref_HPCA_hpca2)

sc.dur2 = 500
# RUN THE SIMULATIONS!
for diam in diameters:
    ad.diam = diam
    for duration in depolar_durations:
        sc.dur2 = duration

        run()
        CaB_tot =  CaBuffer + (HPCA_tot_mM - HPCA) + Ca2HPCA
        # converting Vectors() from NEURON to numpy vectors
        fig, axs = plt.subplots(3, 2, figsize=(15, 15), dpi=150)
        axs[0, 0].plot(t/1000, clamp_v, label='Clamp Voltage')
        axs[0, 0].set(ylabel='mV')
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
        fig  = plt.figure(dpi=150, figsize=(8,6))
#plt.plot(t/1000, 100*HPCA_m/HPCA_tot, color='red', label='$HPCA/HPCA_T$')
#plt.legend()
#plt.ylabel('%')
#dep_dur = int(sc.dur2) # ms
#diam = int(ad.diam) # um
#filename = 'hpca_dep_%sms_sim.png' % dep_dur
#plt.show()
filename = "depolar_%sms_diam%sum.png" % (dep_dur, diam)
fig.savefig(work_dir + filename)

