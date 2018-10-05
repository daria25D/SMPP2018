#!/bin/bash

FILE=$1
TITLE=$2

gnuplot -e "
set terminal svg size 600,500; 
set output './report/$FILE'; 
set title '$TITLE'; 
set xtics ('ijk' 0, 'ikj' 1, 'kij' 2, 'jik' 3, 'jki' 4, 'kji' 5); 
set xrange [0:5]; 
plot 'time_average.txt' with linespoint"