#!/bin/bash
F00IN=$1
F10IN=$2
#F01IN=$3
F11IN=$3
OUT00=$4
OUT10=$5
OUT11=$6
N=$7
#computation of average
 
cat $F00IN | awk -v num=$N 'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s+=$num; } END { print s/5 }' >> $OUT00
cat $F10IN | awk -v num=$N  'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s+=$num; } END { print s/5 }' >> $OUT10
#cat $F01IN | awk -v num=$N  'BEGIN { coun=1; s=0 } 
  #  { while (coun<6) coun++; s+=$num; } END { print s/5 }' >> $OUT
cat $F11IN | awk -v num=$N  'BEGIN { coun=1; s=0 } 
    { while (coun<6) coun++; s+=$num; } END { print s/5 }' >> $OUT11
