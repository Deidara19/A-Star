#include "Maze.h"

Maze::Maze()
{
	solution_size = 0;
	rows = 0;
	cols = 0;
	costo = 0;
	readInput();
	//auxx = start.x;
	//auxy = start.y;
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
		setAdjacencies();
		heuristic();

		/*
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				cout << M[i][j].H << " ";
			cout << endl;
		}
			*/

		astar(start.x, start.y);
		cout << endl;
	}

	input.close();
}

void Maze::setAdjacencies()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{

		if (i - 1 >= 0)
		{
			if (M[i - 1][j].C != -1)
				M[i][j].adyacent[0] = &M[i - 1][j];

			else
				M[i][j].adyacent[0] = NULL;
		}
		else
			M[i][j].adyacent[0] = NULL;

		if (j + 1 < cols)
		{
			if (M[i][j + 1].C != -1)
				M[i][j].adyacent[1] = &M[i][j + 1];

			else
				M[i][j].adyacent[1] = NULL;
		}
		else
			M[i][j].adyacent[1] = NULL;

		if (i + 1 < rows)
		{
			if (M[i + 1][j].C != -1)
				M[i][j].adyacent[2] = &M[i + 1][j];

			else
				M[i][j].adyacent[2] = NULL;
		}
		else
			M[i][j].adyacent[2] = NULL;

		if (j - 1 >= 0)
		{
			if (M[i][j - 1].C != -1)
				M[i][j].adyacent[3] = &M[i][j - 1];

			else
				M[i][j].adyacent[3] = NULL;
		}
		else
			M[i][j].adyacent[3] = NULL;

		}
}

void Maze::printMaze()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << "(" << i << ", " << j << ") COSTOS ADY:" << endl;
			for (int k = 0; k < 4; k++)
			{
				if (M[i][j].adyacent[k] != NULL)
					cout << M[i][j].adyacent[k]->C << " ";

				else
					cout << "NULL ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

int Maze::abs(int x)
{
	if (x<0)
		x *= -1;
	return x;
}

void Maze::heuristic()
{
	//cout<<final.x<<endl<<final.y<<endl;
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols; j++)
			M[i][j].H = abs(final.x - i) + abs(final.y - j);

}

void Maze::astar(int auxx, int auxy)
{
	cout << auxx << ", " << auxy << endl;
	if (auxx == final.x && auxy == final.y) return;
	Node *aux;
	aux = NULL;
	int csm = 0;
	int costo_aux = 10000000;

	for (int i = 0; i < 4; i++) // es 4 porque horacio se le da la puta gana, hdp, report pls, fucking peruvian
	{
		if (M[auxx][auxy].adyacent[i] != NULL)
		{
			if (M[auxx][auxy].adyacent[i]->C + M[auxx][auxy].adyacent[i]->H < costo_aux)
			{
				aux = M[auxx][auxy].adyacent[i];
				csm = i;
				costo_aux = M[auxx][auxy].adyacent[i]->C + M[auxx][auxy].adyacent[i]->H;
			}
		}
	}

	costo += aux->C;

	if (csm == 0)
		auxx -= 1;
	else if (csm == 1)
		auxy += 1;
	else if (csm == 2)
		auxx += 1;
	else if (csm == 3)
		auxy -= 1;

	aux->visited = true;

	astar(auxx, auxy);
}
