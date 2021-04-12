import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
from scipy.optimize import curve_fit
plt.style.use('seaborn-whitegrid')

'''
Kinetic characterization of the Ca L-current for hippocampal pyramidal neurons
(Poirazi et al, 2003; Magee and Johnston, 1995)
'''

V = np.arange(-100, 40, 5)

def alpha_m(V):
    return -0.055 * (V + 27.01)/((np.exp(-(V+27.01))/3.8) - 1) 

def beta_m(V):
    return 0.94*np.exp(-(V + 63.01)/17)

def m_inf(V):
    return alpha_m(V)/(alpha_m(V) + beta_m(V))

def tau_m(V):
    return 1/(5*(alpha_m(V) + beta_m(V)))

fig, axs = plt.subplots(1, 2, figsize=(14, 8), dpi=150)

axs[0].plot(V, m_inf(V), color='red', lw=1.8)
axs[0].set_title('$m_{\infty}$', fontsize=16)
axs[0].set_xlabel('Мембранний потенціал (мВ)', fontsize=14)

axs[1].plot(V, tau_m(V), color='black', lw=1.8)
axs[1].set_title('$\\tau_{m}$', fontsize=16)
axs[1].set_xlabel('Мембранний потенціал (мВ)', fontsize=14)
axs[1].set_ylabel('мілісекунди', fontsize=14)

fig.tight_layout()
plt.show()
