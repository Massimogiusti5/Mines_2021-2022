.data
	str: .string "Sum: "
	.globl str
	newline: .string "\n"
	.globl newline


.text
.globl binarySearch

# Main Recursive Binary Search Algorithm
# @ Params: 
#	$a2: address of array
#	$a3: first index
#	$a4: last index
#	$a5: search value
# @ Locals:
#	$s1: dividend
#	$s2: word multiple
# @ Temporaries: (after printing sum)
#	$t0: middle index
#	$t1: middle address
#	$t2: Pointer to middle element
#	$t3: value of middle element
# @ Returns:
#	$a0: index of search value if found, else zero
	
binarySearch:
#print sum of each recursive iteration
	#constants
	addi s1, zero, 2	#dividend 
	addi s2, zero, 4	#word multiple for pointers
	
	addi a7, zero, 4	#print string
	la a0, str
	ecall			#prints: "Sum: "
	
	sub t0, a4, a3		#get length of array
	add t2, a3, zero
	addi t0, t0, 1	
	addi sp, sp, -12
	add t1, a2, zero	#copy pointer to t2
	sw a3, 0(sp) 		#move $a3 to stack since it an arg for Sum
	sw a2, 4(sp)		#store pointer to front of array
	sw ra, 8(sp)		#store $ra onto stack
	add a3, zero, t0
	mul t2, t2, s2		#get pointer to start of array and sum from there
	add t1, t1, t2
	add a2, t1, zero
	jal ra, sum		#get sum
				#a0 = sum of arr
			
	addi a7, zero, 1	
	ecall			#print sum
	
	addi a7, zero, 4	# print new lines
	la a0, newline
	ecall

	lw a3, 0(sp)		#get a3 and a2 from stack
	lw a2, 4(sp)
	addi sp, sp, 8
	addi t0, zero, 0	#reset registers
	addi t1, zero, 0
	addi t2, zero, 0
	addi t3, zero, 0
	addi a0, zero, 0
	addi s1, zero, 2	 
	addi s2, zero, 4	
	

#binary search algorithm
	sub t0, a4, a3		# get difference between high and low indeces
	div t0, t0, s1		# get $t0 in range of [a3, a4]
	add t0, t0, a3		# formula: mid = (a4-a3)/2 + a3
	mul t1, t0, s2		# get address of middle index, $t2
	add t2, a2, t1		# initialize pointer to middle index
	lw t3, 0(t2)		# load value of middle index into $t3
	bne t3, a5, IF		# if middle index is not search value, set up recursion
	add a0, zero, t0	# found value - jump to end
	jal zero, End		

# sum function copied from HW5
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

	
		
# logic part of binary search				
IF:
	blt t3, a5, secondHalf  # if middle value < search value recurse on second half
				# else recurse on first half 
	addi t0, t0, -1		
	add a4, zero, t0	# set right index to half - 1
	jal zero, endIf		#jump to recursive call

secondHalf:
	addi t0, t0, 1		
	add a3, zero, t0	# set indeces to second half + 1
	
endIf:
	jal ra, binarySearch	# recurse with new bounds

#end of recursion
End:
	lw ra, 0(sp)		# return 
	addi sp, sp, 4
	jalr zero, ra, 0
	
