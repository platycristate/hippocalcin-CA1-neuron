import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('seaborn-whitegrid')


df = pd.read_csv('reproducing-experiments/12Apr2021/hpca_ipulses_soma.csv' ,
        usecols=['#APs', 'Translocation'])

df['Translocation2'] = \
pd.read_csv('reproducing-experiments/12Apr2021/ncald_ipulses_soma.csv', 
        usecols=['Translocation'])

print(df)
plt.figure(dpi=150)
plt.plot(df['#APs'], df['Translocation'], label='HPCA', color='black')
plt.plot(df['#APs'], df['Translocation2'], label='NCALD', color='red')
plt.legend()
plt.xlabel('No. of APs')
plt.ylabel('Max. transloc.')
plt.savefig('reproducing-experiments/12Apr2021/ncald_hpca_ipulses_soma.pdf')
plt.show()

