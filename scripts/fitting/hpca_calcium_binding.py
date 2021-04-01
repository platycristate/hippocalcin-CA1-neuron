import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


def experimental_curve(Ca, n=1.4, Kd=1):
    return (Ca**n/Kd) / (1 + Ca**n/Kd) 

def experimental_curve2(Ca, n=1.4):
    return (Ca**n)/(1 + (Ca**n))


def analytical_curve(Ca, K1, K2):
    return (Ca**2/(K1*K2))/(1 + Ca**2/(K1*K2))

Ca = np.arange(0, 2, 0.0001)
exp_curve = experimental_curve(Ca)

popt, pcov = curve_fit(analytical_curve, Ca, exp_curve)
print(popt)

plt.plot(Ca, experimental_curve(Ca), label='experimental')
#plt.plot(Ca, analytical_curve(Ca, K1=popt2[0], K2=popt2[1]), label='analytical')
plt.plot(Ca, analytical_curve(Ca, K1=popt[0], K2=popt[1]), label='analytical2')
plt.legend()
plt.xlabel('[Ca2+]')
plt.ylabel('HPCA-2Ca/HPCA')
plt.title('Hill equation')
plt.show()
