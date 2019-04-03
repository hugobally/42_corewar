#!/bin/bash

#echo mine --------- ; ./asm tmp.s ; hexdump tmp.cor ; echo --------- ; echo ref ------- ; ./asm_ref tmp.s ; hexdump tmp.cor

sed -i '' -e "s/TEST_DIR/1768515945/g" tmp.s
sed -i '' -e "s/TEST_IND/13398/g" tmp.s
sed -i '' -e "s/TEST_REG/r15/g" tmp.s
echo mine --------- ; ./asm tmp.s ; hexdump tmp.cor ; cp tmp.cor mine.cor ; echo --------- ; echo ref ------- ; ./asm_ref tmp.s ; hexdump tmp.cor ; echo ---- ; diff mine.cor tmp.cor
