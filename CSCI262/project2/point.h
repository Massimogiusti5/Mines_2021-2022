/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    point.h

    Class declaration for the point class.

    Massimo Giusti
*/

#ifndef _POINT_H
#define _POINT_H

using namespace std;

class point{
    public:
        int row;
        int col;
        bool visited;
        point(int row, int col, bool visited);
};

#endif