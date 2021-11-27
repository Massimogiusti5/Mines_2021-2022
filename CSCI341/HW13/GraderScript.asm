.data
	values:			.space 800	#800 bytes, 200 words
	.globl predictions
	predictions:		.space 800	#800 bytes, 200 words
	arrayNumberPrompt:	.string	"Enter a number: "
	actual:			.string "Actual: "
	prediction:		.string "Prediction: "
	accuracy:		.string "Accuracy: "
	
.text
	.globl main
	main:
		jal ra, getValues			#Load values in array
		mv s0, a0				#Save num elements
		
		la a0, actual
		li a7, 4
		ecall
		la a2, values				#Set argument
		mv a3, s0				#Set argument
		jal ra, printValues
		
		la a2, values				#Set argument
		mv a3, s0				#Set argument
		jal ra, branchPredictionSim
		
		la a0, prediction
		li a7, 4
		ecall
		la a2, predictions			#Set argument
		mv a3, s0				#Set argument
		jal ra, printValues
		
		la a2, values				#Set argument
		la a3, predictions			#Set argument
		mv a4, s0				#Set argument
		jal ra, getAccuracy
		mv s1, a0				#Save result
		
		la a0, accuracy
		li a7, 4
		ecall
		mv a0, s1
		li a7, 1
		ecall
		li a0, 37
		li a7, 11
		ecall
		li a0, 10
		li a7, 11
		ecall
		
		li a7, 10				#Set syscall to exit program
		ecall					#Exit
	
	#a0: num of elements inputed
	getValues:
		add t0, zero, zero			#Init loop cntr
		li t3, 200				#sets array size
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

	#a2: address of list to print
	#a3: num of elements
	printValues:
		add t0, zero, zero			#Set loop counter
		printValuesLoop:
			slli t1, t0, 2			#Mult cntr by 4
			add t1, a2, t1			#Get element address
			lw t1, 0(t1)			#Get element
			
			addi a0, t1, 48			#Turn into char
			li a7, 11
			ecall
			
			addi t0, t0, 1			#Increment loop counter
			bne t0, a3, printValuesLoop	#If counter!=num elements, loop again
		li a0, 10
		li a7, 11
		ecall
		jalr zero, ra, 0
		
	#a2: address of actual
	#a3: address of prediction
	#a4: num of elements
	#a0: accuracy
	getAccuracy:
		add t0, zero, zero			#Set correct counter to 0
		add t1, zero, zero			#Set counter to 0
		getAccuracyLoop:
			slli t4, t1, 2			#Mult cntr by 4
			add t2, a2, t4			#Get correct element address
			lw t2, 0(t2)			#Get element
			add t3, a3, t4			#Get prediction element address
			lw t3, 0(t3)			#Get element
			bne t2, t3, incorrectPrediction
				addi t0, t0, 1		#Increment correct counter
			incorrectPrediction:
			addi t1, t1, 1			#Increment loop counter
			bne t1, a4, getAccuracyLoop	#If counter!=num elements, loop again
		li t1, 100				#Set to 100
		mul a0, t0, t1				#Mult correct by 100
		div a0, a0, a4				#correct*100/total
		jalr zero, ra, 0