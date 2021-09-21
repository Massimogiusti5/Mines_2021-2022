# Massimo Giusti
# CSCI 341: Computer Organization
# HW 5 : Math Procedures

.text

.globl sum
# input(s): $a2 = address of array, $a3 = length of the array
# output: $a0 = sum of the elements of the array
# locals: $s2 = current word, $s3 = iterator, $s4 = pointer to array

sum:	
	addi a0, zero, 0	# pre loop: set a0 to zero
	addi s4, a2, 0		# pre loop: set $s4 to point to array
	addi s3, zero, 0	# pre loop: set iterator($s3) to zero
	
sum_loop:
	lw s2, 0(s4) 		# set $s2 to be the value of $s4
	addi s4, s4, 4	 	# increment pointer($s4) by 1 word
	addi s3, s3, 1		# increase iterator($s3) by 1
	add a0, a0, s2		# add element to output register($a0)
	bne s3, a3, sum_loop	# keep looping until iterator = array size
	
	jalr zero, ra, 0	# return $a0
	
	
.globl prod
# input(s): $a2 = address of array, $a3 = length of the array
# output: $a0 = sum of the elements of the array
# locals: $s2 = current word, $s3 = iterator, s4 = pointer to array
prod:
	addi a0, zero, 1	# pre loop: set a0 to 1 so multiplication works
	addi s4, a2, 0		# pre loop: set $s4 to point to array
	addi s3, zero, 0	# pre loop: set iterator($s3) to zero
prod_loop:
	lw s2, 0(s4) 		# set $s2 to be the value of $a4
	addi s4, s4, 4	 	# increment pointer($s4) by 1 word
	addi s3, s3, 1		# increase iterator($s3) by 1
	mul a0, a0, s2		# multiply element with value of output register($a0)
	bne s3, a3, prod_loop	# keep looping until iterator = array size
	
	jalr zero, ra, 0	# return $a0


.globl max
# input(s): $a2 = address of array, $a3 = length of the array
# output: $a0 = sum of the elements of the array
# locals: $s2 = current word, $s3 = iterator, s4 = pointer to array
max:
	addi a0, zero, 0	# pre loop: set a0 to 0 so it is the min element
	addi s4, a2, 0		# pre loop: set $s4 to point to array
	addi s3, zero, 0	# pre loop: set iterator($s3) to zero
max_loop:
	beq s3, a3, end_max	# before loading, check if iterator = array size
	lw s2, 0(s4) 		# set $s2 to be the value of $a4
	addi s4, s4, 4	 	# increment pointer($s4) by 1 word
	addi s3, s3, 1		# increase iterator($s3) by 1
	blt s2, a0, max_loop	# if s2 is less than max, jump and keep looping 
	add a0, s2, zero	# else set a0 to s2
	jal zero, max_loop 	# jump to loop
	
end_max:
	jalr zero, ra, 0	# return $a0