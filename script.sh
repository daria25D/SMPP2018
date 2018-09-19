#!/bin/bash
#CC=g++
#CFLAGS=-g -c
TYPEA=$1
NA=$2
MA=$3
TYPEB=$4
NB=$5
MB=$6

mkdir -p test
g++ -g  generate.cpp -o generate
g++ -g multimatrix.cpp -o multimatrix
./generate $TYPEA $NA $MA ./test/A.dat
./generate $TYPEB $NB $MB ./test/B.dat
./multimatrix ./test/A.dat ./test/B.dat ./test/C0.dat 0 > time.txt
./multimatrix ./test/A.dat ./test/B.dat ./test/C1.dat 1 >> time.txt
./multimatrix ./test/A.dat ./test/B.dat ./test/C2.dat 2 >> time.txt
./multimatrix ./test/A.dat ./test/B.dat ./test/C3.dat 3 >> time.txt
./multimatrix ./test/A.dat ./test/B.dat ./test/C4.dat 4 >> time.txt
./multimatrix ./test/A.dat ./test/B.dat ./test/C5.dat 5 >> time.txt   
gnuplot -e "set terminal svg size 600,500; set output 'plot.svg'; set title 'test'; set xrange [0:5]; plot 'time.txt' with lines"

