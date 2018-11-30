#ifndef _DATALOADER_H
#define _DATALOADER_H

#include "JSONReader.h"
#include "Prefab.h"

class DataLoader 
{
public:

	DataLoader();
	~DataLoader() {};

	//Rooms
	Map GetRoom(std::string x);
	Map GetRoom(int x);

	int GetDifficulty(std::string x);
	int GetDifficulty(int x);

	std::string GetNameRoom(int x);
	int GetIDRoom(std::string x);

	int GetNoOfRooms() { return m_prefabRoom.size(); };


	//Portals
	Map GetPortal(std::string x);
	Map GetPortal(int x);

	int GetType(std::string x);
	int GetType(int x);

	std::string GetNamePortal(int x);
	int GetIDPortal(std::string x);

	int GetNoOfPortal() { return m_prefabPortal.size(); };

	//Goals
	Map GetGoal(std::string x);
	Map GetGoal(int x);

	std::string GetNameGoal(int x);
	int GetIDGoal(std::string x);

	int GetNoOfGoal() { return m_prefabGoal.size(); };

private:
	std::vector<Prefab*> m_prefabRoom;
	std::vector<Prefab*> m_prefabPortal;
	std::vector<Prefab*> m_prefabGoal;
};
#endif