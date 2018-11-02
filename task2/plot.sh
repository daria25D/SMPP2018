#!/bin/bash
F1=$1
F2=$2
F3=$3
OUT=$4
TITLE1=$5
TITLE2=$6
TITLE3=$7=
gnuplot -e "
set terminal svg size 600,500;
set output './report/$OUT';
set xrange [0:4];
set xtics ('1000' 0, '2000' 1, '3000' 2, '4000' 3, '5000' 4)
plot '$F1' with linespoint title '$TITLE1',\
    '$F2' with linespoint title '$TITLE2',\
    '$F3' with linespoint title '$TITLE3'
"