import matplotlib.pyplot as plt
from matplotlib import cm
import pickle
import numpy as np
import pandas as pd
from scipy.optimize import curve_fit
plt.style.use('seaborn-whitegrid')


with open("results4.p", "rb") as f:
    data = pickle.load(f)
    t = data["t"]
    v = data["v"]
    i_soma = data["i_soma"]

fig, axs = plt.subplots(2, 1, dpi=150)
axs[0].plot(t, v, 'k-')
axs[0].set_title('$V_m$ in the soma',  fontsize=14)
axs[0].set_ylabel('mV', fontsize=14)
axs[1].plot(t, i_soma*10**3, 'r-')
axs[1].set_ylim((-70, 70))
axs[1].set_xlabel('time (ms)', fontsize=14)
axs[1].set_ylabel('$\\frac{\mu A}{cm^2}$', fontsize=14).set_rotation(0)
axs[1].set_title('Сurrent in the soma', fontsize=14)

plt.tight_layout()
#plt.savefig('../../Diplom/images/charge_example.png')
plt.show()
