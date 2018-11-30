#pragma once
#include "ManagedGridMap.h"
class GeneticAlgMapGenerator
{
public:
	GeneticAlgMapGenerator();
	~GeneticAlgMapGenerator();

	ManagedGridMap Generate(int width, int height, int difficulty, int poolDepth);

};

