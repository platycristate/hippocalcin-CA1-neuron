'''
I will try to reproduce Hofman_traces.hoc using Python interface.
I am just doing it for the sake of learning HOC and interfacing NEURON with Python
'''


from neuron import h
from neuron.units import mV, ms
import matplotlib.pyplot as plt
import numpy as np
import pickle
import os

plt.style.use('seaborn-whitegrid')
# to change default colormap
plt.rcParams["image.cmap"] = "Dark2"
# to change default color cycle
plt.rcParams['axes.prop_cycle'] = plt.cycler(color=plt.cm.Dark2.colors)

experiment_title = 'Hofman/'
general_path = 'reproducing-experiments/' + experiment_title
if not os.path.exists(general_path):
	os.mkdir(general_path)
	os.mkdir(general_path + 'control/')
	os.mkdir(general_path + 'A-blocked/')
	os.mkdir(general_path + 'A-Ca-blocked/')

h.load_file('nrngui.hoc')
h.load_file("template/load_templates.hoc")

show_errs=1
debug_lev=1
econ=h.ExperimentControl(show_errs,debug_lev)
econ.self_define(econ)
econ.morphology_dir = "morphology/n123"        # Setup morphology directory
econ.generic_dir = "experiment/"               # Setup directory with cell-setup file
econ.add_lib_dir("Terrence","lib")             # Setup directory with library functions 

econ.data_dir = 'reproducing-experiments'      # directory to save produced data

# Setup cell
econ.xopen_geometry_dependent("cell")          # load the raw cell morphologe
econ.xopen_geometry_dependent("cell-analysis") # load user-defined semantics on morphology
h.cell_analysis(econ)

print('Opening cell setup \n')
econ.xopen_generic("cell-setup")               # define specific channels, membrane properties etc.
print('Opened. Setting up the cell \n')   
h.cell_setup(econ)


# Set simulation parameters for the experiment
tstop = 300 * ms
h.dt = 0.1 * ms

# Procedures for the different experimental cases to be tested
def Ca_block():
	'''
	Block all Ca2+ conductances by 75%
	'''
	f = 0.25 
	for section in h.allsec():
		if h.ismembrane('cat', sec=section):
			for seg in section.allseg():
				seg.gcatbar_cat *= f
		if h.ismembrane('cal', sec=section):
			for seg in section.allseg():
				seg.gcalbar_cal *= f
		if h.ismembrane('calH', sec=section):
			for seg in section.allseg():
				seg.gcalbar_calH *= f
		if h.ismembrane('somacar', sec=section):
			for seg in section.allseg():
				seg.gcabar_somacar *= f
		if h.ismembrane('car', sec=section):
			for seg in section.allseg():
				seg.gcabar_car *= f

def A_block():
	'''
	block all conductances through AP K+ channels
	'''
	f = 0
	for section in h.allsec():
		if h.ismembrane('kap', sec=section): # proximal conductances
			for seg in section.allseg():#np.linspace(0, 1, section.nseg):
				seg.gkabar_kap *= f
		if h.ismembrane('kad', sec=section): # distal conductances
			for seg in section.allseg():#np.linspace(0, 1, section.nseg):
				seg.gkabar_kad *= f
data_dir = 'reproducing-experiments/Hofman'        

# Insert current clamp into soma or dendritic section
ic = h.IClamp(h.soma[0](0.5))
ic.delay = 140 * ms
ic.dur = 50   * ms
ic.amp = 0.3  # nA

# Setting up measurement vectors
ic_curr = h.Vector().record(ic._ref_i)
soma_v = h.Vector().record(h.soma[0](0.5)._ref_v)
dend_v = h.Vector().record(h.apical_dendrite[65](0.5)._ref_v)
t = h.Vector().record(h._ref_t)



# ----------------------- Initialize and run experiment ---------------------------

# Control

h.fcurrent() # Make all currents, conductances etc. consistent with state variables
h.finitialize(h.v_init)
h.continuerun(tstop)

# saving results of control experiment
with open(general_path + 'control/' + 'control.p', 'wb') as f:
	pickle.dump({'t': t, 'soma_v': soma_v, 'dend65_v': dend_v}, f)
# Blocked A-type K+ conductance
A_block()
h.fcurrent() # Make all currents, conductances etc. consistent with state variables
h.finitialize(h.v_init)
h.continuerun(tstop)


with open(general_path + 'A-blocked/' + 'A-blocked.p', 'wb') as f:
	pickle.dump({'t': t, 'soma_v': soma_v, 'dend65_v': dend_v}, f)
# Blocked A-type K+ conductance and Ca2+ channels
Ca_block()

h.fcurrent() # Make all currents, conductances etc. consistent with state variables
h.finitialize(h.v_init)
h.continuerun(tstop)


with open(general_path + 'A-Ca-blocked/' + 'A-Ca-blocked.p', 'wb') as f:
	pickle.dump({'t': t, 'soma_v': soma_v, 'dend65_v': dend_v}, f)
# Now, lets make some plots and also check whether we made our saving correctly

with open(general_path + 'control/control.p', 'rb') as f:
	control = pickle.load(f)
time = control['t']
soma_v_control = control['soma_v']
dend_v_control = control['dend65_v']

with open(general_path + 'A-blocked/A-blocked.p', 'rb') as f:
	A_blocked = pickle.load(f)

soma_v_A_blocked = A_blocked['soma_v']
dend_v_A_blocked = A_blocked['dend65_v']

with open(general_path + 'A-Ca-blocked/A-Ca-blocked.p', 'rb') as f:
	A_Ca_blocked = pickle.load(f)

soma_v_A_Ca_blocked = A_Ca_blocked['soma_v']
dend_v_A_Ca_blocked = A_Ca_blocked['dend65_v']


fig, axs = plt.subplots(4, 1, figsize=(8, 8))
axs[0].plot(time, soma_v_control, label='soma')
axs[0].plot(time, dend_v_control, label='dendrite')
axs[0].set_title('Control')

axs[1].plot(time, soma_v_A_blocked, label='soma')
axs[1].plot(time, dend_v_A_blocked, label='dendrite')
axs[1].set_title('Blocked A-type K+ conductance')

axs[2].plot(time, soma_v_A_Ca_blocked, label='soma')
axs[2].plot(time, dend_v_A_Ca_blocked, label='dendrite')
axs[2].set_title('Blocked A-type K+ conductance and 75% of Ca2+ conductance')


axs[3].plot(time, ic_curr)
axs[3].set(xlabel='time [ms]', ylabel='nA')

for i in range(len(axs)):
	axs[i].set_xlim([100, 250])
	axs[i].legend()
	
plt.tight_layout()
fig.savefig(general_path + 'Hofman.pdf')

