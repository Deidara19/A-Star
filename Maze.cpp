#include "Maze.h"
Maze::Maze()
{
	solution_size = 0;
	rows = 0;
	cols = 0;
	costo = 0;
	asd = 0;
	//auxx = start.x;
	//auxy = start.y;
}

Maze::~Maze()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			for (int k = 0; k < 4; k++)
				M[i][j].adyacent[k] = NULL;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			delete[] M[i][j].adyacent;

	for (int i = 0; i < rows; i++)
		delete[] M[i];
	delete[] M;
}

void Maze::printMaze()
{
	cout << "Laberinto Inicial:" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j<cols; j++)
			cout << setw(3) << M[i][j].C;
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

void Maze::readInput(char *fileName)
{
	char coma;

	ifstream input(fileName);

	input >> rows;
	input >> cols;

	M = new Node*[rows];
	for (int i = 0; i < rows; i++)
		M[i] = new Node[cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
		input >> M[i][j].C;
		M[i][j].i = i;
		M[i][j].j = j;
		}

	setAdjacencies();
	printMaze();

	cout << "\nAlgoritmo A*:" << endl;
	while (input >> start.x >> coma >> start.y >> final.x >> coma >> final.y)
	{
		cout << "Salida: (" << start.x << ", " << start.y << ")     ";
		cout << "Meta: (" << final.x << ", " << final.y << ")" << endl;

		start.x--;
		start.y--;
		final.x--;
		final.y--;

		heuristic();   // Heurísticas
		/*
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j<cols; j++)
				cout << setw(3) << M[i][j].H;
			cout << endl;
		}
		*/

		cout << "Recorrido:" << endl;
		S.push(M[start.x][start.y]);
		/* AQUÍ SE MANDA A LLAMAR LA FUNCIÓN */
		astar(start.x, start.y);
		costo = 0;
		asd = 0;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				M[i][j].visited = false;

		while (!S.empty())
		{
			cout << "(" << S.top().i + 1 << ", " << S.top().j + 1 << ") -> ";
			costo += S.top().C;
			if (S.top().i == start.x && S.top().j == start.y)
				costo -= S.top().C;
			S.pop();
		}

		cout << "Costo Final: " << costo << endl << endl;
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


void Maze::astar(int auxx, int auxy)
{
	if (auxx == final.x && auxy == final.y) return;
	Node *aux;
	aux = NULL;
	int csm = 4;
	int costo_aux = 10000000;

	for (int i = 0; i < 4; i++) // es 4 porque horacio se le da la puta gana, hdp, report pls, fucking peruvian
	{
		if (M[auxx][auxy].adyacent[i] != NULL)
			if (M[auxx][auxy].adyacent[i]->visited == false)
				if (asd + M[auxx][auxy].adyacent[i]->H < costo_aux)
				{
					aux = M[auxx][auxy].adyacent[i];
					csm = i;
					costo_aux = asd + M[auxx][auxy].adyacent[i]->H;
				}
	}

	if (csm != 4)
		asd += M[auxx][auxy].adyacent[csm]->C;

	if (csm == 0)
	{
		auxx -= 1;
		S.push(M[auxx][auxy]);
		M[auxx][auxy].visited = true;
	}

	else if (csm == 1)
	{
		auxy += 1;
		S.push(M[auxx][auxy]);
		M[auxx][auxy].visited = true;
	}

	else if (csm == 2)
	{
		auxx += 1;
		S.push(M[auxx][auxy]);
		M[auxx][auxy].visited = true;
	}
	else if (csm == 3)
	{
		auxy -= 1;
		S.push(M[auxx][auxy]);
		M[auxx][auxy].visited = true;
	}
	else
	{
		S.pop();
		aux = &S.top();
		auxx = aux->i;
		auxy = aux->j;
	}

	astar(auxx, auxy);
}
