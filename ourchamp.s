.name "ourchamp"
.comment ""

fork %:yolo
st r1, 35
suite:
	ld %57673245, r6 #load the following store instruction
	st r6, 787356928 #overflow to get the instruction on 4 bytes
	ld %1, r2
	st r2, 787356929
	live %1
boucle1:
	live %1
	ld %0, r16
	zjmp %:boucle1
yolo:
	ld %57673245, r6
	st r6, 787356928
	ld %1, r2
	st r2, 787356928
	ld %57672221, r7
	st r7, 787356928
