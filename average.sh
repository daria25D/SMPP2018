#!/bin/bash

IN=$1
OUT=$2

cat $IN | awk 'BEGIN { coun=0; sum=0 } 
    { while (coun<6) coun++; sum+=$1 } END { print sum/(coun-1) }' > $OUT
cat $IN | awk 'BEGIN { coun=0; sum=0 } 
    { while (coun<6) coun++; sum+=$2 } END { print sum/(coun-1) }' >> $OUT
cat $IN | awk 'BEGIN { coun=0; sum=0 } 
    { while (coun<6) coun++; sum+=$3 } END { print sum/(coun-1) }' >> $OUT
cat $IN | awk 'BEGIN { coun=0; sum=0 } 
    { while (coun<6) coun++; sum+=$4 } END { print sum/(coun-1) }' >> $OUT
cat $IN | awk 'BEGIN { coun=0; sum=0 } 
    { while (coun<6) coun++; sum+=$5 } END { print sum/(coun-1) }' >> $OUT
cat $IN | awk 'BEGIN { coun=0; sum=0 } 
    { while (coun<6) coun++; sum+=$6 } END { print sum/(coun-1) }' >> $OUT