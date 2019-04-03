#!/bin/bash

#./asm tmp.s | hexdump tmp.cor ; echo --------- ; ../sujet/asm_ref tmp.s | hexdump tmp.cor

sed -i '' -e "s/TEST_DIR/1768515945/g" tmp.s
sed -i '' -e "s/TEST_IND/13398/g" tmp.s
sed -i '' -e "s/TEST_REG/r15/g" tmp.s
