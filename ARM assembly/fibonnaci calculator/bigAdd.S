;@============================================================================
;@
;@ Student Name 1: Parsa Eslami
;@ Student 1 #: 301429848
;@ Student 1 userid (email): pea4 (pea4@sfu.ca)
;@
;@ Student Name 2: Dorsa Ahmadi Dafchahi
;@ Student 2 #: 301432248
;@ Student 2 userid (email): daa28(daa28@sfu.ca)
;@
;@ Below, edit to list any people who helped you with the code in this file,
;@      or put ‘none’ if nobody helped (the two of) you.
;@Roozbeh Eslami
;@ Helpers: _everybody helped us/me with the assignment (list names or put ‘none’)__
;@Roozbeh Eslami
;@ Also, reference resources beyond the course textbooks and the course pages on Canvas
;@ that you used in making your submission.
;@
;@ Resources:  ___________
;@
;@% Instructions:
;@ * Put your name(s), student number(s), userid(s) in the above section.
;@ * Edit the "Helpers" line and "Resources" line.
;@ * Your group name should be "HW4_<userid1>_<userid2>" (eg. HW4_stu1_stu2)
;@ * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
;@ * Submit your file to courses.cs.sfu.ca
;@
;@ Name        : bigAdd.S
;@ Description : bigAdd subroutine for Assignment -- 2022
;@============================================================================

;@ Tabs set for 8 characters in Edit > Configurationo

;@ registers:
;@ r0 : pointer to first array
;@ r1 : pointer to second array
;@ r2 : maxSize for output
;@ r3 : loop counter
;@ r4 : max size of arrays
;@ r5 , r6: size of array one and two
;@ r7 , r9: temp registers
;@ r8 : min size of arrays
;@ r11 : use as carry holder

	.text				;@ Store in ROM
	.global	bigAdd
bigAdd:	
	push {r3-r11}
	

	ldr r5 , [r0]
	ldr r6 , [r1]
	
	mov r4 , r5	 
	cmp r6 , r5
	movge r4 , r6   ;@ getting max size of arrays
	
	cmp r4 , r2
	ble endifstatusminusone ;@ check error -1
	mov r0 , #-1
	pop {r3-r11}
	mov pc , lr  ;@ return -1
endifstatusminusone:

	adds r0, r0 , #0 ;@ set carry = 0
	
	mov r3, #1 ;@ set counter = 1
	
	mov r8 , r5	 
	cmp r6 , r5
	movle r8 , r6   ;@ getting min size of arrays
	
	mov r11 , #0 ;@ initialize carry holder
	
whileLoop:
	cmp r8 , r3 ;@The cmp command changes our carry flag so we made an artificial carry flag in r11
	blt endWhileLoop
	
	adds r0, r0 , #0 ;@ set carry = 0
	ldr r7, [r0 , r3, LSL #2]
	ldr r9, [r1 , r3, LSL #2]
	
	adcs r7 , r7 , r11 ;@add carry from previous loop to this loop's calculations
	adcs r7 , r7 , r9
	
	movcs r11 , #1 ;@ store carry flag c = 1
	movcc r11 , #0 ;@ store carry flag c = 0
	
	str r7 , [r0 , r3 , LSL #2]
								;@ add two elements and store the result in first array
	add r3 , r3 , #1
	b whileLoop
endWhileLoop:

	
	cmp r5 , r6
	bge firstarrayisbigger
	
WhileLoop2:
	cmp r3, r6 ;@The cmp command changes our carry flag so we made an artificial carry flag in r11
	bgt endWhileLoop2
	
	ldr r9 , [r1, r3 , lsl #2] ;@ load value from second array
	adds r9 , r9 , r11 	;@ add carry to the element from second array
	
	movcs r11 , #1 ;@ store carry flag c = 1
	movcc r11 , #0 ;@ store carry flag c = 0
	
	str r9 , [r0 , r3 , lsl #2] ;@ store to the first array
	
	add r3, r3, #1
	b WhileLoop2
endWhileLoop2:
	str r6 , [r0] ;@update  the value of bigN0P size in register and memory
	mov r5 , r6
	b endfirstarrayisbigger
	
firstarrayisbigger:
	
WhileLoop3:
	cmp r3 , r5
	bgt EndWhileLoop3
	
	cmp r11 , #1   
	beq carryisyes  ;@branch if carry is set
	mov	r0, #0 
	pop {r3-r11}
	mov	pc, lr ;@ return 0
	
carryisyes:
	ldr r7 , [r0 , r3 , lsl #2]
	adds r7 , r7 , r11
	
	movcs r11 , #1 ;@ store carry flag c = 1
	movcc r11 , #0 ;@ store carry flag c = 0
	
	str r7 , [r0 , r3 , lsl #2]
	
	add r3, r3 , #1
	b WhileLoop3

EndWhileLoop3:

endfirstarrayisbigger:	

	cmp r5 , r2
	beq endfinalif

	str r11 , [r0 , r3 , lsl #2] ;@ add the last element of the r0 array when carry is 1
	
	ldr r7 , [r0]  
	add r7 , r7 , r11 ;@update the size of the array
	mov r11 , #0 ;@clear carry
	str r7 , [r0]

endfinalif:
	
	mov	r0, r11 
	pop {r3-r11}
	mov	pc, lr  ;@ return carry

	.global	rndLoc
rndLoc:		;@ use location after program as somewhat random seed value
