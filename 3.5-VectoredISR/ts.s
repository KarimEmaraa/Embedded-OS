.text
.code 32
.global copy_vectors, init_sections, vectors_start, vectors_end, reset_handler, copy_exceptions
.global lock, unlock

reset_handler:
	LDR sp, =svc_stack_top 	//set SVC Mode stack as reset uses it 
	//Now going to IRQ Mode to setup it's sp

	MSR cpsr, #0x92		//to IRQ Mode
	LDR sp, =irq_stack_top
	MSR cpsr, 0x13		//go back to SVC Mode with Inter on
	BL  copy_exceptions
	BL  init_sections	//init BSS
	BL  copy_vectors
	BL main
	B .

.align 4
irq_handler:
	sub lr, lr, #4
	stmfd sp!, {r0-r12, lr}
	bl IRQ_handler
	ldmfd sp! , {R0-R12, PC}^

lock:
	MRS r0, cpsr
	ORR r0,#0x80 //set I bit
	MSR cpsr, R0
	MOV pc, lr
unlock:
	MRS R0, cpsr
	BIC r0, #0x80	//clear I bit
	MSR cpsr, r0
	mov pc,lr


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



