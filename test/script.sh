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

# STARTUP #

make -C ..
cp ../corewar .
cp ../asm .

# COMPILE CHAMP LIST #

while true; do
	read -e -p "Recompile Champions ? " yn
	case $yn in
		[Yy]* )
			ls -1 $CHAMP_DIR | grep "\.s" | sed -e "s/\.s//g" > tmp
			while read -r line; do
				./asm_ref $CHAMP_DIR/$line.s
				mv $CHAMP_DIR/$line.cor $COR_DIR/$line.cor
			done < tmp
			break;;
		[Nn]* ) break;;
	esac
done

clear

# AFF CHAMP LIST #

cd $COR_DIR

CURSOR_X=0
CURSOR_Y=0
MAX_Y=20

clear 
printf $BLU
for file in *; do
	tput cup $CURSOR_Y $CURSOR_X 
	echo $file | sed "s/\.cor//g"
	CURSOR_Y=$(($CURSOR_Y + 1))
	if [[ $CURSOR_Y -eq $MAX_Y ]]; then
		CURSOR_Y=0
		CURSOR_X=$(($CURSOR_X + 30))
	fi
done

printf $RESET
tput cup $MAX_Y 0

# ARGS #

for file in *; do
	mv $file $(echo $file | sed "s/\.cor//g");
done

echo ""
printf $WHT
read -e -p "Champion 1 : " C1
read -e -p "Champion 2 : " C2
read -e -p "Champion 3 : " C3
read -e -p "Champion 4 : " C4
read -e -p "Run for X cycles : " NUM_CYCLES
printf $RESET

for file in *; do
	mv $file $file.cor
done

rm -f tmp

# RUN #

cd ../..

REF_CMD="./corewar_ref -d CYCLE"

if [[ ${#C1} -ge 1 ]]; then
	REF_CMD="$REF_CMD $COR_DIR/$C1.cor"
fi
if [[ ${#C2} -ge 1 ]]; then
	REF_CMD="$REF_CMD $COR_DIR/$C2.cor"
fi
if [[ ${#C3} -ge 1 ]]; then
	REF_CMD="$REF_CMD $COR_DIR/$C3.cor"
fi
if [[ ${#C4} -ge 1 ]]; then
	REF_CMD="$REF_CMD $COR_DIR/$C4.cor"
fi

MY_CMD=$(echo $REF_CMD | sed "s/corewar_ref -d/corewar -dump/")

for ((i = 1 ; i <= $NUM_CYCLES ; i++)); do
	echo "Cycle $i"
	MY_CMD_TMP=$(echo $MY_CMD | sed "s/CYCLE/$i/")
	REF_CMD_TMP=$(echo $REF_CMD | sed "s/CYCLE/$i/")
	echo $MY_CMD_TMP
	diff -s <($REF_CMD_TMP) <($MY_CMD_TMP)
done
