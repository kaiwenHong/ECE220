; Implement a stack calculator that can do the following operations:
; ADD, SUBTRACT, MULTIPLY, DIVIDE

; Inputs:
; terminal - postfix equation

; Outputs:
; terminal - [0 - F]{4}, evaluation of postfix equation
; Register R5 - [0 - F]{4}, evaluation of postfix equation

; checks the character whether it is an operand or an operator. Also prints invalid if it is a symbol other than the earlier two.
; Partners - Manan Mittal (manansm2), Luis Aragon (laragon2)

.ORIG x3000

MAIN
	JSR EVALUATE
	ADD R0,R0,#0
	BRnp DONE
	JSR PRINT_HEX

DONE
 HALT


; PRINT_HEX
; Description: prints out the value in Register 3 to the terminal
; Inputs: R3 - value in register to be printed out
; Outputs: Value printed to the terminal

PRINT_HEX
	ST R7,SAVE_R7_PRINT
	ADD R3,R5,#0
	AND R1,R1,#0

; to keep track of the number of digits printed
DIGITS	
	ADD R6,R1,#-4
	BRz DONE_PRINT	;if All digits are printed
	AND R0,R0,#0
	AND R2,R2,#0

; to determine the character that needs to be printed
CHAR_GEN
 ADD R6,R2,#-4
 BRz PRINTER	;if all four bits of a sequence of 4 have been shifted
 ADD R0,R0,R0
 AND R3,R3,R3
 BRzp SKIP
 ADD R0,R0,#1

SKIP
	ADD R2,R2,#1
	ADD R3,R3,R3
	BRnzp CHAR_GEN

;prints the character to screen

PRINTER
 ADD R6,R0,#-9
	BRp ALPHABET	; it is an alphabet
	LD R6, CHAR0	
	ADD R0,R0,R6
	BRnzp PRINT

ALPHABET
 LD R6,CHARA10
	ADD R0,R0,R6

PRINT 
	OUT
	ADD R1,R1,#1
	BRnzp DIGITS

DONE_PRINT
	LD R7,SAVE_R7_PRINT
	RET

SAVE_R7_PRINT .BLKW #1
CHAR0 .FILL x30
CHARA10 .FIll x37
SAVE_R7_EVALUATE .BLKW #1

; EVALUATE
; Description: handles input from terminal
; Inputs: terminal - input
; Outputs: terminal - evaluation of equation or outputs an error
;	R5 - evalution of equation
;	Register table
; R0- is used for all the IO
;	R1- is used as a temp register to determine the character entered
;	R3- to store that value popped from the stack
; R4- to store the value popped from the stack
;	R5- to check whether the push and pop routines were successful
;	R6- to store the initial input when R0 gets changed
; R7- For storing PC values during subroutine calls



EVALUATE
	ST R7,SAVE_R7_EVALUATE
INPUT 
	IN
	LD R1,NEG_EQUALS_CHAR	; if the character is an '=' sign
	ADD R1,R1,R0
	BRz OUTPUT
	LD R1,NEG_SPACE_CHAR	; if the character is a blank space
	ADD R1,R0,R1
	BRz INPUT
	LD R1,NEG_NINE_CHAR	; if the character is <=9
	ADD R1,R0,R1
	BRp INVALID_OUTPUT
	LD R1,NEG_ZERO_CHAR	; if the character is >=0
	ADD R1,R0,R1
	BRzp OPERAND
	ADD R6,R0,#0
	JSR POP
	ADD R5,R5,#0	; Underflow
	BRp INVALID_OUTPUT
	ADD R4,R0,#0
	JSR POP
	ADD R5,R5,#0	; Underflow
	BRp INVALID_OUTPUT
	ADD R3,R0,#0
	LD R1,NEG_ADD_CHAR	; if the characater = '+' then add
	ADD R1,R6,R1
	BRnp SUBTRACT
	JSR PLUS
	JSR PUSH
	BRnzp INPUT

SUBTRACT
	LD R1,NEG_MIN_CHAR	; if character is '-' then subtract
	ADD R1,R6,R1
	BRnp MULTIPLY
	JSR MIN
	JSR PUSH
	BRnzp INPUT

MULTIPLY
	LD R1,NEG_MUL_CHAR	; if the character is '*' then multiply
	ADD R1,R6,R1
	BRnp DIVIDE
	JSR MUL
	JSR PUSH
	BRnzp INPUT

DIVIDE
	LD R1,NEG_DIV_CHAR	; if the character is '/' then o this method divide
	ADD R1,R6,R1
	BRnp INVALID_OUTPUT
	JSR DIV
	JSR PUSH
	BRnzp INPUT

OPERAND
	LD R1,NEG_ZERO_CHAR	; converting the character to the value of the number
	ADD R0,R0,R1
	JSR PUSH
	ADD R5,R5,#0
	BRp INVALID_OUTPUT	; overflow
	BRnzp INPUT

