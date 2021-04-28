import matplotlib.pyplot as plt 
from matplotlib import cm 
import pickle 
import numpy as np
import pandas as pd
from scipy.optimize import curve_fit

plt.style.use('seaborn-whitegrid')


f = pd.read_csv('results3.csv')

def func(x, a, b, c):
    return a*np.exp(b*x) + c

popt, _ = curve_fit(func, f["C"], f["ratio"])


plt.figure(dpi=150, figsize=(8, 8))
plt.plot(f["C"], f["ratio"], "bo", markersize=4)
plt.plot(f["C"], func( f["C"], *popt), 'r-', lw=1.2)
plt.xlabel("С", fontsize=16)
plt.ylabel("$Q/Q_0$", fontsize=15, labelpad=10).set_rotation(0)
plt.tight_layout()
plt.savefig('../../Diplom/images/C_charge.png')
plt.show()

