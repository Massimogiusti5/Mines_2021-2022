.data
	values:			.space 800	#800 bytes, 200 words
	arrayNumberPrompt:	.string	"Enter a number: "
	multPrompt:		.string "Mult Result: "
	
.text
	.globl main
	main:
		jal ra, getValues			#Load values in array
		mv s0, a0				#Save num elements
		
		
		la t0, values				#Get array address
		lw a2, 0(t0)				#Get first number
		lw a3, 4(t0)				#Get second number
		jal ra, mult
		mv s0, a0				#Save result
		
		la a0, multPrompt
		li a7, 4
		ecall
		mv a0, s0				#Set int to print
		li a7, 1				#Set to print int
		ecall
		li a0, 10				#Set newline char
		li a7, 11				#Set to print char
		ecall
		
		li a7, 10				#Set syscall to exit program
		ecall					#Exit
	
	#a0: num of elements inputed
	getValues:
		add t0, zero, zero			#Init loop cntr
		li t3, 2				#sets array size
		la t1, values				#Load array address
		getValuesLoop:
			la t4, arrayNumberPrompt
			add a0, zero, t4		#Copies buffer address to a0
 			li a7, 4			#Sets syscall to print null-terminated string
 			ecall
			li a7, 5			#Set syscall argument to 5 (read int from console)
			ecall
			mv t2, a0			#Place syscall rv into the given register
			beqz t2, getValuesLoopEnd	#If input is 0, end
			sw t2, 0(t1)			#Save input
			addi t1, t1, 4			#Increment array address
			addi t0, t0, 1			#Increment loop cntr
			beq t0, t3, getValuesLoopEnd	#If loop cntr=max array size, exit
			j getValuesLoop
		getValuesLoopEnd:
			mv a0, t0			#Set rv
			jalr zero, ra, 0
