/*
    Queue.cpp
        
    Method implementations for Queue class

    assignment: CSCI 262 Lab - Queues, part 1        

    author: 

    last modified: 9/7/2017
*/

/* 
   NOTE: if you prefer, the Queue class is simple enough that you can do all
   of your methods inline.  In that case, you can remove this file.
*/

#include "Queue.h"
using namespace std;

bool Queue::enqueue(char c){
    if (size() != ARRAY_SZ){
        _data[_back] = c;
        _back++;
        return true;
    }
    return false;
}

bool Queue::dequeue(){
    if(size() != 0){
        _front++;
        return true;
    }
    return false;
}

