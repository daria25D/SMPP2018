#!/bin/bash
TYPEA=$1
NA=$2
MA=$3
TYPEB=$4
NB=$5
MB=$6
Af=./test/$7
Bf=./test/$8
Cf=./test/$9

./generate $TYPEA $NA $MA $Af 
./generate $TYPEB $NB $MB $Bf
./multimatrix $Af $Bf $Cf 0 &>/dev/null
