#PiEstimation
#Author: Massimo Giusti
#11/1/2021

.text
# calcPI: calculates an approximation of PI accurate to the precision of $a2
#	  the formula used is a sum of pi/4 = ∑(-1)^n/(2n+1) as n goes from zero to $a2
# Params:
#	$a2: number of iterations of summation
#	$fa0: result, approximation of pi as float
# Locals: none
# Temporaries:
#	$t0: count    
#	$t1: fraction (int)
#	$ft0: (-1)^n (float)
#	$ft1: (2n+1) (float)
# 	$ft2: ft0/ft1, essentially the current number in the series

.globl calcPI
calcPI:
	addi t0, zero, 0	# initialize counter
	addi t1, zero, 1	# initialize fraction
	fcvt.s.w fa0, t1	# set current sum to 1, and convert to float
	fcvt.s.w ft0, t1	# store current fraction as float
	fcvt.s.w ft1, t1	# store fraction as float
	fsgnjn.s ft0, ft0, ft0	# negate $ft1 as per formula
	
Loop:
	addi t0, t0, 1		# count ++
	beq t0, a2, END		# if count == num iterations, jump to end
	addi t1, t1, 2		# add 2 to fraction per formula	
	fcvt.s.w ft1, t1

	fdiv.s ft2, ft0, ft1	# get fraction: 1/ft1
	fadd.s fa0, fa0, ft2	# add result to sum
	fsgnjn.s ft0, ft0, ft0  # negate ft0 every iteration
	jal zero, Loop

END:	
	addi t0, zero, 4	# initialize multiplicand of 4
	fcvt.s.w ft0, t0	# store as float
	fmul.s fa0, fa0, ft0	# multiply approximation by 4 to get pi
	jalr zero, ra, 0	# return