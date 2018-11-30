#include "ManagedGridMap.h"

ManagedGridMap::ManagedGridMap(int x, int y)
{
	m_prefabs = new DataLoader();
	m_grid = new Map(x, y);
	m_mapLarge = new Map(x * 16, y * 16);

	m_width = x;
	m_height = y;

	GenerateGridFromScratch();
	ApplyMap();
}

void ManagedGridMap::ApplyPrefab(int x, int y, Map p)
{
	int k = 0;
	int l = 0;
	for (int i = (x * 16); i < (x * 16) + 16; i++)
	{
		for (int j = (y * 16); j < (y * 16) + 16; j++)
		{
			m_mapLarge->SetCell(i, j, p.GetCell(l, k));
			l++;
		}
		k++;
		l = 0;
	}
}

void ManagedGridMap::ResetGraph()
{

	for (int i = 0; i < m_graph.NoOfNodes(); i++)
	{
		delete m_graph.Nodes(i);
	}
	m_graph.Clear();

	for (int i = 0; i < m_grid->Width(); i++)
	{
		for (int j = 0; j < m_grid->Height(); j++)
		{
			m_graph.AddNode(i, j);
		}
	}
	for (int i = 0; i < m_grid->Width(); i++)
	{
		for (int j = 0; j < m_grid->Height(); j++)
		{
			if (i - 1 >= 0)
			{
				m_graph.Nodes(i, j)->AddArc(m_graph.Nodes(i - 1, j));
				std::cout << "|(" << i << "," << j << ")to" << "(" << i - 1 << "," << j << ")|";
			}
			if (j - 1 >= 0)
			{
				m_graph.Nodes(i, j)->AddArc(m_graph.Nodes(i, j - 1));
				std::cout << "|(" << i << "," << j << ")to" << "(" << i << "," << j - 1 << ")|";
			}
			if (i + 1 < m_grid->Height())
			{
				m_graph.Nodes(i, j)->AddArc(m_graph.Nodes(i + 1, j));
				std::cout << "|(" << i << "," << j << ")to" << "(" << i + 1 << "," << j << ")|";
			}
			if (j + 1 < m_grid->Width())
			{
				m_graph.Nodes(i, j)->AddArc(m_graph.Nodes(i, j + 1));
				std::cout << "|(" << i << "," << j << ")to" << "(" << i << "," << j + 1 << ")|";
			}
			std::cout << "" << std::endl;
		}
	}
}

void ManagedGridMap::GenerateGridFromScratch()
{
	for (int i = 0; i < m_width; i++)
	{
		//std::cout << "" << std::endl;
		for (int j = 0; j < m_height; j++)
		{
			int holder = rand() % m_prefabs->GetNoOfRooms();
			m_grid->SetCell(i, j, m_prefabs->GetNameRoom(holder));

			//std::cout << "(" << m_grid->GetCell(i, j) << ") ";
			m_meanPrefabDifficulty += m_prefabs->GetDifficulty(m_grid->GetCell(i, j));
		}
	}
	//std::cout << "" << std::endl;

	m_meanPrefabDifficulty = m_meanPrefabDifficulty / (m_width * m_height);

	//std::cout << "Mean Difficulty: " << m_meanPrefabDifficulty << std::endl;
}

void ManagedGridMap::MutateGrid()
{
	for (int i = 0; i < m_width; i++)
	{
		//std::cout << "" << std::endl;
		for (int j = 0; j < m_height; j++)
		{
			if (rand() % 3 > 1)
			{
				int holder = rand() % m_prefabs->GetNoOfRooms();
				m_grid->SetCell(i, j, m_prefabs->GetNameRoom(holder));
			}
			//std::cout << "(" << m_grid->GetCell(i, j) << ") ";
			m_meanPrefabDifficulty += m_prefabs->GetDifficulty(m_grid->GetCell(i, j));
		}
	}
	//std::cout << "" << std::endl;

	m_meanPrefabDifficulty = m_meanPrefabDifficulty / (m_width * m_height);

	ApplyMap();

	//std::cout << "Mean Difficulty: " << m_meanPrefabDifficulty << std::endl;
}

void ManagedGridMap::ApplyMap()
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			ApplyPrefab(i, j, m_prefabs->GetRoom(m_grid->GetCell(i, j)));
		}
	}

	for (int i = 0; i < m_width * 16; i++)
	{
		for (int j = 0; j < m_height * 16; j++)
		{
			if (i == 0 || i == (m_height * 16) - 1 || j == 0 || j == (m_width * 16) - 1)
			{
				m_mapLarge->SetCell(i, j, "X");
			}
		}
	}

	//for (int i = 0; i < m_height * 16; i++)
	//{
	//	for (int j = 0; j < m_width * 16; j++)
	//	{
	//		std::cout << m_mapLarge->GetCell(i, j) << " ";
	//	}
	//	std::cout << "" << std::endl;
	//}
}

void ManagedGridMap::ApplyHazards(int rate)
{
	for (int i = 0; i < m_width * 16; i++)
	{
		for (int j = 0; j < m_height * 16; j++)
		{
			if (m_mapLarge->GetCell(i, j) == "T")
			{
				int holder = rand() % rate;
				if (holder >= rate - 2)
				{
					m_mapLarge->SetCell(i, j, "H");
				}
			}
		}
	}
	for (int i = 0; i < 16; i++)
	{
		AdjacentHazards();
	}
	m_meanHazardDifficulty = 0;
	std::vector<int> x;
	std::vector<int> y;
	for (int i = 0; i < m_width * 16; i++)
	{
		for (int j = 0; j < m_height * 16; j++)
		{
			if (m_mapLarge->GetCell(i, j) == "H")
			{
				int holderX;
				int holderY;
				bool proceed = true;
				for (int k = 0; k < x.size(); k++)
				{
					holderX = i / 16;
					holderY = j / 16;
					if (holderX == x.at(k) && holderY == y.at(k))
					{
						proceed = false;
					}
				}
				if (proceed)
				{
					x.push_back(holderX);
					y.push_back(holderY);
				}
				m_meanHazardDifficulty++;
			}
		}
	}
	if (x.size() - 1 >= 1)
	{
		m_meanHazardDifficulty = m_meanHazardDifficulty / (x.size() - 1);
	}
	else
	{
		m_meanHazardDifficulty = 0;
	}
}

void ManagedGridMap::MutateHazards(int rate)
{
	if (rand() % 3 >= 1)
	{
		for (int i = 0; i < m_width * 16; i++)
		{
			for (int j = 0; j < m_height * 16; j++)
			{
				if (m_mapLarge->GetCell(i, j) == "H")
				{
					int holder = rand() % rate;
					if (holder >= rate - 2)
					{
						m_mapLarge->SetCell(i, j, "T");
					}
				}
			}
		}
		for (int i = 0; i < 16; i++)
		{
			for (int i = 0; i < m_width * 16; i++)
			{
				for (int j = 0; j < m_height * 16; j++)
				{
					if (m_mapLarge->GetCell(i, j) == "H")
					{
						if (i > 0 && m_mapLarge->GetCell(i - 1, j) == "T")
						{
							m_mapLarge->SetCell(i, j, "T");
						}
						else if (i < (m_height * 16) - 1 && m_mapLarge->GetCell(i + 1, j) == "H")
						{
							m_mapLarge->SetCell(i, j, "T");
						}
						else if (j > 0 && m_mapLarge->GetCell(i, j - 1) == "T")
						{
							m_mapLarge->SetCell(i, j, "T");
						}
						else if (j < (m_width * 16) - 1 && m_mapLarge->GetCell(i, j + 1) == "T")
						{
							m_mapLarge->SetCell(i, j, "T");
						}
					}
				}
			}
		}
	}
	else
	{
		ApplyHazards(rate);
	}
	m_meanHazardDifficulty = 0;
	std::vector<int> x;
	std::vector<int> y;
	for (int i = 0; i < m_width * 16; i++)
	{
		for (int j = 0; j < m_height * 16; j++)
		{
			if (m_mapLarge->GetCell(i, j) == "H")
			{
				m_meanHazardDifficulty++;
			}

			if (m_mapLarge->GetCell(i, j) == "H" || m_mapLarge->GetCell(i, j) == "T")
			{
				int holderX;
				int holderY;
				bool proceed = true;
				for (int k = 0; k < x.size(); k++)
				{
					holderX = i / 16;
					holderY = j / 16;
					if (holderX == x.at(k) && holderY == y.at(k))
					{
						proceed = false;
					}
				}
				if (proceed)
				{
					x.push_back(holderX);
					y.push_back(holderY);
				}
			}
		}
	}

	if (x.size() - 1 > 0)
	{
		m_meanHazardDifficulty = m_meanHazardDifficulty / (x.size() - 1);
	}
	else
	{
		m_meanHazardDifficulty = 0;
	}
}

void ManagedGridMap::AdjacentHazards()
{
	for (int i = 0; i < m_width * 16; i++)
	{
		for (int j = 0; j < m_height * 16; j++)
		{
			if (m_mapLarge->GetCell(i, j) == "T")
			{
				if (i > 0 && m_mapLarge->GetCell(i - 1, j) == "H")
				{
					m_mapLarge->SetCell(i, j, "H");
				}
				else if (i < (m_width * 16) - 1 && m_mapLarge->GetCell(i + 1, j) == "H")
				{
					m_mapLarge->SetCell(i, j, "H");
				}
				else if (j > 0 && m_mapLarge->GetCell(i, j - 1) == "H")
				{
					m_mapLarge->SetCell(i, j, "H");
				}
				else if (j < (m_height * 16) - 1 && m_mapLarge->GetCell(i, j + 1) == "H")
				{
					m_mapLarge->SetCell(i, j, "H");
				}
			}
		}
	}
}

void ManagedGridMap::GeneratePath()
{
	ResetGraph();
	int holderX;
	int holderY;

	holderX = rand() % m_width;
	holderY = 0;

	int z = rand() % m_prefabs->GetNoOfGoal();
	ApplyPrefab(holderX, holderY, m_prefabs->GetGoal(z));

	m_start = m_graph.Nodes(holderX, holderY);

	holderX = rand() % m_width;
	holderY = m_height - 1;

	z = rand() % m_prefabs->GetNoOfGoal();
	ApplyPrefab(holderX, holderY, m_prefabs->GetGoal(z));

	m_end = m_graph.Nodes(holderX, holderY);

	m_pathPoints.clear();

	m_pathPoints.push_back(m_start);

	for (int i = 1; i < m_height - 1; i++)
	{
		int holder = rand() % m_width;
		m_pathPoints.push_back(m_graph.Nodes(holder, i));
	}
	m_pathPoints.push_back(m_end);

	m_mapLarge;

	m_path.clear();
	std::vector<Node*> pathHolder;

	for (int i = 1; i < m_pathPoints.size(); i++)
	{
		pathHolder.clear();
		std::cout << "(" << m_pathPoints.at(i - 1)->X() << ", " << m_pathPoints.at(i - 1)->Y() << ") " << "to (" << m_pathPoints.at(i)->X() << ", " << m_pathPoints.at(i)->Y() << ")" << std::endl;
		pathHolder = m_graph.UCS(m_pathPoints.at(i-1)->X(), m_pathPoints.at(i-1)->Y(), m_pathPoints.at(i)->X(), m_pathPoints.at(i)->Y());
		for (int j = 0; j < pathHolder.size(); j++)
		{
			if (m_path.size() > 0)
			{
				if (m_path.back() != pathHolder.at(j))
				{
					m_path.push_back(pathHolder.at(j));
				}
			}
			else
			{
				m_path.push_back(pathHolder.at(j));
			}
		}
	}
	std::cout << "" << std::endl;

	std::cout << "Path ";
	for (int i = 0; i < m_path.size(); i++)
	{
		std::cout << "(" << m_path.at(i)->X() << "," << m_path.at(i)->Y() << ") ";
	}
	std::cout << "" << std::endl;

	m_pathLength = m_path.size();

	ApplyPath();
}

void ManagedGridMap::ApplyPath()
{
	for (int i = 0; i < m_path.size() - 1; i++)
	{
		if (m_path.at(i)->X() < m_path.at(i + 1)->X())
		{
			int temp = -1;
			while (temp == -1)
			{
				int rando = rand() % m_prefabs->GetNoOfPortal();
				if (m_prefabs->GetType(rando) == 1)
				{
					temp = rando;
				}
			}
			int k = 0;
			int l = 0;
			for (int v = (m_path.at(i)->X() * 16) + 13; v < (m_path.at(i)->X() * 16) + 19; v++)
			{
				for (int z = (m_path.at(i)->Y() * 16); z < (m_path.at(i)->Y() * 16) + 16; z++)
				{
					m_mapLarge->SetCell(z, v, m_prefabs->GetPortal(temp).GetCell(k, l));
					l++;
				}
				k++;
				l = 0;
			}
			std::cout << "Going Right" << std::endl;
		}
		else if (m_path.at(i)->X() > m_path.at(i + 1)->X())
		{
			int temp = -1;
			while (temp == -1)
			{
				int rando = rand() % m_prefabs->GetNoOfPortal();
				if (m_prefabs->GetType(rando) == 1)
				{
					temp = rando;
				}
			}
			int k = 0;
			int l = 0;
			for (int v = (m_path.at(i)->X() * 16) - 3; v < (m_path.at(i)->X() * 16) + 3; v++)
			{
				for (int z = (m_path.at(i)->Y() * 16); z < (m_path.at(i)->Y() * 16) + 16; z++)
				{
					m_mapLarge->SetCell(z, v, m_prefabs->GetPortal(temp).GetCell(k, l));
					l++;
				}
				k++;
				l = 0;
			}
			std::cout << "Going Left" << std::endl;
		}
		else if (m_path.at(i)->Y() < m_path.at(i + 1)->Y())
		{
			int temp = -1;
			while (temp == -1)
			{
				int rando = rand() % m_prefabs->GetNoOfPortal();
				if (m_prefabs->GetType(rando) == 2)
				{
					temp = rando;
				}
			}
			int k = 0;
			int l = 0;
			for (int v = (m_path.at(i)->X() * 16); v < (m_path.at(i)->X() * 16) + 16; v++)
			{
				for (int z = (m_path.at(i)->Y() * 16) + 13; z < (m_path.at(i)->Y() * 16) + 19; z++)
				{
					m_mapLarge->SetCell(z, v, m_prefabs->GetPortal(temp).GetCell(l, k));
					l++;
				}
				k++;
				l = 0;
			}
			std::cout << "Going Down" << std::endl;
		}
		else if (m_path.at(i)->Y() > m_path.at(i + 1)->Y())
		{
			int temp = -1;
			while (temp == -1)
			{
				int rando = rand() % m_prefabs->GetNoOfPortal();
				if (m_prefabs->GetType(rando) == 2)
				{
					temp = rando;
				}
			}
			int k = 0;
			int l = 0;
			for (int v = (m_path.at(i)->X() * 16); v < (m_path.at(i)->X() * 16) + 16; v++)
			{
				for (int z = (m_path.at(i)->Y() * 16) - 3; z < (m_path.at(i)->Y() * 16) + 3; z++)
				{
					m_mapLarge->SetCell(z, v, m_prefabs->GetPortal(temp).GetCell(l, k));
					l++;
				}
				k++;
				l = 0;
			}
			std::cout << "Going Up" << std::endl;
		}
	}

	for (int i = 0; i < m_width * 16; i++)
	{
		for (int j = 0; j < m_height * 16; j++)
		{
			if (i == 0 || i == (m_width * 16) - 1 || j == 0 || j == (m_height * 16) - 1)
			{
				m_mapLarge->SetCell(i, j, "X");
			}
		}
	}

	for (int i = 0; i < m_width * 16; i++)
	{
		for (int j = 0; j < m_height * 16; j++)
		{
			std::cout << m_mapLarge->GetCell(i, j) << " ";
		}
		std::cout << "" << std::endl;
	}
}

void ManagedGridMap::ApplyDeadEnds()
{
	for (int i = 0; i < m_width - 1; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			int temp = -1;
			while (temp == -1)
			{
				int rando = rand() % m_prefabs->GetNoOfPortal();
				if (m_prefabs->GetType(rando) == 1)
				{
					temp = rando;
				}
			}
			int k = 0;
			int l = 0;
			for (int v = (i * 16) + 13; v < (i * 16) + 19; v++)
			{
				for (int z = (j * 16); z < (j * 16) + 16; z++)
				{
					m_mapLarge->SetCell(v, z, m_prefabs->GetPortal(temp).GetCell(k, l));
					l++;
				}
				k++;
				l = 0;
			}
			std::cout << "Going Right" << std::endl;
		}
	}
}

void ManagedGridMap::ApplyLadders()
{
	for (int i = 0; i < 16; i++)
	{
		AdjacentLadders();
	}
}

void ManagedGridMap::AdjacentLadders()
{
	for (int i = 0; i < m_width * 16; i++)
	{
		for (int j = 0; j < m_height * 16; j++)
		{
			if (m_mapLarge->GetCell(i, j) == "L")
			{
				if (j + 1 < m_mapLarge->Height() && m_mapLarge->GetCell(i, j + 1) != "W" && m_mapLarge->GetCell(i, j+1) != "X")
				{
					m_mapLarge->SetCell(i, j + 1, "L");
				}
			}
		}
	}

}
