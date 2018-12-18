.text
.global start, sum
start:
	ldr sp, =stack_top
	bl main
stop:
	b stop
sum:
	stmfd sp! , { fp,lr}
	add fp,sp,#4
	// Now adding the parameters
	add r0,r0,r1
	add r0,r0,r2
	add r0,r0,r3
	ldr r3, [fp,#4]
	add r0,r0,r3
	ldr r3, [fp,#4]
	add r0,r0,r3
	
	sub sp,fp,#4
	ldmfd sp!, {fp,pc}
