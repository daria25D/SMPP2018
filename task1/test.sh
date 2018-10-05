#!/bin/bash
Af=$1
Bf=$2
Cf=$3

## не генерировать новые матрицы, сгенерировать их заранее, а потом запускать на них тесты
#
g++ -g compare.cpp -o compare
g++ -g print.cpp -o print

#generate C to compare?
T0=$(./multimatrix $Af $Bf ./test/C0.dat 0) 
C0=$(./compare $Cf ./test/C0.dat)
T1=$(./multimatrix $Af $Bf ./test/C1.dat 1)
C1=$(./compare $Cf ./test/C1.dat)
T2=$(./multimatrix $Af $Bf ./test/C2.dat 2)
C2=$(./compare $Cf ./test/C2.dat)
T3=$(./multimatrix $Af $Bf ./test/C3.dat 3)
C3=$(./compare $Cf ./test/C3.dat)
T4=$(./multimatrix $Af $Bf ./test/C4.dat 4)
C4=$(./compare $Cf ./test/C4.dat)
T5=$(./multimatrix $Af $Bf ./test/C5.dat 5)
C5=$(./compare $Cf ./test/C5.dat)

echo -e $C0" (0 and 0)\n"$C1" (0 and 1)\n"$C2" (0 and 2)\n"$C3" (0 and 3)\n"$C4" (0 and 4)\n"$C5" (0 and 5)\n" > $4
echo -e "time:" $T0 $T1 $T2 $T3 $T4 $T5 "\n" >> $4
#./print ./test/C0.dat > C.txt
