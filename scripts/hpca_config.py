'''
Config file for hpca_compartment.py file. This
files contains important parameters of the model
'''

import os
import gc
import sys
import pickle
import numpy as np

from NeuroTools.parameters import Parameter

params = { 'working_dir': 'reproducing-experiments/12Apr2021/', 
           'filename': 'ipulses100_diam_dependence.pdf',
        'Simulation':
        {
            'duration': Parameter(8000, "ms"),
            'dep_loc': Parameter('h.apical_dendrite[7](.5)'),
            'dep_dur': Parameter(2000, "ms"),
            '#spikes': Parameter(100), 
            'dt': Parameter(0.1, 'ms'),
            'section':Parameter('h.apical_dendrite[7]')
        },
        'HPCA':
        {
            # Cytosol buffer
            'Buffer0': Parameter(0.180, "mM"),
            'k1B': Parameter(142, "/mM*ms"), #142 # Kd = 0.5 uM
            'k2B': Parameter(0.1, "/ms"),

             # Ca2+ATPase
             'Pump0': Parameter(5e-12 * 1.5 , "mol/cm2"),
             'k1P': Parameter(1, "/mM*ms"),
             'k2P': Parameter(0.0003, "/ms"),
             'k3P': Parameter(1, "/ms"),
             'k4P': Parameter(0.0003, "/mM*ms"),

             # HPCA 
             'HPCA0': Parameter(0.03, "mM"),
             'k_out': Parameter(0.002, "/ms"),

             # initial Ca2+
             'Ca_i': Parameter(3000*10**(-6), "mM"),

             # calcium diffusion coefficient
             'DCa': Parameter(0.22, "um2/ms")
         },
        'NCALD':
        {
            # 12 s tau_out for neurocalcin
            'k_out': Parameter(1/12000, "/ms")
        },
        'CaL':
        {
            'gcalbar_dendrite': Parameter(0.0015 / 10 , 'S/cm2') # 0.0015
        },
        'CaT':
        {
            'gcatbar_dendrite': Parameter(0.001, 'S/cm2')
        },
        'Neuron':
        {
            'diam': Parameter(1.5, 'um'),
            'length': Parameter(20, 'um')
        }
    }
