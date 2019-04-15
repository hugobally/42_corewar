#!/bin/bash

sed -i '' -e "s/DIR_LAB/%:l1/g" 	test.s
sed -i '' -e "s/IND_LAB/:l1/g" 		test.s
sed -i '' -e "s/DIR/%1985229328/g" 	test.s 	# 0x69696969 : 1768515945 -- 0x12345678 : 305419896 -- 0x76543210 : 1985229328
sed -i '' -e "s/IND/4660/g" 		test.s 		  	# 0x1234 : 4660 -- 0x4321 : 17185
sed -i '' -e "s/REG/r14/g" 			test.s

echo mine --------- ; ../../asm test.s ; hexdump test.cor ; cp test.cor mine.cor ; echo --------- ; echo ref ------- ; ./asm_ref test.s ; hexdump test.cor ; echo ---- ; diff mine.cor test.cor
