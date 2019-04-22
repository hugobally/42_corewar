#!/bin/bash -i

CHAMP_DIR="champs"
COR_DIR="champs/cor"

# COLORS #

RED="\033[1;31m"
GRN="\033[1;32m"
YEL="\033[1;33m"
BLU="\033[1;34m"
MAG="\033[1;35m"
CYN="\033[1;36m"
WHT="\033[1;37m"
RESET="\033[0m"

# RUN #

REF_CMD="./corewar_ref -d CYCLE"

if [ $1 ]; then
	REF_CMD="$REF_CMD $1"
fi
if [ $2 ]; then
	REF_CMD="$REF_CMD $2"
fi
if [ $3 ]; then
	REF_CMD="$REF_CMD $3"
fi
if [ $4 ]; then
	REF_CMD="$REF_CMD $4"
fi

MY_CMD=$(echo $REF_CMD | sed "s/corewar_ref -d/corewar -dump/")
NUM_CYCLES=2000000000
START_CYCLE=1

LOG_NAME=$(echo vm_log_$1$2$3$4.out | sed "s/champs\/cor\///" | sed "s/\.cor//")

i=0
while [[ $i -le $NUM_CYCLES ]]; do
	CURRENT_CYCLE=$(($START_CYCLE + $i))
	REF_OUT=$(echo $REF_CMD | sed "s/CYCLE/$CURRENT_CYCLE/")
	MY_OUT=$(echo $MY_CMD | sed "s/CYCLE/$CURRENT_CYCLE/")
	if ! diff -q <($REF_OUT) <($MY_OUT) &>/dev/null; then
		diff <($REF_OUT) <($MY_OUT) &> $LOG_NAME
		printf $RED
		echo "$LOG_NAME : FOUND DIFF"
		printf $RESET
		exit
	fi
	if $REF_OUT | grep "won" &>/dev/null; then
		printf $BLU
		echo "$LOG_NAME : DONE"
		echo "DONE" > $LOG_NAME
		printf $RESET
		exit
	fi
	i=$(($i + 1))
done
