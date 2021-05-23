from random import seed, randint
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
    os.makedirs(work_dir)

#_________________________________INITIALIZATION___________________________________________

econ = initialize() # initialize pyramidal CA1 neuron from Poirazi 2003
ad = eval(params['Simulation']['section'].value)
for s in h.allsec():
    mechs = s.psection()['density_mechs'].keys()
    s.uninsert('kca')
    if h.ismembrane('hha2'):
        for seg in s:
            print(seg.hha2.gkbar)
            seg.hha2.gkbar = params['HH_IK']['gkbar_soma'].value
    if 'hha_old' in mechs:
        for seg in s:
            print(seg.hha_old.gkbar)
            seg.hha2.gkbar = params['HH_IK']['gkbar_dend'].value
    if 'apical_dendrite' in str(s) or 'soma' in str(s):
        s.uninsert('cad')
        s.insert('hpca2')
        s.uninsert('car')
        s.insert('cal')
        for seg in s:
            seg.cal.gcalbar = params['CaL']['gcalbar_dendrite'].value


h.cai0_hpca2 = params['HPCA']['Ca_i'].value
c = 0.2
h.C_hpca2 = c
h.TotalHPCA_hpca2 = 0.03

central = [6, 4, 0, 2, 5, 7, 2, 1]

seed(2489)

distal = [randint(50, 80) for i in range(10)]

Synapse.gmax_AMPA /= len(central)
Synapse.gmax_NMDA /= len(central)
central_synapses = []

for i in central:
    central_synapses.append( Synapse(h.apical_dendrite[i](.5)) )
print(central_synapses[1].GluSyn.gmax_AMPA)

Synapse.setup_gmax(
    gmax_AMPA_new=0.001 * 80, 
    gmax_NMDA_new = 0.001 * 0.7 * 80
    )

Synapse.gmax_AMPA /= len(distal)
Synapse.gmax_NMDA /= len(distal)
distal_synapses = []

for i in distal:
    distal_synapses.append( Synapse(h.apical_dendrite[i](.5)) )

central_times = [i for i in range(100, 800, 150)]
distal_times = [i for i in range(1200, 1800, 50)]

stim_central = Synapse.create_stim(central_synapses)
stim_distal = Synapse.create_stim(distal_synapses)

Synapse.play_stimulation(stim_central, central_times)
Synapse.play_stimulation(stim_distal, distal_times)

Synapse.plot_synapses_locs([central_synapses, distal_synapses], colors=['y', 'r'])
plt.show()

t = h.Vector().record(h._ref_t)
hpca = h.Vector().record(ad(0.5)._ref_HPCA_m_z_hpca2)
tot_hpca = h.Vector().record(ad(.5)._ref_HPCA_tot_z_hpca2)
ik_sahp = h.Vector().record(ad(.5)._ref_ik_hpca2)
v = h.Vector().record(h.soma[0](.5)._ref_v)
v_dend = h.Vector().record(h.apical_dendrite[6](.5)._ref_v)
v_dend2 = h.Vector().record(h.apical_dendrite[110](.5)._ref_v)

run(2000, v_init=-62)
fig, axs = plt.subplots(3, 1, dpi=150)
axs[0].plot(t, v_dend)
axs[0].set(ylabel='mV')
axs[1].plot(t, v_dend2)
axs[1].set(ylabel='mV')
axs[2].plot(t, v)
axs[2].set(xlabel='time [ms]', ylabel='mV')
#plt.savefig(params['working_dir'] + 'distal_bef_proximal.pdf')
plt.show()

with open('c2.p', 'wb') as f:
    pickle.dump({'t': t, 'c2_v':v}, f)

fig.tight_layout()
plt.show()
#plt.savefig('../../Diplom/images/signal.png')
plt.show()
