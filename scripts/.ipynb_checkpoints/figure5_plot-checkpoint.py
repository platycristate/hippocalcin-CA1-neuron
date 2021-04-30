import matplotlib.pyplot as plt 
from matplotlib import cm 
import pickle 
import numpy as np
import pandas as pd
from scipy.optimize import curve_fit

plt.style.use('seaborn-whitegrid')
f = pd.read_csv('results5.csv')
f2 = pd.read_csv('results5_2.csv')
f3 = pd.read_csv('results5_3.csv')
f4 = pd.read_csv('results5_4.csv')

temp_f = f.drop_duplicates(subset='n_ap', keep='last')
new_f = temp_f.sort_values(by = 'n_ap')
temp_f2 = f2.drop_duplicates(subset='n_ap', keep='last')
new_f2 = temp_f2.sort_values(by = 'n_ap')
temp_f3 = f3.drop_duplicates(subset='n_ap', keep='last')
new_f3 = temp_f3.sort_values(by = 'n_ap')
temp_f4 = f4.drop_duplicates(subset='n_ap', keep='last')
new_f4 = temp_f4.sort_values(by = 'n_ap')

def sigmoid(x, L ,x0, k, b):
    y = -L / (1 + np.exp(-k*(x-x0)))+b
    return y

p0 = [max(new_f["ratio"]), np.median(new_f["n_ap"]), 1, min(new_f["ratio"])] # this is an mandatory initial guess
p02 = [max(new_f2["ratio"]), np.median(new_f2["n_ap"]), 1, min(new_f2["ratio"])] # this is an mandatory initial guess
p03 = [max(new_f3["ratio"]), np.median(new_f3["n_ap"]), 1, min(new_f3["ratio"])] # this is an mandatory initial guess
p04 = [max(new_f4["ratio"]), np.median(new_f4["n_ap"]), 1, min(new_f4["ratio"])] # this is an mandatory initial guess

popt, pcov = curve_fit(sigmoid, new_f["n_ap"], new_f["ratio"], p0, method='dogbox')
popt2, pcov2 = curve_fit(sigmoid, new_f2["n_ap"], new_f2["ratio"], p02, method='dogbox')
popt3, pcov3 = curve_fit(sigmoid, new_f3["n_ap"], new_f3["ratio"], p03, method='dogbox')
popt4, pcov4 = curve_fit(sigmoid, new_f4["n_ap"], new_f4["ratio"], p04, method='dogbox')

plt.figure(dpi=150, figsize=(8, 8))

plt.plot(new_f["n_ap"], new_f["ratio"], "bo", markersize=4, label="C=0.1")
plt.plot(new_f["n_ap"], sigmoid( new_f["n_ap"], *popt), 'r-', lw=1.2, label="фітування для С=0.1")
plt.plot(new_f2["n_ap"], new_f2["ratio"], "go", markersize=4, label="C=0.2")
plt.plot(new_f2["n_ap"], sigmoid( new_f2["n_ap"], *popt2), 'k-', lw=1.2, label="фітування для С=0.2")
plt.plot(new_f3["n_ap"], new_f3["ratio"], "yo", markersize=4, label="C=0.05")
plt.plot(new_f3["n_ap"], sigmoid( new_f3["n_ap"], *popt3), '-', lw=1.2, label="фітування для С=0.05")
#plt.plot(new_f4["n_ap"], new_f4["ratio"], "o", markersize=4, label="C=0.01")
#plt.plot(new_f4["n_ap"], sigmoid( new_f4["n_ap"], *popt3), '-', lw=1.2, label="фітування для С=0.01")
plt.legend(fontsize=11)

plt.xlabel("Кількість потенціалів дії", fontsize=14)
plt.ylabel("$Q/Q_0$", fontsize=14, labelpad=20).set_rotation(0)
plt.tight_layout()
plt.savefig('../../Diplom/images/n_ap_charge.png')
plt.show()
