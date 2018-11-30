#include "stdafx.h"
#include "JSONReader.h"

////////////////////////////////////////////////////////////
JSONReader::JSONReader(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}
}

////////////////////////////////////////////////////////////
JSONReader::~JSONReader() {
	delete m_value;
}

////////////////////////////////////////////////////////////
void JSONReader::load(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}

}

////////////////////////////////////////////////////////////
void JSONReader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	// Loads all the data in the file into a std::string.
	std::ifstream myfile(filename);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			m_JSONData.append(line);
		}
		myfile.close();
	}
	else
	{
		std::string errorMessage = "Could not open " + filename + " exiting!";
		std::cout << "Could not open " + filename + " exiting!" << std::endl;
		throw std::exception(errorMessage.c_str());
	}
}

////////////////////////////////////////////////////////////
JSONObject JSONReader::getTopLevelJSONObject() {
	// Retrieve the main (root) object
	JSONObject root;

	if (m_value->IsObject() == false)
	{
		throw std::exception("Problem with root element in json file, exiting");
	}
	root = m_value->AsObject();

	return root;
}

////////////////////////////////////////////////////////////
std::string JSONReader::wStringToString(std::wstring const & wstr)
{
	std::string s(wstr.begin(), wstr.end());
	return s;
}


Map JSONReader::getRoom()
{
	Map tempRoom = Map(16, 16);
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();
	for (int i = 0; i < 16; i++)
	{
		std::string word("Row" + std::to_string(i));
		std::wstring wWord;
		wWord.assign(word.begin(), word.end());
		JSONObject row = root[wWord]->AsObject();
		for (int j = 0; j < 16; j++)
		{
			std::string word2(std::to_string(j));
			std::wstring wWord2;
			wWord2.assign(word2.begin(), word2.end());
			std::wstring holder(row[wWord2]->AsString());
			std::string holderString(holder.begin(), holder.end());
			tempRoom.SetCell(i, j, holderString);
			std::cout << " " << holderString;
		}
		std::cout << "" << std::endl;
	}
	return tempRoom;
}

Map JSONReader::getGoal()
{
	Map tempRoom = Map(16, 16);
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();
	for (int i = 0; i < 16; i++)
	{
		std::string word("Row" + std::to_string(i));
		std::wstring wWord;
		wWord.assign(word.begin(), word.end());
		JSONObject row = root[wWord]->AsObject();
		for (int j = 0; j < 16; j++)
		{
			std::string word2(std::to_string(j));
			std::wstring wWord2;
			wWord2.assign(word2.begin(), word2.end());
			std::wstring holder(row[wWord2]->AsString());
			std::string holderString(holder.begin(), holder.end());
			tempRoom.SetCell(i, j, holderString);
			std::cout << " " << holderString;
		}
		std::cout << "" << std::endl;
	}
	return tempRoom;
}

Map JSONReader::getPortal()
{
	Map tempRoom = Map(6, 16);
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();
	for (int i = 0; i < 16; i++)
	{
		std::string word("Row" + std::to_string(i));
		std::wstring wWord;
		wWord.assign(word.begin(), word.end());
		JSONObject row = root[wWord]->AsObject();
		for (int j = 0; j < 6; j++)
		{
			std::string word2(std::to_string(j));
			std::wstring wWord2;
			wWord2.assign(word2.begin(), word2.end());
			std::wstring holder(row[wWord2]->AsString());
			std::string holderString(holder.begin(), holder.end());
			tempRoom.SetCell(j, i, holderString);
			std::cout << " " << holderString;
		}
		std::cout << "" << std::endl;
	}
	return tempRoom;
}

int JSONReader::getNoOfRooms()
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("NoOfRooms");
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	int holderInt = std::stoi(root[wWord]->AsString());
	return holderInt;
}

int JSONReader::getNoOfPortals()
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("NoOfPortals");
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	int holderInt = std::stoi(root[wWord]->AsString());
	return holderInt;
}

int JSONReader::getNoOfGoals()
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("NoOfGoals");
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	int holderInt = std::stoi(root[wWord]->AsString());
	return holderInt;
}

std::string JSONReader::getFileNameRoom(int x)
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("Room" + std::to_string(x));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject row = root[wWord]->AsObject();
	std::string word2("FileName");
	std::wstring wWord2;
	wWord2.assign(word2.begin(), word2.end());
	std::wstring holder(row[wWord2]->AsString());
	std::string holderString(holder.begin(), holder.end());
	std::cout << "FileName: " << holderString << std::endl;
	return holderString;
}

std::string JSONReader::getFileNamePortal(int x)
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("Port" + std::to_string(x));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject row = root[wWord]->AsObject();
	std::string word2("FileName");
	std::wstring wWord2;
	wWord2.assign(word2.begin(), word2.end());
	std::wstring holder(row[wWord2]->AsString());
	std::string holderString(holder.begin(), holder.end());
	std::cout << "FileName: " << holderString << std::endl;
	return holderString;
}

std::string JSONReader::getFileNameGoal(int x)
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("Goal" + std::to_string(x));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject row = root[wWord]->AsObject();
	std::string word2("FileName");
	std::wstring wWord2;
	wWord2.assign(word2.begin(), word2.end());
	std::wstring holder(row[wWord2]->AsString());
	std::string holderString(holder.begin(), holder.end());
	std::cout << "FileName: " << holderString << std::endl;
	return holderString;
}

std::string JSONReader::getRoomName(int x)
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("Room" + std::to_string(x));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject row = root[wWord]->AsObject();
	std::string word2("Name");
	std::wstring wWord2;
	wWord2.assign(word2.begin(), word2.end());
	std::wstring holder(row[wWord2]->AsString());
	std::string holderString(holder.begin(), holder.end());
	std::cout << "Name: " << holderString << std::endl;
	return holderString;
}

std::string JSONReader::getGoalName(int x)
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("Goal" + std::to_string(x));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject row = root[wWord]->AsObject();
	std::string word2("Name");
	std::wstring wWord2;
	wWord2.assign(word2.begin(), word2.end());
	std::wstring holder(row[wWord2]->AsString());
	std::string holderString(holder.begin(), holder.end());
	std::cout << "Name: " << holderString << std::endl;
	return holderString;
}

std::string JSONReader::getPortalName(int x)
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("Port" + std::to_string(x));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject row = root[wWord]->AsObject();
	std::string word2("Name");
	std::wstring wWord2;
	wWord2.assign(word2.begin(), word2.end());
	std::wstring holder(row[wWord2]->AsString());
	std::string holderString(holder.begin(), holder.end());
	std::cout << "Name: " << holderString << std::endl;
	return holderString;
}

int JSONReader::getDifficulty(int x)
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("Room" + std::to_string(x));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject row = root[wWord]->AsObject();
	std::string word2("Difficulty");
	std::wstring wWord2;
	wWord2.assign(word2.begin(), word2.end());
	int holderInt = std::stoi(row[wWord2]->AsString());
	std::cout << "Difficulty: " << holderInt << std::endl;
	return holderInt;
}

int JSONReader::getType(int x)
{
	JSONObject root = getTopLevelJSONObject();
	std::string word("Port" + std::to_string(x));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject row = root[wWord]->AsObject();
	std::string word2("Type");
	std::wstring wWord2;
	wWord2.assign(word2.begin(), word2.end());
	int holderInt = std::stoi(row[wWord2]->AsString());
	std::cout << "Type: " << holderInt << std::endl;
	return holderInt;
}