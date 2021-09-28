Massimo Giusti
CSCI 341 HW5 - Procedures

Collaborators: none*

2. Pseudocode (C++):

int sum(int* ptr, int length){
    int sum = 0;
    int i = 0;
    while(i < length){
        sum += *ptr;
        ptr += 4;
        i++; 
    }
    return sum;
}

int prod(int* ptr, int length){
    int prod = 1;
    int i = 0;
    while(i < length){
        sum *= *ptr;
        ptr += 4;
        i++; 
    }
    return prod;
}

int max(int* ptr, int length){
    int max = 0;
    int i = 0;
    while(i < length){
        if(i == length) return max;
        if(*ptr > max){
          max = *ptr;
        }
        ptr += 4;
        i++;
    }
    return max;
}


3. The only real challenge I had was figuring out how to keep my register use consistent across the grading file and my procedures.
   I had bugs where the registers $s1 and $s0 were dirty between procedure calls, so what I did was find registers that weren't used
   between procedures, and stored data there.

4. What I liked about this assignment was how it started to mimic higher level programming in the way I solved the problem. For example,
   my Pseudocode is very close to what I actually wrote in the .s file. 

5. I spent close to an hour on this assignment.

6. No extra credit features.