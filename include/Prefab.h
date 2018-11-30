#ifndef _PREFAB_H
#define _PREFAB_H
#include "Map.h"

class Prefab
{
private:

	int m_difficulty;
	std::string m_name;
	Map m_room;

public:
	Prefab(std::string name, int difficulty, Map r)
	{
		m_name = name;
		m_difficulty = difficulty;
		m_room = r;
	};
	~Prefab() {};

	Map Room() { return m_room; };
	int Difficulty() { return m_difficulty; };
	std::string Name() { return m_name; };

};
#endif

