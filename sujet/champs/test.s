.name "TestChampion"
.comment "YOLOSWAG"


sti		r1, %:live, %1
or		%0, %1111638594, r2
or		%0, %22, r3
or		%0, %4, r4

live:	live %1
		sti r2, r3, %0
		add r3, r4, r3
		and r1, %0, r1
		zjmp %:live

end:
