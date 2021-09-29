/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    maze_solver.cpp

    Code for the maze_solver class.  This class will use stack-based depth
    first search or queue-based breadth first search to find a solution (if
    one exists) to a simple maze.

    C. Painter-Wakefield
*/

#include "maze_solver.h"
#include "point.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

//globals
stack<point> _stack;
queue<point> _queue;


/*
 _read_maze()

 Read in maze information (rows, columns, maze) from the provided input stream.
*/
void maze_solver::_read_maze(istream& in) {
	vector<char> temp = {};
	string str_stream = "";
	while(!in.eof()){
		getline(in, str_stream);
		_maze.push_back(str_stream);
	}
}


/*
 _write_maze()

 Output the (partially or totally solved) maze on cout.
*/
void maze_solver::_print_maze() {
	for(int i = 0; i < _maze.size(); i++){
		cout << _maze.at(i) << endl;
	}
}


/*
 _initialize()

 Find the start point.  Push or enqueue the start point.
*/
void maze_solver::_initialize() {
	for(int i = 0; i < _maze.size(); i++){
		for(int j = 0; j < _maze[i].size(); j++){
			if(_maze.at(i)[j] == 'o'){
				point p = point(i, j, false);
				if(_use_stack){
					_stack.push(p);
				}else{
					_queue.push(p);
				}
			}
		}
	}
}


/*
 _step()

 Take *one* step towards solving the maze, setting _no_more_steps and
 _goal_reached as appropriate.  This implements the essential maze search
 algorithm; take the next location from your stack or queue, mark the
 location with '@', add all reachable next points to your stack or queue,
 etc.

 
*/
void maze_solver::_step() {
	if(_use_stack){
		_step_with_stack();
	}else{
		_step_with_queue();
	}
}

//helper function for stack
void maze_solver::traverse_points_stack(int x, int y){
	if(_maze.at(x)[y] == '.' || _maze.at(x)[y] == '*'){
		point _new_point = point(x, y, false);
		_stack.push(_new_point);
	}
}

void maze_solver::_step_with_stack(){
//traversing with stack
	if (_stack.empty()){
		_no_more_steps = true;
		return;
	}
	point p = _stack.top();
	_stack.pop();
	if(_maze.at(p.row)[p.col] == '*'){
		_goal_reached = true;
		_no_more_steps = true;
		return;
	}
	//if p is visited ignore point
	if(p.visited ){
		_stack.pop();
	}else{
		//mark as visited
		if(_maze.at(p.row)[p.col] != 'o'){
			_maze.at(p.row)[p.col] = '@';
		}
		p.visited = true;
		//check for boundaries and valid point
		if(p.row != _maze.at(p.row).size()){
			traverse_points_stack(p.row+1,p.col);
		}
		if(p.col != _maze.size()){
			traverse_points_stack(p.row,p.col+1);
		}
		if(p.row != 0){
			traverse_points_stack(p.row-1,p.col);
		}
		if(p.col != 0){
			traverse_points_stack(p.row,p.col-1);
		}		
	}
}

void maze_solver::_step_with_queue(){
	//traversing with queue
	if (_queue.empty()){
		_no_more_steps = true;
		return;
	}
	point p = _queue.front();
	_queue.pop();
	if(_maze.at(p.row)[p.col] == '*'){
		_goal_reached = true;
		_no_more_steps = true;	
		return;
	}
	//if visited ignore point
	if(p.visited ){
		_queue.pop();
	}else{
		//set to visited
		if(_maze.at(p.row)[p.col] != 'o'){
			_maze.at(p.row)[p.col] = '@';
		}
		p.visited = true;
		//check for boundaries and valid point
		if(p.row != _maze.at(p.row).size()){
			traverse_points_queue(p.row+1,p.col);
		}
		if(p.col != _maze.size()){
			traverse_points_queue(p.row,p.col+1);
		}
		if(p.row != 0){
			traverse_points_queue(p.row-1,p.col);
		}
		if(p.col != 0){
			traverse_points_queue(p.row,p.col-1);
		}	
	}	
}



//helper function for queue
void maze_solver::traverse_points_queue(int x, int y){
	if(_maze.at(x)[y] == '.' || _maze.at(x)[y] == '*'){
		point _new_point = point(x, y, false);
		_queue.push(_new_point);
	}
}



/***************************************************************************
    You should not need to modify code below this point.  Touch at your own
    risk!
****************************************************************************/

/*
 maze_solver constructor

 You should not need to modify this.  It opens the maze file and passes
 the input stream to read_maze(), along with setting up some internal state
 (most importantly, the variable telling you whether to use a stack or
 a queue).
*/
maze_solver::maze_solver(string infile, bool use_stak, bool pause) {
	_use_stack = use_stak;
	_do_pause = pause;

	_no_more_steps = false;
	_goal_reached = false;

	// parse out maze name for later use in creating output file name
	int pos = infile.find(".");
	if (pos == string::npos) {
		_maze_name = infile;
	} else {
		_maze_name = infile.substr(0, pos);
	}

	// open input file and read in maze
	ifstream fin(infile);

	_read_maze(fin);

	fin.close();
}

/*
 run()

 Initializes the maze_solver, then runs a loop to keep moving forward towards
 a solution.

 While more steps are possible (while no_more_steps == false), run() calls
 step(), then calls print_maze(), then pause().  Once there are no more steps,
 it prints a success/failure message to the user (based on the goal_reached 
 flag) and writes the final maze to a solution file.
*/

void maze_solver::run() {
    _initialize();

	cout << "Solving maze '" << _maze_name << "'." << endl;
	cout << "Initial maze: " << endl << endl;
	_print_maze();
	cout << endl;
	_pause();

	// main loop
	while (!_no_more_steps) {
		_step();
		cout << endl;
		_print_maze();
		cout << endl;
		_pause();
	}

	// final output to user
	cout << "Finished: ";
	if (_goal_reached) {
		cout << "goal reached!" << endl;
	} else {
		cout << "no solution possible!" << endl;
	}
}


/*
 pause()

 Pauses execution until user hits enter (unless do_pause == false).
*/
void maze_solver::_pause() {
	if (!_do_pause) return;
	string foo;
	cout << "Hit Enter to continue...";
	getline(cin, foo);
}

