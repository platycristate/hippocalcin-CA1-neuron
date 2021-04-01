from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
import numpy as np
import os
import pickle
from hpca_config import params

colors = plt.rcParams["axes.prop_cycle"]()

def initialize():
    h.load_file('nrngui.hoc');
    h.load_file("../template/load_templates.hoc");
    show_errs=1
    debug_lev=1
    econ=h.ExperimentControl(show_errs,debug_lev);
    econ.self_define(econ) ;
    econ.morphology_dir = "../morphology/n123"        # Setup morphology directory
    econ.generic_dir = "../experiment/"               # Setup directory with cell-setup file
    econ.add_lib_dir("Terrence","../lib");             # Setup directory with library functions
    econ.data_dir = '../reproducing-experiments'      # directory to save produced data
    # Setup cell
    econ.xopen_geometry_dependent("cell");          # load the raw cell morphology
    econ.xopen_geometry_dependent("cell-analysis"); # load user-defined semantics on morphology
    h.cell_analysis(econ);
    econ.xopen_generic("cell-setup");               # define specific channels, membrane properties etc.
    print('Opened. Setting up the cell \n');
    h.cell_setup(econ);
    return econ

def run(dur=None):
    # Set simulation parameters for the experiment
    # initialization
    h.finitialize(h.v_init);
    h.dt = params['Simulation']['dt'].value
    h.t = -5000
    # if cvode is on, turn it off to do large fixed step
    temp = h.cvode.active()
    if temp != 0:
        h.cvode.active(0)
    while h.t < -1000:
        h.fadvance()

    # restoring cvode
    if temp != 0:
        h.cvode.active(1)
    h.t = 0
    if h.cvode.active():
        h.cvode.re_init()
    else:
        h.fcurrent()
    h.frecord_init()
    if dur:
        h.continuerun(dur)
    else:
        h.continuerun( params['Simulation']['duration'].value );

def select_section(my_sec):
    for section in h.allsec():
        if my_sec != section:
            h.delete_section(sec=section)
    return my_sec

def trains_stim( loc, n=params['Simulation']['#spikes'].value,
        amp=35, delay=1000, per=20, dur=0.1):
    ic = h.Ipulse2(loc)
    ic.delay = delay
    ic.dur = dur #ms
    ic.per = per #ms
    ic.amp = amp #nA
    ic.num = n
    return ic

def seclamp_stim(loc, dur1=1000, dur2=params['Simulation']['dep_dur'].value,
        dur3=20000, v0=-70, v1=0):
    sc = h.SEClamp( loc )
    sc.dur1 = dur1
    sc.dur2 = dur2
    sc.dur3 = dur3
    sc.amp1 = sc.amp3 = -70 * mV
    sc.amp2 = 0 * mV
    return sc

def hpca_plot(t, *args, title=None):
    no_plots = len(args)
    fig, axs = plt.subplots(no_plots, figsize=(8, no_plots*5))
    for i, ar in zip(range(no_plots), args):
        c = next(colors)["color"]
        axs[i].plot(t/1000, ar[0], label=ar[1], color=c)
        axs[i].legend()
    axs[no_plots-1].set(xlabel='time [s]')
    if title:
        fig.suptitle(title)
    plt.show()
    return fig, axs
