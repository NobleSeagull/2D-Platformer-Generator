#ifndef _JSONREADER_H
#define _JSONREADER_H

#include "JSON.h"
#include "Map.h"
#include <fstream>
#include <iostream>

class JSONReader {
public:

	JSONReader(std::string const & filename);
	~JSONReader();

	void load(std::string const & filename);

	Map getRoom();
	Map getGoal();
	Map getPortal();

	int getNoOfRooms();
	int getNoOfPortals();
	int getNoOfGoals();

	std::string getFileNameRoom(int x);
	std::string getFileNamePortal(int x);
	std::string getFileNameGoal(int x);

	std::string getRoomName(int x);
	std::string getPortalName(int x);
	std::string getGoalName(int x);

	int getDifficulty(int x);
	int getType(int x);

private:
	JSONValue *m_value;
	std::string m_JSONData;

	void loadJSONData(std::string const & filename);

	// Utility methods.
	JSONObject getTopLevelJSONObject();
	std::string wStringToString(std::wstring const & wstr);
};
#endif