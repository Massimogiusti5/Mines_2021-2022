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
    if (_size != ARRAY_SZ){
        _data[_back] = c;
        _back++;
        _back = _back % 6;
        _size++;
        return true;
    }
    return false;
}

bool Queue::dequeue(){
    if(size() != 0){
        _front++;
        _front = _front % 6;
        _size--;
        return true;
    }
    return false;
}

char Queue::front(){
    return _data[_front];
}

bool Queue::is_empty(){
    return (_size == 0);
}

int Queue::size(){
    return _size;
}