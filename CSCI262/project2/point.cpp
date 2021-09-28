/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    point.cpp

    code for the point class.

    Massimo Giusti
*/


#include "point.h"
#include <string>
using namespace std;

point::point(int row, int col, bool visited){
        this->row = row;
        this->col = col;
        this->visited = visited;
}