#! /bin/bash

n=100

if [ $# -eq 1 ]
then
    n=$1
fi

for ((i = 1; i <= $n; i++))
do
    echo "i=$i"
    ./a.out
done
