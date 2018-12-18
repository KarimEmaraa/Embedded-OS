.text
.code 32
.global copy_vectors, init_sections, vectors_start, vectors_end, reset_handler, copy_exceptions
.global lock, unlock
.global tswitch, taskSize, taskArray, running, kernel_scheduler, main
reset_handler:
	LDR R0, =taskArray  	//task[0]
	LDR r1, =taskSize	//SVC sp must point to the end of task sp stack
	LDR r2, [r1, #0]
	ADD r0, r0 ,r2
	MOV sp, r0
	
	BL  copy_exceptions
	BL  init_sections	//init BSS
	BL  copy_vectors
	
	//init IRQ Stack
	  MRS r0, cpsr
	  BIC r1, r0, #0x1F
	  ORR r1, r1, #0x12
	  MSR cpsr, r1
	  LDR sp, =irq_stack_top


	// go back to SVC mode
	  MRS r0, cpsr
	  BIC r1, r0, #0x1F
	  ORR r1, r1, #0x13
	  BIC r0, r0, #0x80  // enable IRQ interrupt
	  MSR cpsr, r0
	

	BL main 		//in SVC mode
	B .

.align 4
irq_handler:
	sub lr, lr, #4
	stmfd sp!, {r0-r12, lr}
	bl IRQ_handler
	ldmfd sp! , {R0-R12, PC}^

lock:	//disable Interrupts
	MRS r0, cpsr
	ORR r0,#0x80 //set I bit
	MSR cpsr, R0
	MOV pc, lr
unlock:	//enable Interrupts
	MRS R0, cpsr
	BIC r0, #0x80	//clear I bit
	MSR cpsr, r0
	mov pc,lr

tswitch:
MRS r0, cpsr
  ORR r0, r0, #0x80   // set bit means MASK off IRQ interrupt 
  MSR cpsr, r0

  stmfd	sp!, {r0-r12, lr}

  LDR r0, =running // r0=&running
  LDR r1, [r0,#0]  // r1->runningPROC
  str sp, [r1,#4]  // running->ksp = sp

  bl	kernel_scheduler

  LDR r0, =running
  LDR r1, [r0,#0]     // r1->runningPROC
  lDR sp, [r1,#4]

// enable IRQ interrupts : r0 is FREE for use
  MRS r0, cpsr
  BIC r0, r0, #0x80   // clear bit means UNMASK IRQ interrupt
  MSR cpsr, r0
	
  ldmfd	sp!, {r0-r12, pc}
vectors_start:
	LDR PC, reset_handler_addr
	LDR PC, undef_handler_addr
	LDR PC, swi_handler_addr
	LDR PC, prefetch_abort_handler_addr
	LDR PC, data_abort_handler_addr
	B .
	LDR PC, irq_handler_addr
	LDR PC, fiq_handler_addr

	reset_handler_addr:		.word reset_handler
	undef_handler_addr: 		.word undef_handler
	swi_handler_addr: 		.word swi_handler
	prefetch_abort_handler_addr: 	.word prefetch_abort_handler
	data_abort_handler_addr: 	.word data_abort_handler
	irq_handler_addr: 		.word irq_handler
	fiq_handler_addr: 		.word fiq_handler

vectors_end:



