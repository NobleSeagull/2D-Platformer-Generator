#ifndef _MAP_H
#define _MAP_H
#include <iostream>
#include <vector>

class Map {
public:

	Map()
	{
		for (int i = 0; i < 1; i++)
		{
			m_cell.push_back(new std::vector<std::string*>());
			for (int j = 0; j < 1; j++)
			{
				m_cell.at(i)->push_back(new std::string("B"));
			}
		}
	}

	Map(int x, int y)
	{
		m_width = x;
		m_height = y;
		for (int i = 0; i < m_width; i++)
		{
			m_cell.push_back(new std::vector<std::string*>());
			for (int j = 0; j < m_height; j++)
			{
				m_cell.at(i)->push_back(new std::string("B"));
			}
		}
	};
	~Map() {};

	std::string GetCell(int x, int y)
	{
		return *m_cell.at(x)->at(y);
	};
	void SetCell(int x, int y, std::string value)
	{
		*m_cell.at(x)->at(y) = value;
	};

	int Width() { return m_width; };
	int Height() { return m_height; };

private:

	int m_width;
	int m_height;

	std::vector<std::vector<std::string*>*> m_cell;

};
#endif