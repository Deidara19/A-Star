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
	char coma;

	ifstream input("Examen2-1.txt");

	input >> rows;
	input >> cols;

	M = new Node*[rows];
	for (int i = 0; i < rows; i++)
		M[i] = new Node[cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			input >> M[i][j].C;

	setAdjacencies();

	while (input >> start.x >> coma >> start.y >> final.x >> coma >> final.y)
	{
		/* AQUÍ SE MANDA A LLAMAR LA FUNCIÓN */
	}
		
	input.close();
}

void Maze::setAdjacencies()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (i - 1 > 0)
			{
				if (M[i - 1][j].C != -1)
					M[i][j].adyacent[0] = &M[i - 1][j];

				else
					M[i][j].adyacent[0] = NULL;
			}
			
			if (j + 1 < cols)
			{
				if (M[i][j + 1].C != -1)
					M[i][j].adyacent[1] = &M[i][j + 1];

				else
					M[i][j].adyacent[1] = NULL;
			}

			if (i + 1 < rows)
			{
				if (M[i + 1][j].C != -1)
					M[i][j].adyacent[2] = &M[i + 1][j];

				else
					M[i][j].adyacent[2] = NULL;
			}
			
			if (j - 1 > 0)
			{
				if (M[i][j - 1].C != -1)
					M[i][j].adyacent[3] = &M[i][j - 1];

				else
					M[i][j].adyacent[3] = NULL;
			}
		}	
}

void Maze::printMaze()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << M[i][j].C << ' ';
		cout << endl;
	}
}

int Maze::abs(int x)
{
    if(x<0)
        x*=-1;
    return x;
}

void Maze::heuristic()
{
    //cout<<final.x<<endl<<final.y<<endl;
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
             M[i][j].H = abs(final.x - i) + abs(final.y - j);

}
