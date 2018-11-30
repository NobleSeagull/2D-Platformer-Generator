#ifndef _MANAGEDGRIDMAP_H
#define _MANAGEDGRIDMAP_H

#include <random>
#include <time.h>
#include <utility>

#include "Map.h"
#include "DataLoader.h"
#include "Graph.h"

//This class manages the map in it's early stages. It generates the map's parts and applies it to a larger grid.

class ManagedGridMap
{
public:
	ManagedGridMap(int x, int y);
	~ManagedGridMap() {};

	void ApplyPrefab(int x, int y, Map p);
	void ResetGraph();

	void GenerateGridFromScratch();
	void MutateGrid();

	void ApplyMap();

	void ApplyHazards(int rate);
	void MutateHazards(int rate);
	void AdjacentHazards();

	void ApplyLadders();
	void AdjacentLadders();

	void GeneratePath();

	void ApplyPath();
	void ApplyDeadEnds();

	int PrefabDifficulty() { return m_meanPrefabDifficulty; };
	int HazardDifficulty() { return m_meanHazardDifficulty; };
	int PathLength() { return m_pathLength; };

	int Width() { return m_width; };
	int Height() { return m_height; };
	Map LargeMap() { return * m_mapLarge; };

private:

	DataLoader * m_prefabs;
	Map* m_grid;
	Map* m_mapLarge;

	Graph m_graph;

	int m_width;
	int m_height;

	int m_meanPrefabDifficulty;
	int m_meanHazardDifficulty;
	int m_pathLength;

	Node* m_start;
	Node* m_end;
	std::vector<Node*> m_pathPoints;

	std::vector<Node*> m_path;

};
#endif

class Point
{
public:

	Point() { x = 0; y = 0; };

	int x;
	int y;
};