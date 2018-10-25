#!/bin/bash
F00IN=$1
F10IN=$2
F01IN=$3
F11IN=$4
F00OUT=$5
F10OUT=$6
F01OUT=$7
F11OUT=$8
N=$9


> $F00OUT && > $F10OUT && > $F01OUT && > $F11OUT 
cat $F00IN | awk -v num=$N 'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s=$num; print s }' >> $F00OUT
cat $F10IN | awk -v num=$N  'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s=$num; print s }' >> $F10OUT
cat $F01IN | awk -v num=$N  'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s=$num; print s }' >> $F01OUT
cat $F11IN | awk -v num=$N  'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s=$num; print s }' >> $F11OUT
