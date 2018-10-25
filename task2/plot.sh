#!/bin/bash
F00=$1
F10=$2
F01=$3
F11=$4
OUT=$5
TITLE00=$6
TITLE10=$7
TITLE01=$8
TITLE11=$9

gnuplot -e "
set terminal svg size 600,500;
set output './report/$OUT';
set xrange [0:4];
plot '$F00' with linespoint title '$TITLE00',\
    '$F10' with linespoint title '$TITLE10',\
    '$F01' with linespoint title '$TITLE01',\
    '$F11' with linespoint title '$TITLE11'
"