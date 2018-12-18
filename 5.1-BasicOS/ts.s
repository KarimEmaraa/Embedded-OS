.text
.code 32
.global reset_handler,t1, taskSize, main,scheduler,tswitch

reset_handler:
	LDR R0, =t1
	LDR R1, =taskSize
	LDR R2, [r1, #0]
	ADD R0,R0,R2
	MOV sp, R0
	BL main

tswitch:
	STMFD sp!, {r0-r12, lr}
	LDR r0, =running // r0=&running
	LDR r1, [r0, #0] // r1->runningPROC
	STR sp, [r1, #4] // running->ksp = sp
	FIND:
	BL scheduler
	// call scheduler() in C
	LDR r0, =running
	LDR r1, [r0, #0] // r1->running PROC
	LDR sp, [r1, #4] // restore running->ksp
	LDMFD sp!, {r0-r12, lr} // restore register
	MOV pc, lr
	// return
