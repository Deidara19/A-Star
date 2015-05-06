#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include "Node.h"

class Maze
{
	public:
		int x[100], y[100], solution_size;    // Store the coordinates of each step of the solution
		Node **M;                             // Store the maze.
		int rows, cols;                       // Height of the maze (Rows and Columns)

		Maze();
		~Maze();

		void readInput();
};

#endif
