#>results5_2.csv
for i in $(seq 62 1 350)
do
    python3 figure5_calc.py $i | cat | tail -n1  >> results5_5.csv
done
    
