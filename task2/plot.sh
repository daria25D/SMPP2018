#!/bin/bash
F1=$1
F2=$2
F3=$3
F4=$4
F5=$5
OUT=$6
TITLE1=$7
TITLE2=$8
TITLE3=$9
TITLE4=${10}
TITLE5=${11}
gnuplot -e "
set terminal svg size 600,500;
set output './report/$OUT';
set yrange [0:4];
set xtics ('32 ijk' 0, '32 ikj' 1, 'opt ijk' 2, 'opt ikj' 3)
plot '$F1' with linespoint title '$TITLE1',\
    '$F2' with linespoint title '$TITLE2',\
    '$F3' with linespoint title '$TITLE3',\
    '$F4' with linespoint title '$TITLE4',\
    '$F5' with linespoint title '$TITLE5'
"