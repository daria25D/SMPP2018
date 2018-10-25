#!/bin/bash
Af=$1
Bf=$2
Cf=$3

T0=$(./blocks $Af $Bf ./test/C0_32.dat 0 32) 
C0=$(./compare $Cf ./test/C0_32.dat)
T1=$(./blocks $Af $Bf ./test/C1_32.dat 1 32)
C1=$(./compare $Cf ./test/C1_32.dat)
T2=$(./blocks $Af $Bf ./test/C0_opt.dat 0 100) #make optimal size
C2=$(./compare $Cf ./test/C0_opt.dat)
T3=$(./blocks $Af $Bf ./test/C1_opt.dat 1 100) #make optimal size
C3=$(./compare $Cf ./test/C1_opt.dat)

echo -e $C0" (0 and 0)\n"$C1" (0 and 1)\n"$C2" (0 and 2)\n"$C3 > $4
echo -e "time:" $T0 $T1 $T2 $T3 "\n" >> $4
#./print ./test/C0.dat > C.txt
