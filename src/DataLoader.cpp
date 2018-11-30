#include "DataLoader.h"

DataLoader::DataLoader()
{
	JSONReader tempData = JSONReader("prefabs/Data.json");
	for (int i = 0; i < tempData.getNoOfRooms(); i++)
	{
		JSONReader tempRoom = JSONReader("prefabs/rooms/" + tempData.getFileNameRoom(i));
		m_prefabRoom.push_back(new Prefab(tempData.getRoomName(i), tempData.getDifficulty(i), tempRoom.getRoom()));
	}
	for (int i = 0; i < tempData.getNoOfGoals(); i++)
	{
		JSONReader tempRoom = JSONReader("prefabs/rooms/" + tempData.getFileNameGoal(i));
		m_prefabGoal.push_back(new Prefab(tempData.getGoalName(i), 1, tempRoom.getGoal()));
	}
	for (int i = 0; i < tempData.getNoOfPortals(); i++)
	{
		JSONReader tempRoom = JSONReader("prefabs/portals/" + tempData.getFileNamePortal(i));
		if (tempData.getType(i) == 1)
		{
			m_prefabPortal.push_back(new Prefab(tempData.getPortalName(i), tempData.getType(i), tempRoom.getPortal()));
		}
		else
		{
			Map tempMap = Map(6, 16);
			Map tempMap2 = tempRoom.getPortal();

			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					tempMap.SetCell(i, j, tempMap2.GetCell(i, j));
				}
			}
			m_prefabPortal.push_back(new Prefab(tempData.getPortalName(i), tempData.getType(i), tempMap));
		}
	}
}

Map DataLoader::GetRoom(std::string x)
{
	Map tempRoom;
	for (int i = 0; i < m_prefabRoom.size(); i++)
	{
		if (m_prefabRoom.at(i)->Name() == x)
		{
			tempRoom = m_prefabRoom.at(i)->Room();
			break;
		}
	}
	return tempRoom;
}

Map DataLoader::GetRoom(int x)
{
	return m_prefabRoom.at(x)->Room();
}

int DataLoader::GetDifficulty(std::string x)
{
	int tempInt;
	for (int i = 0; i < m_prefabRoom.size(); i++)
	{
		if (m_prefabRoom.at(i)->Name() == x)
		{
			tempInt = m_prefabRoom.at(i)->Difficulty();
			break;
		}
	}
	return tempInt;
}
int DataLoader::GetDifficulty(int x)
{
	return m_prefabRoom.at(x)->Difficulty();
}

std::string DataLoader::GetNameRoom(int x)
{
	return m_prefabRoom.at(x)->Name();
}

int DataLoader::GetIDRoom(std::string x)
{
	int tempInt;
	for (int i = 0; i < m_prefabRoom.size(); i++)
	{
		if (m_prefabRoom.at(i)->Name() == x)
		{
			tempInt = i;
			break;
		}
	}
	return tempInt;
}



Map DataLoader::GetPortal(std::string x)
{
	Map tempRoom;
	for (int i = 0; i < m_prefabPortal.size(); i++)
	{
		if (m_prefabPortal.at(i)->Name() == x)
		{
			tempRoom = m_prefabPortal.at(i)->Room();
			break;
		}
	}
	return tempRoom;
}
Map DataLoader::GetPortal(int x)
{
	return m_prefabPortal.at(x)->Room();
}

int DataLoader::GetType(std::string x)
{
	int tempInt;
	for (int i = 0; i < m_prefabPortal.size(); i++)
	{
		if (m_prefabPortal.at(i)->Name() == x)
		{
			tempInt = m_prefabPortal.at(i)->Difficulty();
			break;
		}
	}
	return tempInt;
}
int DataLoader::GetType(int x)
{
	return m_prefabPortal.at(x)->Difficulty();
}

std::string DataLoader::GetNamePortal(int x)
{
	return m_prefabPortal.at(x)->Name();
}
int DataLoader::GetIDPortal(std::string x)
{
	int tempInt;
	for (int i = 0; i < m_prefabPortal.size(); i++)
	{
		if (m_prefabPortal.at(i)->Name() == x)
		{
			tempInt = i;
			break;
		}
	}
	return tempInt;
}

Map DataLoader::GetGoal(std::string x)
{
	Map tempRoom;
	for (int i = 0; i < m_prefabGoal.size(); i++)
	{
		if (m_prefabGoal.at(i)->Name() == x)
		{
			tempRoom = m_prefabGoal .at(i)->Room();
			break;
		}
	}
	return tempRoom;
}
Map DataLoader::GetGoal(int x)
{
	return m_prefabGoal.at(x)->Room();
}

std::string DataLoader::GetNameGoal(int x)
{
	return m_prefabGoal.at(x)->Name();
}
int DataLoader::GetIDGoal(std::string x)
{
	int tempInt;
	for (int i = 0; i < m_prefabGoal.size(); i++)
	{
		if (m_prefabGoal.at(i)->Name() == x)
		{
			tempInt = i;
			break;
		}
	}
	return tempInt;
}