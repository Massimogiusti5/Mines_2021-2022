.text
	# branchPredictionSim: simulated a branch predictor, given a list of branch history, decide whether or not to take a branch
	# args:
	#	$a2: address of branches taken list
	#	$a3: num of elements in list
	# locals:
	#	$s0: address of predicted branches
	#	$s1: state of predictor (0-3)
	#	$s2: initiated to 2 to determine whether or not to take a branch
	#	$s3: to check if state is equal to 3
	# temporaries:
	#	$t0: current actual branch value (1 or 2)
	#	$t1: current predicted branch value (1 or 2)
	#	$t2: counter for loop
	#returns:
	#	$a0: address of array of branch predictions
	.globl branchPredictionSim
	branchPredictionSim:
		#initialize vars
		la s0, predictions
		la a0, predictions	#set a0 to base address of prediction list
		addi s1, zero, 0	#state of predictor (0-3)
		addi s2, zero, 2	#whether or not to take a branch
		addi s3, zero, 3	#to check if state is equal to 3
		addi t0, zero, 0	#current actual branch value
		addi t1, zero, 0	#current predicted branch value
		addi t2, zero, 0	#counter for loop
	Loop:
		beq t2, a3, END		#if loop counter == size of given list, jump to end
		lw t0, 0(a2)		#load current actual branch taken
		blt s1, s2, notTaken	#if state < 2, don't take branch, else take branch
		addi t1, zero, 2	#set predicted branch value to 2
		sw t1, 0(s0)		#store the predicted value to list
		jal zero, UpdateState	#jump to avoid notTaken label
	notTaken:
		addi t1, zero, 1	#set predicted branch value to 1
		sw t1, 0(s0)		#store the predicted value to list
	UpdateState:
		bne t0, s2, Decrement	#If branch was not taken, decrement state
		beq s1, s3, ENDIF	#If state == 3, no need to increment
		addi s1, s1, 1		#increment state
		jal zero, ENDIF		#jump to avoid decrement block
	Decrement:
		beq s1, zero, ENDIF	#if state is zero, no need to decrement
		addi s1, s1, -1		#decrement state
	ENDIF:
		addi a2, a2, 4		#update index for actual list
		addi s0, s0, 4		#update index for prediction list
		addi t2, t2, 1		#increment loop count
		jal zero, Loop		#jump to loop
	END:
		add s0, zero, a3	#set s0 equal to length of list for graderscript
		jalr zero, ra, 0	#return
