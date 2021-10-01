/**  
 * Egyptian Multiplication Algorithm
 * Author: Massimo Giusti
 * 10/01/2021
 */

#include <string>
#include <iostream>
#include <vector>
using namespace std;

/**
 * multiply: returns the product of 2 integers using the egyptian multiplication method
 * @ Params: num1, num2
 * @ Returns: Product
 */
int multiply(int num1, int num2){
    //use 2 vectors to store multiples of both ints
    vector<int> arr1;
    vector<int> arr2;
    int product = 0;
    
    //Store factors of num1 into arr1
    while(num1 >= 1){
        arr1.push_back(num1);
        num1 /= 2;
    }

    //multiply num2 n times and store into arr2
    //where n is the amount of times num1 is divisible by 2
    for(int i = 0; i < arr1.size(); i++){
        arr2.push_back(num2);
        //if the factor of num1 is odd, add the corresponding multiple of num2 to product
        if(arr1.at(i) % 2 == 1){
            product += num2;
        }
        num2 *= 2;
    }
    return product;       
}

int main(){
    int num1 = 0;
    int num2 = 0;
    cout << "Please enter 2 positive integers: " << endl;
    cin >> num1 >> num2;
    int product = multiply(num1, num2);
    cout << "The product is: " << product << endl;
}
