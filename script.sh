#!/bin/bash
TYPEA=$1
NA=$2
MA=$3
TYPEB=$4
NB=$5
MB=$6
OUT=$7

mkdir -p report
g++ -g  generate.cpp -o generate
g++ -g multimatrix.cpp -o multimatrix
./generate $TYPEA $NA $MA ./report/A.dat
./generate $TYPEB $NB $MB ./report/B.dat
./multimatrix ./report/A.dat ./report/B.dat ./report/C0.dat 0 >> $OUT
./multimatrix ./report/A.dat ./report/B.dat ./report/C1.dat 1 >> $OUT
./multimatrix ./report/A.dat ./report/B.dat ./report/C2.dat 2 >> $OUT
./multimatrix ./report/A.dat ./report/B.dat ./report/C3.dat 3 >> $OUT
./multimatrix ./report/A.dat ./report/B.dat ./report/C4.dat 4 >> $OUT
./multimatrix ./report/A.dat ./report/B.dat ./report/C5.dat 5 >> $OUT  
printf "\n" >> $OUT
#gnuplot -e "set terminal svg size 600,500; set output './report/$FILE'; set title '$TITLE'; 
#set xtics ('ijk' 0, 'ikj' 1, 'kij' 2, 'jik' 3, 'jki' 4, 'kji' 5); 
#set xrange [0:5]; plot 'time.txt' with lines"

