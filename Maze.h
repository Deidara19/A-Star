#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include "Node.h"
#include "Point2D.h"
#include<fstream>

class Maze
{
public:
	Point2D *solution;                    // Store the coordinates of each step of the solution
	int solution_size;
	Point2D start, final;
	Node **M;                             // Store the maze.
	int rows, cols;                       // Height of the maze (Rows and Columns)
	int costo;
	//int auxx, auxy;

	Maze();
	~Maze();

	void readInput();
	void printMaze();
	void setAdjacencies();
	void heuristic();
	int  abs(int x);
	void astar(int auxx, int auxy);
};

#endif
