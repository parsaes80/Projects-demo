

;@ Highly recommended in Edit > Configuration 
;@ Set "Auto Indent" to: "None"
;@ Tabs set for 8 characters for ASM files

	.EQU	WORDS_PER_ARRAY, 	4 
	.EQU	BYTES_PER_WORD,		4
	.EQU	BYTES_PER_ARRAY,	WORDS_PER_ARRAY * BYTES_PER_WORD
	.EQU	ARRAYS_PER_ROW,		3
	.EQU	BYTES_PER_ROW,		BYTES_PER_ARRAY * ARRAYS_PER_ROW + 4 * BYTES_PER_WORD 

	.EQU	RAND_REG,		6 ;@ regs to fill with random
	.EQU	USED_REG,		3 ;@ number of "other" registers that are used

	.org 0				;@ start assembling at address 0.
	
	.text				;@ start storing in simulated ROM

Reset_Handler:
	.global Reset_Handler		;@ The entry point on reset
	
	ldr 	sp, =stackT		;@ Initialize SP just past space for stack	
	b	Start			;@ Skip over the definition of the repeat subroutine.

;@ Repeat the bl** instruction that branched to this label -- used at the end of a program.
;@   It is recommended when you hit the breakpoint for this instruction to single step to find out where
;@   in the program called this subroutine.
;@  !!!! Recommended to set a breakpoint for this instruction !!!!
repeat:	sub	pc, lr, #4	;@ repeat the calling bl instruction, not go on to the next instruction.

;@ you can improve the testing code below if you want to.  	
Start:	ldr	r4, =TestTableBigAdd + BYTES_PER_ARRAY	;@ load with address after bigN0 (i.e. bigN1)
	ldr	r5, =bigN				;@ load address of bigN variable
	
loop:	ldmdb	r4, {r0-r3}
	cmn	r0, #1					;@ compare size of bigN0 with -1 marking end of table
success:bleq	repeat					;@ loop here if program successful
;@success:	adreq	pc, success				;@ loop here if program successful
	
	stmia	r5, {r0-r3}				;@ copy bigN0 to bigN
	
	;@ fill the registers {r6-r11} with some random values 
	;@ 1) put random values in memory
	ldr 	r0, =randrb
	bl	rndGen

	;@ 2) load registers {r6-r11} from memory 
	ldmia 	r0, {r6-r11}	
	
	;@ save  registers {r4-r5, SP} in memory for further check
	ldr  	r12, =usedrb
	stmia 	r12, {r4-r5, sp}	
	
	mov	r0, r5
	mov	r1, r4
	ldr 	r2, [r4, #BYTES_PER_ARRAY*2 + BYTES_PER_WORD]	;@ load  maxN0Size
	
	bl	bigAdd			;@ branch and link with our subroutine

	ldr 	r1, =usedra	
	stmia 	r1, {r4-r5, sp}		
	
	push	{r0}			;@ put return value on stack

	ldr  	r0, =usedrb 
	mov	r2, #(USED_REG * 4)	;@ number of registers to compare	
	bl	memcmp			;@ compare using library function
	
	cmp	r0, #0			;@ are the current values of registers and their previous values equal?	
p4r5sp:	blne	repeat			;@ loop here if a problem with r4, r5, or sp
	
	;@ check if the registers {r8-r10} are changed during the bigAdd. 
	;@    If stack is used properly then their values should not change.
	ldr  	r0, =randrb 
	ldr  	r1, =randra	
	stmia 	r1, {r6-r11}	
	mov	r2, #(RAND_REG * 4)	;@ number of registers to compare	
	bl	memcmp			;@ compare using library function
	
	cmp	r0, #0			;@ is the current values of registers and their previous values equal?	
	pop	{r0}			;@ get bigAdd return value back from stack.
p6r11:	blne	repeat			;@ loop here if a problem with r6-r11

	;@load expected return value and check against actual return value
	ldr 	r1, [r4, #BYTES_PER_ARRAY*2 + 2*BYTES_PER_WORD]	
	cmp 	r0, r1
retWrg:	blne 	repeat			;@ loop here if return value Wrong

	;@ compare to check whether an error correctly occurred and therefore further checks can be skipped
	cmp 	r0, #-1			;@ translated to "   cmn r0, #1"
	beq	nxtRow
	
	;@ check whether the calculated and expected sums are equal.
	mov 	r0, r5 
	add	r1, r4,#BYTES_PER_ARRAY	;@put address of bigNR in r1
	ldr	r2, [r1]
	add	r2, r2, #1		;@ add 1 word because size takes a word and needs to be compared too.
	mov	r2, r2, lsl #2		;@ quadruple to get number of bytes to compare
	bl	memcmp			;@ compare bytes using library function
	
	cmp	r0, #0			;@ is bigNR and bigN equal?
notEq:	blne	repeat			;@ loop if test failure detected -- bigNR and bigN not equal

nxtRow:	add	r4, r4, #BYTES_PER_ROW	;@go to next "row" of table
	b	loop			;@loop back for next row

;@ function rndGen to generate random numbers
rndGen:	push	{r4-r5, lr}		;@ also push link register with return location
	mov	r4, r0			;@ r0 has base address to write results
	mov 	r5, #(RAND_REG - 1) * BYTES_PER_WORD
	ldr	r3, =rndSeed
	ldmia	r3, {r0, r1}

rgLoop:	bl	myRand			;@ simple rand function
	str    	r0, [r4, r5]
	subs   	r5, #BYTES_PER_WORD
	bpl 	rgLoop

	ldr	r3, =rndSeed		;@ we could optimize this out.
	stmia	r3, {r0, r1}

	mov	r0, r4			;@ subroutine returns back the base address in r0
	pop	{r4-r5, pc}		;@ also pop return location into program counter

myRand:
;@ from:  http://hackipedia.org/Platform/3D0/html,%203DO%20SDK%20Documentation/Type%20A/tktfldr/acbfldr/2acbh.html

;@ enter with seed in R0 (32 bits), R1 (1 bit in least significant bit)
;@ R2 is used as a temporary register.
;@ on exit the new seed is in R0 and R1 as before
;@ Note that a seed of 0 will always produce a new seed of 0.
;@ All other values produce a maximal length sequence.

	TST    R1, R1, LSR #1                       ;@ top bit into Carry
	MOVS   R2, R0, RRX                          ;@ 33 bit rotate right
	ADC    R1, R1, R1                           ;@ carry into lsb of R1
	EOR    R2, R2, R0, LSL #12                  ;@ (involved!)
	EOR    R0, R2, R2, LSR #20                  ;@ (similarly involved!)

	mov	pc, lr

;@ *******************	
	.data						;@ Store in RAM	
	.space 0x100					;@ Space for stack
stackT:
bigN: 	.space BYTES_PER_ARRAY + BYTES_PER_WORD		;@ bigN0 is copied here and given to bigAdd

randrb: .space (RAND_REG * 4)				;@ registers holding random values before
randra: .space (RAND_REG * 4)				;@ registers holding random values after

usedrb: .space (USED_REG * 4)				;@ used registers before
usedra:	.space (USED_REG * 4)				;@ used registers after

rndSeed:.word	rndLoc					;@ state for random number generator
	.word	rndLoc					;@ initialize with a "random" location used twice
	
	.end						;@ End of assembly in program file	
