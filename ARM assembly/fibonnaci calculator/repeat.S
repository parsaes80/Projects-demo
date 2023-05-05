	.text				;@ Store in ROM

;@ Repeat the bl** instruction that branched to this label -- used at the end of a program.
;@   It is recommended when you hit the breakpoint for this label to single step to find out where
;@   in the program called this subroutine.
	.global repeat		
repeatX:	nop
	sub	pc, lr, #4	;@ repeat the calling bl instruction, not go on to the next instruction.