; if there is only one value in the stack it will print the output
OUTPUT
	LD R1, STACK_TOP
	LD R2, STACK_START
	ADD R1,R1,#1
	NOT R2,R2
	ADD R2,R2,#1
	ADD R1,R1,R2
	BRz VALID_OUTPUT
	BRnzp INVALID_OUTPUT

VALID_OUTPUT
	JSR POP
	ADD R5,R0,#0	; storing the value in R5
	AND R0,R0,#0
	BRnzp RET_EVALUATE

INVALID_OUTPUT
	LEA R0,ERROR
	PUTS
	BRnzp RET_EVALUATE
	

RET_EVALUATE
	LD R7,SAVE_R7_EVALUATE
	RET

NEG_SPACE_CHAR .FILL xFFE0
NEG_ZERO_CHAR .FILL xFFD0
NEG_NINE_CHAR .FILL xFFC7
NEG_ADD_CHAR	.FILL xFFD5
NEG_MIN_CHAR	.FILL xFFD3
NEG_MUL_CHAR	.FILL xFFD6
NEG_DIV_CHAR	.FILL xFFD1
NEG_EQUALS_CHAR	.FILL xFFC3
ERROR .STRINGZ "Invalid equation"

; PLUS
; Description: adds two numbers (R0 = R3 + R4)
; Inputs: R3 - number_1
;	R4 - number_2
; Outputs: R0 - sum of the two numbers inputted
PLUS
	ADD R0,R3,R4
	RET


; MIN
; Description: subtracts two numbers (R0 = R3 - R4)
; Inputs: R3 - Number_1
;	R4 - number_2
; Outputs: R0 - the difference between 1 and 2

MIN
	ADD R0,R4,#0
	NOT R0,R0	
	ADD R0,R0,#1
	ADD R0,R3,R0
	RET


; MUL
; Description: multiplies two numbers (R0 = R3 * R4)
; Inputs: R3 - factor
;	R4 - factor
; Outputs: R0 - product
MUL
	ST R7,SAVE_R7
	JSR SIGN

;multiplication by repeated addition
LOOP_MUL
	ADD R3,R3,#0
	BRz FINISH_MUL	
	ADD R0,R4,R0
	ADD R3,R3,#-1
	BRnzp LOOP_MUL

FINISH_MUL
	ADD R1,R1,#-1
	BRnp RET_MUL
	NOT R0,R0
	ADD R0,R0,#1

RET_MUL
	LD R1,SAVE_R1
	LD R7,SAVE_R7
	RET

SAVE_R1 .BLKW #1
SAVE_R7 .BLKW #1

; decides the sign of the numbers that are popped from the stack to determine the final sign of the answer
SIGN
	ST R1, SAVE_R1
	AND R1,R1,#0;
	ADD R3,R3,#0
	BRzp POS_1
	ADD R1,R1,#1
	NOT R3,R3
	ADD R3,R3,#1

POS_1
	ADD R4,R4,#0
	BRzp POS_2
	ADD R1,R1,#1
	NOT R4,R4
	ADD R4,R4,#1

POS_2
	AND R0,R0,#0
	RET

; DIV
; Description: divides two numbers (R0 = R3 / R4)
; Inputs: R3 - numerator
;	R4 - denominator
; Outputs: R0 - quotient
DIV	
	ADD R4,R4,#0
	BRz INVALID_OUTPUT
	ST R7,SAVE_R7
	JSR SIGN
	NOT R4,R4
	ADD R4,R4,#1

; division by repeated subtraction
LOOP_DIV
	ADD R3,R3,#0
	BRn FINISH_DIV
	ADD R3,R3,R4
	ADD R0,R0,#1
	BRnzp LOOP_DIV

FINISH_DIV
	ADD R0,R0,#-1
	ADD R1,R1,#-1
	BRnp RET_DIV
	NOT R0,R0
	ADD R0,R0,#1

RET_DIV
	LD R1,SAVE_R1
	LD R7,SAVE_R7
	RET
	



; PUSH
; Description: Pushes a charcter unto the stack
; Inputs: R0 - character to push unto the stack
; Outputs: R5 - 0 (success) or 1 (failure/overflow)
; Registers: R3 - stores STACK_END
;	R4 - stores STACK_TOP
PUSH
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0	;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1	;
	NOT R3, R3	;
	ADD R3, R3, #1	;
	ADD R3, R3, R4	;
	BRz OVERFLOW	;stack is full
	STR R0, R4, #0	;no overflow, store value in the stack
	ADD R4, R4, #-1	;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH	;
OVERFLOW
	ADD R5, R5, #1	;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


; POP
; Description: Pops a character off the stack
; Inputs:
; Outputs: R0 - character popped off the stack
;	R5 - 0 (success) or 1 (failure/underflow)
; Registers: R3 - stores STACK_END
;	R4 - stores STACK_TOP

POP
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0	;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3	;
	ADD R3, R3, #1	;
	ADD R3, R3, R4	;
	BRz UNDERFLOW	;
	ADD R4, R4, #1	;
	LDR R0, R4, #0	;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP	;
UNDERFLOW
	ADD R5, R5, #1	;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END;
