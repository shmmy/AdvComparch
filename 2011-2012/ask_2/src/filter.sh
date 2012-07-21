a=`head -n $1 $2 | tail -n 1`
b=`head -n $3 $4 | tail -n 1`
echo $a > $2
echo $b >> $2
