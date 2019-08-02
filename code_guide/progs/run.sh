#! /bin/bash

n=100

if [ $# -eq 1 ]
then
    n=$1
fi

[ ! -e "a.out" ] && echo "a.out not exist!" && exit 1

for ((i = 1; i <= $n; i++))
do
    echo "i=$i"
    ./a.out
done
