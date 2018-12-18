.global reset_start
reset_start:
	LDR sp, =stack_top //set SVC Stack
	BL main
	B .

