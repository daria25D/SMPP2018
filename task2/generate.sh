#!/bin/bash
NA=$1
MA=$2
NB=$3
MB=$4
Af=./test/$5
Bf=./test/$6
Cf=./test/$7
BLOCKS=$8

./generate $NA $MA $Af 
./generate $NB $MB $Bf
./blocks $Af $Bf $Cf 0 $BLOCKS &>/dev/null
