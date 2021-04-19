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
plt.style.use('dark_background')

NumSpikes = pd.read_csv(params['working_dir'] + 'Spikes_current_amplitudes.csv')

for colName in NumSpikes.columns[2:]:
    print( 'Concentration:', colName)
    plt.plot(NumSpikes['Amps, nA'], NumSpikes[colName], 'o-', label=colName)

plt.xlabel('Амплітуда струму, нА')
plt.ylabel('Кількість ПД')
plt.title('Кількість ПД за 800 мс стимуляції струмом')
plt.legend(title='[HPCA], мкмM')
plt.savefig(params['working_dir'] + 'Spikes_current_amplitudes.pdf')
plt.show()

