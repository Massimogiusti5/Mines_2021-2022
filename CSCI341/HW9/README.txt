Massimo Giusti
CSCI 341: Computer Organization
10/20/2021

1) Collaborators: none
2) Pseudocode (c)

int mult(int multiplier, int multiplicand ){
	int product = 0;
	for(int i = 0; i < 32; i++){
		//if LSB == 1, add to product
		if(multiplicand  % 2 == 1){
			product +=  multiplier;
		}
		//shift nums
		multpilicand  >> 1;
		multiplier << 1;
	}
	return product;
}

3) I didn't have much issue design-wise with this homework, I coded up the pseudocode very easily and implemented it quickly. However, I had a few issues with variables. I lost track of what stored what and got some registers mixed up. After a bit of debugging, I got the solution.

4) What I liked about this assignment was showing the intricacy of a simple built in operation. Coding up a multiplication algorithm better explains the process in hardware rather than using the mul instruction.

5) I spent like an hour on this assignment.

6) No ec features. 
