.text

# Multiplication Procedure
# Inputs: 
#	$a2: First number
#	$a3: Second number 
# Output:
#	$a0: product of $a2 and $a3
# Locals:
#	$s0: equals 32 (constant)
#	$s1: equals 1 (constant)
#	$s3: first half of product register
#	$s4: second half of product register
# Temporaries:
#	$t0: count
#	$t1: first digit of $s3
.globl mult
mult:
	addi sp, sp, -8		#allocate memory to stack
	sw t0, 0(sp)		#store $t0
	sw t1, 4(sp)		#store $t1
	addi s3, zero, 0	#clear product registers
	addi s4, zero, 0
	addi t0, zero, 0	#set t0 to 0
	addi t1, zero, 0	#set t1 to 0
	add s3, zero, a2	#set lower half of product register to $a2
	addi s0, zero, 32	#set constants to values
	addi s1, zero, 1
			
mult_loop:
	addi t0, t0, 1		#increment count
	andi t1, s3, 1		#get first bit of product register
	bne s1, t1, shift	#if LSB of product == 0, skip to shift
	
	add s4, s4, a3		#Else: add multiplicand to left half of product

shift:
	andi t1, s4, 1		#$t1 is now first bit of product
	srli s3, s3, 1		#shift first half to the right
	srli a2, a2, 1
	srli s4, s4, 1		#shift second half to the right
	slli t1, t1, 31		#shift first bit of second half by 31
	add s3, s3, t1		#move LSB of second half to MSB of first half
	bne t0, s0, mult_loop	#if count < 32, jump to loop
	
	lw t0, 0(sp)		#restore temp registers
	lw t1, 4(sp)		
	add a0, s3, zero	#return product 
	jalr zero, ra, 0