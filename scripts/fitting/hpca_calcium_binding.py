import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
from scipy.optimize import curve_fit
plt.style.use('seaborn-whitegrid')



def experimental_curve(Ca, n=1.4, Kd=1):
    return (Ca**n/Kd**n) / (1 + Ca**n/Kd**n) 

def analytical_curve(Ca, K1=0.6666, K2=0.6):
    return (Ca**2/(K1*K2))/(1 + (Ca/K1) + Ca**2/(K1*K2))

Ca = np.arange(0, 4, 0.0001)
exp_curve = experimental_curve(Ca)

plt.figure(dpi=150)
plt.scatter([1], [0.5])
plt.plot(Ca, experimental_curve(Ca), color='black', lw=0.8, label='експериментальна')
plt.plot(Ca, analytical_curve(Ca), color='red', lw=0.8, label='аналітична')
plt.legend(title='Функція')
plt.xlabel('$[Ca^{2+}]$ мкМ', fontsize=15)
plt.ylabel('$\\theta$', fontsize=20).set_rotation(0)
plt.title('Функції Хілла')
plt.show()
