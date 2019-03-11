;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA			; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop


; Partners - Manan Mittal (manansm2), Luis Aragon (laragon2)
; The program keeps track of the the character whose frequency that needs to be printed in which branches into the code to print the frequency of that character
; The print algorithm takes the the 16 bit value and breaks it into sets of 4 bits to print them to the screen and the whole code loops to print each subsequent character and its frequency




; Table of registers used in this part of the code
;		R0- R0 is meant to read values that must be printed to the monitor when needed
;		R1- R1 is used to keep count of the current symbol and also to check whether all 27 symbols' count has been properly printed out
;		R2-	R2 makes sure all 4 count digits have been printed out
;		R3- R3 stores the value of the count of the current symbol
;		R5- R5 keeps track of every set of four bits
;		R6- R6 is utilized as a temporary register/value holder


PRINT_HIST 	
	AND R1,R1,#0				; put 0 into R1

; The main loop to print the current character and set the registers to print the correct count of each character

PRINT_LOOP
	LD R6,NEG_TWENTY_SEVEN		; Loading -27 to keep count of the number of loops
	ADD R6,R1,R6				; Checking the number of loop count;
	BRz DONE					; If R1 hits 27 the program will branch to done and halt.
	LD R0,FIRST_CHAR			; Loading the '@' (first character) into R0
	ADD R0,R0,R1				; Using the value of R1 to offset the value to the correct frequency count.
	OUT							
	LD R0,SPACE					; Loading the blank space character to put between the character and its frequency
	OUT
	LD R6, HIST_ADDR			; Loading the addresss of the first index of the histogram
	ADD R6,R6,R1				; R1 offsets the value of R6 to the memory location which holds the correct characters count
	LDR R3,R6,#0				; R3 hold the correct characters count
	AND R2,R2,#0				; put 0 into R2

; Sets up the printing of the value represented in the memory address stored in R3	

DIGITS 
	ADD R6,R2,#-4				; Check whether every digit stored in R3 have been printed out
	BRz NEXT_CHAR				; If all digits have been printed, the program fetches the next symbol to be printed
	AND R0,R0,#0				; put 0 into R0
	AND R5,R5,#0				; put 0 into R5

; Generates a 4 bit sequence whose ASCII value must be printed 	
		
CHAR_GEN
	ADD R6,R5,#-4				; Check if R5 equals 4
	BRz PRINTER					; If R5 is 4 it will loop to print next
	ADD R0,R0,R0				; Left shifting R0 to check the next bit
	AND R3,R3,R3				; SETcc
	BRzp SKIP					; if the number is negative the most significant bit is 1 otherwise it is 0 
	ADD R0,R0,#1

; If the MSB is 0 then R0 doesnt need any change

SKIP 
	ADD R5,R5,#1				; Increment R5
	ADD R3,R3,R3				; Left shift R3 to check next bit
	BRnzp CHAR_GEN				; Branch to Charg_gen no matter what

; Decides whether the ASCII value represented is suppoed to be printed out or added to "@"

PRINTER 
	ADD R6,R0,#-9				; If the 4 bits in R0 are less than 9 then its a number according to ASCII
	BRp ALPHABET
	LD R6, ZERO					; ASCII of 0 into R6
	ADD R0,R0,R6				; Offset R0 to what needs to be printed
	BRnzp PRINT					; Branch to print

; If the bit sequence is an alphabet

ALPHABET
	LD R6,A_MIN_TEN 			; Loads the ASCII of A
	ADD R0,R0,R6				; Offset R0 to what needs to be printed

; Prints the ASCII character that needs to be printed
		
PRINT
	OUT
	ADD R2,R2,#1				; Increments R2
	BRnzp DIGITS				; Branch to DIGITS

NEXT_CHAR
	LD R0,NEWLINE				; Loads the newline character
	OUT
	ADD R1,R1,#1				; Increments R1
	BRnzp PRINT_LOOP

DONE	HALT			; done

FIRST_CHAR 			.FILL x40	; ASCII character '@'
NEWLINE 			.FILL xA 	; Newline character
NEG_TWENTY_SEVEN	.FILL #-27	; To keep track of loop
SPACE				.FILL x20	; Space charcater
ZERO				.FILL x30	; Zero character
A_MIN_TEN 			.FILL x37	; Character 'A-10'


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
