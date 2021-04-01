from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
import numpy as np
import os
import pickle
from instrumentation import *
from hpca_config import *
h.load_file('nrngui.hoc')
work_dir = params['working_dir']
if not os.path.exists(work_dir):
    os.makedirs(work_dir)

soma = h.Section(name='soma')
soma.L = 30
diam = 3
soma.insert('hpca2')


h.TotalHPCA_hpca2 = params['HPCA']['Buffer0'].value
h.TotalPump_hpca2 = params['HPCA']['Pump0'].value
h.Bufer0_hpca2 = params['HPCA']['Buffer0'].value
h.k1bufer_hpca2 = params['HPCA']['k1B'].value
h.k2bufer_hpca2 = params['HPCA']['k2B'].value
h.k1Pump_hpca2 = params['HPCA']['k1P'].value
h.k2Pump_hpca2 = params['HPCA']['k2P'].value
h.cai0_hpca2 = params['HPCA']['Ca_i'].value
#h.DCa_hpca2 = params['HPCA']['DCa'].value
#h.tau_d_hpca2 = 0.01



t = h.Vector().record(h._ref_t)
ica = h.Vector().record(soma(.5)._ref_ica_pmp_hpca2)
cai = h.Vector().record(soma(0.5)._ref_cai)
#ca1 = h.Vector().record(soma(.5)._ref_ca1_hpca2)
#ca2 = h.Vector().record(soma(.5)._ref_ca2_hpca2)
hpca = h.Vector().record(soma(0.5)._ref_HPCA_m_hpca2)
tot_hpca = h.Vector().record(soma(.5)._ref_HPCA_tot_z_hpca2)

##########################################33
#constants2 = [i for i in np.linspace(0.00001, 0.0007, 100)]
#basal_ica = []
#
#for k2P in constants2:
#    h.k2Pump_hpca2 = k2P
#    h.finitialize()
#    h.continuerun(50 * ms)
#    basal_ica.append(np.array(ica).max() * 10**6)
#
#plt.plot(constants2, basal_ica)
#plt.ylabel('[Ca2+] nM')
#plt.xlabel('k2Pump (/mM*ms)')
#plt.show()
##############################################
h.finitialize()
h.continuerun(27000* ms)
print(cai[-1]*10**6, 'nM')
print(h.cao0_ca_ion)
fig, axs = hpca_plot(t,
        (ica, 'ica_pmp (mA/cm2)'),
        (cai*10**6, 'Ca[0] outermost shell (nM)')
        #(ca1*10**3, 'Ca[1] (uM)'),
                    )

#fig.savefig(work_dir + params['filename'])
