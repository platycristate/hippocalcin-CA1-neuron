from random import randint, uniform, seed 
from neuron import h 
from neuron.units import ms, mV
import matplotlib.pyplot as plt 
from matplotlib import cm 
import numpy as np 
import os 
import pickle
from instrumentation import * 
from hpca_config import *
from Synapse import Synapse

plt.style.use('seaborn-whitegrid')
work_dir = params['working_dir'] 
if not os.path.exists(work_dir):
    print(work_dir)
    os.makedirs(work_dir)
#_________________________________INITIALIZATION___________________________________________

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

h.C_hpca2 = 0.1
h.TotalHPCA_hpca2 = 0.03

ic = h.IClamp(h.soma[0](.5))
ic.delay = 100 * ms
ic.dur = 100 * ms
ic.amp = 0.420 # nA  = 100 pa

t = h.Vector().record(h._ref_t)
v = h.Vector().record(h.soma[0](.5)._ref_v)
apc = h.APCount(h.soma[0](0.5))
apc.thresh = -15 * mV
#-------------------------------FIRST PART-------------------------------------------
amplitudes = np.arange(0.05, 0.8, 0.05)

NOfSpikes = []
sAHP_max_amps = []
for amp in amplitudes:
    ic.amp = amp
    print("amplitude", amp)
    run(dur=1500, v_init=-66)
    NOfSpikes.append(apc.n)
    # maximal amplitude of sAHP
    sAHP_max_amps.append(np.array(v)[3] - np.array(v).min())

with open(params['working_dir'] + 'sAHP_nSpikes.p', 'wb') as f:
    pickle.dump({'NOfSpikes': NOfSpikes, 'sAHP_max_amps': sAHP_max_amps}, f)


plt.figure(dpi=150)
plt.plot(NOfSpikes, sAHP_max_amps, 'ko-')
plt.xlabel('Кількість ПД')
plt.ylabel('$\Delta $sAHP (мВ)')
plt.savefig(params['working_dir'] + 'sAHP_nSpikes.pdf')
plt.show()

#-----------------------------------SECOND PART----------------------------------
vm_traces = []
amplitudes = [0.2, 0.4, 0.5]
for amp in amplitudes:
    ic.amp = amp
    run(12000, v_init=-66)
    vm_traces.append(np.array(v))

with open(params['working_dir'] + 'sAHP_Vm_traces.p', 'wb') as f:
    pickle.dump({'vm_traces': vm_traces, 'dt': 0.1}, f)

plt.figure(dpi=150)
for i, vm in enumerate(vm_traces):
    plt.plot(t, vm, label=amplitudes[i])
plt.xlabel('Час, с')
plt.ylabel('Мембранний потенціал (мВ)')
plt.legend(title='Амп. струму, нА')
plt.savefig(params['working_dir'] + 'sAHP_vm_traces.pdf')
plt.show()
