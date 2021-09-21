.data
	values:	.space 40				#40 bytes, 10 words
	arrayNumberPrompt:	.string	"Enter a number to add to the array: "
	sumPrompt:		.string	"Summation: "
	prodPrompt:		.string	"Product: "
	maxPrompt:		.string	"Max: "
	interpPrompt:		.string	"Interp: "
	
.text
	.globl main
	main:
		jal ra, getValues
		mv s0, a0
		
		la a2, values
		mv a3, s0
		jal ra, sum
		mv s1, a0
		la t0, sumPrompt
		add a0, zero, t0			#Copies buffer address to a0
 		li a7, 4				#Sets syscall to print null-terminated string
 		ecall
		mv a0, s1				#Set syscall argument to the integer
		li a7, 1				#Set syscall argument to 1 (print integer)
		ecall
		addi a0, zero, 10			#Set syscall argument to print char
		li a7, 11				#Set syscall argument to 11 (print char)
		ecall
		
		la a2, values
		mv a3, s0
		jal ra, prod
		mv s1, a0
		la t0, prodPrompt
		add a0, zero, t0			#Copies buffer address to a0
 		li a7, 4				#Sets syscall to print null-terminated string
 		ecall
		mv a0, s1				#Set syscall argument to the integer
		li a7, 1				#Set syscall argument to 1 (print integer)
		ecall
		addi a0, zero, 10			#Set syscall argument to print char
		li a7, 11				#Set syscall argument to 11 (print char)
		ecall

		la a2, values
		mv a3, s0
		jal ra, max
		mv s1, a0
		la t0, maxPrompt
		add a0, zero, t0			#Copies buffer address to a0
 		li a7, 4				#Sets syscall to print null-terminated string
 		ecall
		mv a0, s1				#Set syscall argument to the integer
		li a7, 1				#Set syscall argument to 1 (print integer)
		ecall
		addi a0, zero, 10			#Set syscall argument to print char
		li a7, 11				#Set syscall argument to 11 (print char)
		ecall
		
		li a7, 10				#Set syscall to exit program
		ecall					#Exit
	
	#a0: num of elements inputed
	getValues:
		add t0, zero, zero			#Init loop cntr
		li t3, 10				#Array size
		la t1, values				#Load array address
		getValuesLoop:
			la t4, arrayNumberPrompt
			add a0, zero, t4		#Copies buffer address to a0
 			li a7, 4			#Sets syscall to print null-terminated string
 			ecall
			li a7, 5			#Set syscall argument to 5 (read int from console)
			ecall
			mv t2, a0			#Place syscall rv into the given register
			beqz t2, getValuesLoopEnd
			sw t2, 0(t1)
			addi t1, t1, 4
			addi t0, t0, 1
			beq t0, t3, getValuesLoopEnd
			j getValuesLoop
		getValuesLoopEnd:
			mv a0, t0
			jalr zero, ra, 0
