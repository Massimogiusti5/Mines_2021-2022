Massimo Giusti
CSCI 341 HW6 - Binary Search

Collaborators: none*

2. Pseudocode (C++):

int binarySearch(int* ptr, int first, int last, int search){
    printSum(ptr + first*4, first-last+1);
    int middle = (last - first)/2 + last;
    int middle_ptr = ptr + (middle*4);
    if(*middle_ptr == search){
        return middle;
    }
    if(*middle_ptr > search){
        binarySearch(ptr, middle + 1, last, search);
    }else{
        binarySearch(ptr, first, middle - 1, search);
    }
    return 0;
}
    
int sum(int* ptr, int length){
    //prints sum
    int sum = 0;
    int i = 0;
    while(i < length){
        sum += *ptr;
        ptr += 4;
        i++; 
    }
    return sum;
}

3. A challenge I had during this project was actually printing the sum. 
   The recursive algorithm was pretty straightforward to implement. However,
   printing out the sum was tricky because the file is never ran, only
   the prodecure is referenced. Therefore there couldn't be any internal data in the file
   and in order to print strings, i had to modify the .data of this file to be globl. Another challenge I had
   was designing the program to correctly return to the original return address
   after recursion was finished. This was solved by ensuring that all recursive calls
   went to the stored return address in the stack, and that each stack frame was resolved
   sequentially.

4. What I liked about the assignment was the challenge to design binary search with
   many constraints. The algorithm is a very simple implementation in high level, 
   but with the constraints of a low level language, it made the process very fun. 
   Also, I liked how recursion was not as trivial as in other high level languages.
   Having to store the return address provided a fun challenge. 

5. I spent a couple hours on this assignment

6. No EC features