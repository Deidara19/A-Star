#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include<iostream>

using namespace std;

class Node
{
	public:
		int C, H;                 // C = Cost, H = Heuristic
		bool visited;             // Marks if the node is visited (1 for Visited & 0 for !Visited).
		Node **adyacent;          /* Adyacent Nodes of the current node, 
							      each node contains 4 directional pads
								  (North, East, South and West) */
		Node();
		~Node();
};

#endif
