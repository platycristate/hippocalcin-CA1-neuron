import matplotlib.pyplot as plt 
from matplotlib import cm 
import pickle 

plt.style.use('seaborn-whitegrid')


with open('c0.p', 'rb') as f:
    file_data = pickle.load(f)
    t = file_data['t']
    c0_v= file_data['c0_v']

with open('c1.p', 'rb') as f:
    file_data = pickle.load(f)
    c1_v= file_data['c1_v']

with open('c2.p', 'rb') as f:
    file_data = pickle.load(f)
    c2_v = file_data['c2_v']


fig, axs = plt.subplots(3, 1, figsize=(16, 10), dpi=150)

axs[0].plot(t, c0_v, color='black')
axs[0].set_title('C=0', fontsize=14)
axs[0].set_ylabel('мВ', fontsize=14)
axs[1].plot(t, c1_v, color='black')
axs[1].set_title('C=0.1', fontsize=14)
axs[1].set_ylabel('мВ', fontsize=14)
axs[2].plot(t, c2_v, color='black')
axs[2].set_title('C=0.2', fontsize=14)
axs[2].set_ylabel('мВ', fontsize=14)
axs[2].set_xlabel('Час (мс)', fontsize=14)

fig.tight_layout()
plt.savefig('../../Diplom/images/signal.png')
plt.show()
