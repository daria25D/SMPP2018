#!/bin/bash
TYPEA=$1
NA=$2
MA=$3
TYPEB=$4
NB=$5
MB=$6

mkdir -p test
g++ -g  generate.cpp -o generate
g++ -g multimatrix.cpp -o multimatrix
g++ -g compare.cpp -o compare
g++ -g print.cpp -o print
./generate $TYPEA $NA $MA ./test/A.dat
./generate $TYPEB $NB $MB ./test/B.dat
#generate C to compare?
T0=$(./multimatrix ./test/A.dat ./test/B.dat ./test/C0.dat 0) 
T1=$(./multimatrix ./test/A.dat ./test/B.dat ./test/C1.dat 1)
C1=$(./compare ./test/C0.dat ./test/C1.dat)
T2=$(./multimatrix ./test/A.dat ./test/B.dat ./test/C2.dat 2)
C2=$(./compare ./test/C0.dat ./test/C1.dat)
T3=$(./multimatrix ./test/A.dat ./test/B.dat ./test/C3.dat 3)
C3=$(./compare ./test/C0.dat ./test/C1.dat)
T4=$(./multimatrix ./test/A.dat ./test/B.dat ./test/C4.dat 4)
C4=$(./compare ./test/C0.dat ./test/C1.dat)
T5=$(./multimatrix ./test/A.dat ./test/B.dat ./test/C5.dat 5)
C5=$(./compare ./test/C0.dat ./test/C1.dat)
echo -e $C1" (0 and 1)\n"$C2" (0 and 2)\n"$C3" (0 and 3)\n"$C4" (0 and 4)\n"$C5" (0 and 5)\n" > test.txt
echo -e "time:" $T0 $T1 $T2 $T3 $T4 $T5 "\n" >> test.txt
./print ./test/C0.dat > C.txt
