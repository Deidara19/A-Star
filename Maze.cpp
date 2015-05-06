#include "Maze.h"

Maze::Maze()
{
	solution_size = 0;
	rows = 0;
	cols = 0;
	readInput();
}

Maze::~Maze()
{
	for (int i = 0; i < rows; i++)
			delete[] M[i];
	delete[] M;
}

void Maze::readInput()
{

}
