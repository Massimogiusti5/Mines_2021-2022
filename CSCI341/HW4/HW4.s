# Author: Massimo Giusti
# CSCI 341 HW4
# Hash Code for a String

.data
str: .space 21
Prompt: .string "Input a string: "
Result: .string "The Hash Code is:  "
NewLine: "! \n\n"

.text	
Main:
	
	addi a7, zero, 4
	la a0, Prompt
	ecall				# prints prompt
	
	addi a7, zero, 8
	la a0, str
	addi a1, zero, 21 		# max length is 21
	ecall				# read input string from user
	addi s2, zero, 0x0a 		# store delimiter "\n"
	
	lb s0, 0(a0)
	beq s0, s2, EXIT		# before looping, check if string is empty
	
	addi s0, a0, 0			# initailize pointers
	addi s1, a0, 0			# s0 -> beginning of string
					# s1 -> end of string

Loop1:
	lb t1, 0(s1)
	beq t1, s2, LOOPEXIT		# loop unitl we find "\n"
	addi s1, s1, 1			# else traverse string
	jal zero, Loop1 
	
LOOPEXIT:
	addi s1, s1, -1			# have s1 point to last byte of string

GetHashCode:
	lb t2, 0(s0)
	beq t2, s2, PRINTRESULT		# loop until we find "\n"
	lb t1, 0(s1)			# else traverse array
	mul t3, t1, t2			# multiply elements
	add t4, t4, t3			# store to sum
	addi s0, s0, 1			# update pointers
	addi s1, s1, -1
	jal zero, GetHashCode
	
PRINTRESULT:

	addi a7, zero, 4
	la a0, Result
	ecall				# "The hash code is: "

	addi a7, zero, 1
	add a0, zero, t4
	ecall				#print number
	
	addi a7, zero, 4
	la a0, NewLine
	ecall				#print "!" and new line
	
	addi t4, zero, 0		#wipe sum register
	
	jal zero, Main			#go back to main
	
EXIT:
