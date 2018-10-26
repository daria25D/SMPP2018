#!/bin/bash
F00IN=$1
F10IN=$2
F01IN=$3
F11IN=$4
OUT=$5
N=$6
#computation of average

> $OUT 
cat $F00IN | awk -v num=$N 'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s+=$num; print s/5 }' >> $OUT
cat $F10IN | awk -v num=$N  'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s+=$num; print s/5 }' >> $OUT
cat $F01IN | awk -v num=$N  'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s+=$num; print s/5 }' >> $OUT
cat $F11IN | awk -v num=$N  'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s+=$num; print s/5 }' >> $OUT
