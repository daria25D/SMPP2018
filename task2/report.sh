#!/bin/bash
NA=$1
MA=$2
NB=$3
MB=$4
SIZE=$5
OUT1=$6
OUT2=$7
L11=$8
L21=$9
L31=${10}
TLBIM1=${11}
TLBDM1=${12}
CYC1=${13}
INS1=${14}
L12=${15}
L22=${16}
L32=${17}
TLBIM2=${18}
TLBDM2=${19}
CYC2=${20}
INS2=${21}

mkdir -p report
./generate $NA $MA ./report/A.dat
./generate $NB $MB ./report/B.dat
./blocks ./report/A.dat ./report/B.dat ./report/C0.dat 0 $SIZE 1 2 3 $L11 $L21 $L31 >> $OUT1
./blocks ./report/A.dat ./report/B.dat ./report/C1.dat 0 $SIZE 5 7 6 4 $TLBIM1 $TLBDM1 $CYC1 $INS1 >> $OUT1
./blocks ./report/A.dat ./report/B.dat ./report/C2.dat 1 $SIZE 1 2 3 $L12 $L22 $L32 >> $OUT2
./blocks ./report/A.dat ./report/B.dat ./report/C3.dat 1 $SIZE 5 7 6 4 $TLBIM2 $TLBDM2 $CYC2 $INS2 >> $OUT2 
#printf "\n" >> $OUT
