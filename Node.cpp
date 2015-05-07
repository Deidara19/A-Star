#include "Node.h"

Node::Node()
{
	C = 0;
	H = 0;
	visited = false;
	adyacent = new Node*[4];             // 0 = North, 1 = East, 2 = South, 3 = West
}

Node::~Node()
{
	//for (int i = 0; i < 4; i++)
	//	adyacent[i] = NULL;
	//delete[] adyacent;
}
