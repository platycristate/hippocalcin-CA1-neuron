#results3_3.csv
for i in $(seq 0.01 0.001 0.1)
do
    python3 figure3_calc.py $i | cat | tail -n1  >> results3_3.csv
done
    
