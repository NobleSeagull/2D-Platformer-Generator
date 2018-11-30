#ifndef _GRAPH_H
#define _GRAPH_H

#include "Node.h"
#include <vector>
#include <iostream>
#include <queue>

class Graph
{
private:

	std::vector<Node*> m_nodes;

public:

	Graph() {};

	std::vector<Node*> UCS(int startX, int startY, int endX, int endY);

	Node * Nodes(int x, int y) 
	{ 
		Node * holder = m_nodes.at(0);
		for (int i = 0; i < m_nodes.size(); i++)
		{
			if (m_nodes.at(i)->X() == x && m_nodes.at(i)->Y() == y)
			{
				holder = m_nodes.at(i);
			}
		}
		return holder;
	};
	Node * Nodes(int x) { return m_nodes.at(x); };
	void AddNode(int x, int y) { m_nodes.push_back(new Node(x, y));};

	void Clear() { m_nodes.clear(); };

	int NoOfNodes() { return m_nodes.size(); };

};
#endif