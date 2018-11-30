#include "Graph.h"

std::vector<Node*> Graph::UCS(int startX, int startY, int endX, int endY)
{
	std::queue<Node*> nodeQ;

	std::vector<Node*> path;
	std::vector<Node*> pathTemp;

	int start = 0;
	int end = 0;

	int valueTemp = 9999999;
	int value = 9999999;

	//Gets start point
	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes.at(i)->X() == startX && m_nodes.at(i)->Y() == startY)
		{
			start = i;
			break;
		}
	}

	//Gets end point
	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes.at(i)->X() == endX && m_nodes.at(i)->Y() == endY)
		{
			end = i;
			break;
		}
	}

	nodeQ.push(m_nodes.at(start));
	m_nodes.at(start)->Marked(true);

	while (nodeQ.size() != 0)
	{
		Node * holderA = nodeQ.front();
		int size = nodeQ.front()->GetArcList().size();
		for (int i = 0; i < size; i++)
		{
			if (holderA->GetArcList().at(i)->Marked() == false)
			{
				holderA->GetArcList().at(i)->Marked(true);
				nodeQ.push(holderA->GetArcList().at(i));
				holderA->GetArcList().at(i)->Prev(nodeQ.front());
			}
			if (holderA->GetArcList().at(i) == m_nodes.at(end))
			{
				pathTemp.clear();
				Node* holder = m_nodes.at(end);
				pathTemp.push_back(holder);
				while (holder != m_nodes.at(start))
				{
					holder = holder->Prev();
					pathTemp.push_back(holder);
				}
				valueTemp = 0;
				for (int j = 0; j < pathTemp.size(); j++)
				{
					valueTemp += 1;
				}
				if (valueTemp < value)
				{
					value = valueTemp;
					path.clear();
					path = pathTemp;
				}
			}
		}
		nodeQ.pop();
	}

	if (value > 900)
	{
		int j = 0;
	}

	std::vector<Node*> holder;
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes.at(i)->Marked(false);
	}

	for (int i = path.size()-1; i > -1; i--)
	{
		holder.push_back(path.at(i));
	}

	return holder;
}