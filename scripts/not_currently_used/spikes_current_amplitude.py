from random import randint, uniform, seed
from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt 
from matplotlib import cm 
import numpy as np 
import os 
import pandas as pd
import pickle
from instrumentation import * 
from hpca_config import *
from Synapse import Synapse
plt.style.use('seaborn-whitegrid')

work_dir = params['working_dir'] 
if not os.path.exists(work_dir):
    os.makedirs(work_dir)


econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = eval(params['Simulation']['section'].value)

for s in h.allsec():
    s.uninsert('kca')
    s.uninsert('mykca')
    if 'apical_dendrite' in str(s):
        s.uninsert('cad')
        s.insert('hpca2')
        s.uninsert('car')
        s.insert('cal')
        for seg in s:
            seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value

h.cai0_hpca2 = params['HPCA']['Ca_i'].value
h.C_hpca2 = params['HPCA']['C'].value # transfer coefficinet of HPCAm/HPCatot to current amplitude

#____________________________________________________________________________________________
t = h.Vector().record(h._ref_t)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
ik_sahp = h.Vector().record(ad(.5)._ref_ik_hpca2)
v = h.Vector().record(h.soma[0](.5)._ref_v)

ic = h.IClamp(h.soma[0](.5))
ic.delay = 50 * ms
ic.dur = 800 * ms

APcounter = h.APCount(h.soma[0](0.5))
APcounter.thresh = -15 * mV
amplitudes = np.arange(0.1, 0.6, 0.05)

NumSpikes = pd.DataFrame()
NumSpikes['Amps, nA'] = amplitudes
HPCAconcs = [1, 0.3]

for HPCAconc in HPCAconcs:
    h.C_hpca2 = HPCAconc
    APcounts = []
    for amplitude in amplitudes:
        ic.amp = amplitude
        run(dur=1000)
        print(APcounter.n)
        APcounts.append(APcounter.n)
    NumSpikes['C=%s' % HPCAconc] = APcounts

NumSpikes.to_csv(params['working_dir'] + 'Spikes_current_amplitudes.csv')    
with open(params['working_dir'] + 'Spikes_current_amplitudes.p', 'wb') as f:
    pickle.dump({'NumSpikes': NumSpikes}, f)

# PLOTIING THE RESULTS
print(NumSpikes)
plt.figure(dpi=150)
for colName in NumSpikes.columns[1:]:
    print( 'C:', colName)
    plt.plot(NumSpikes['Amps, nA'], NumSpikes[colName], 'o-', label=colName)

plt.xlabel('Амплітуда струму, нА')
plt.ylabel('Кількість ПД')
plt.title('Кількість ПД за 800 мс стимуляції струмом')
plt.legend(title='C')
plt.savefig(params['working_dir'] + 'Spikes_current_amplitudes.pdf')
plt.show()
