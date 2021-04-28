#results3.txt
for i in $(seq 0.6 0.02 1.0)
do
    python3 figure3_calc.py $i | cat | tail -n1  >> results3.txt 
done
    
