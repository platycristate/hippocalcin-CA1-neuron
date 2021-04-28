#>results5_2.csv
for i in $(seq 10 1 150)
do
    python3 figure5_calc.py $i | cat | tail -n1  >> results5_2.csv
done
    
