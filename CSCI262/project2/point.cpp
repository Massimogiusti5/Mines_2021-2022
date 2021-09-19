/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    point.cpp

    code for the point class.

    Massimo Giusti
*/


#include "point.h"
#include <string>
using namespace std;

point::point(int x, int y, bool visited){
        this->x = x;
        this->y = y;
        this->visited = visited;
}