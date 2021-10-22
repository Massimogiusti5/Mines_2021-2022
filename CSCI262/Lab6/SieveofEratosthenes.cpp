/**  
 * Finding Prime Numbers: Sieve of Estosthenes
 * Author: Massimo Giusti
 * 10/01/2021
 */

#include <string>
#include <iostream>
#include <vector>
using namespace std;

/**
 * getPrimes: given an integer, finds all prime numbers less than that number
 * @ Input: int num
 * @ Output: vector<int> result: vector with all the prime numbers
 */
vector<int> getPrimes(int num){
    vector<int> nums;
    vector<int> result;
    //make data structure to hold all ints [2,n]
    for(int i = 2; i <= num; i++){
        nums.push_back(i);
    }

    //main loop that identifies the prime numbers
    for(int i = 2; i <= num; i++){
        //for all multiples of i, set value at index to zero
        if(2*i <= num){   
            for(int j = 2*i; j <= num; j += i){
                //value is set to zero because multiple erasures with iterators doesn't work
                nums.at(j-2) = 0;
            }   
        }
    }

    //for all remaining numbers (primes), add to result vector
    for(int i = 0; i < nums.size(); i++){
        if(nums.at(i) != 0){
            result.push_back(nums.at(i));
        }
    }

    return result;
}

int main(){
    int num = 0;
    cout << "Please enter a maximum number: ";
    cin >> num;
    vector<int> result = getPrimes(num);
    for(int i = 0; i < result.size(); i++){
        cout << result.at(i) << " ";
    }
    cout << endl;
}