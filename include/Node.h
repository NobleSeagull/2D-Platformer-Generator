#ifndef _NODE_H
#define _NODE_H
#include <iostream>
#include <vector>

class Node
{
private:

	int m_x = -1;
	int m_y = -1;
	bool m_marked = false;

	Node * m_previous;

	std::vector<Node*> m_arcList;

public:

	Node(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	void X(int x) { m_x = x; };
	int X() { return m_x; };

	void Y(int y) { m_y = y; };
	int Y() { return m_y; };

	void AddArc(Node * dest) { m_arcList.push_back(dest); };
	std::vector<Node*> GetArcList() { return m_arcList; }

	void Prev(Node * x) { m_previous = x; };
	Node * Prev() { return m_previous; };

	void Marked(bool m) { m_marked = m; };
	bool Marked() { return m_marked; };

};
#endif