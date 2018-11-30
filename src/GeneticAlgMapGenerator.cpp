#include "GeneticAlgMapGenerator.h"



GeneticAlgMapGenerator::GeneticAlgMapGenerator()
{


}

GeneticAlgMapGenerator::~GeneticAlgMapGenerator()
{
}

ManagedGridMap GeneticAlgMapGenerator::Generate(int width, int height, int difficulty, int poolDepth)
{
	
	ManagedGridMap holder = ManagedGridMap(width, height);
	bool resultNotAchieved = true;
	while (resultNotAchieved)
	{
		std::cout << "Starting Anew" << std::endl;
		holder.GenerateGridFromScratch();

		std::vector<ManagedGridMap> temps;
		for (int i = 0; i < poolDepth; i++)
		{
			temps.push_back(holder);
		}

		int value = -10;
		int loop = 0;
		std::cout << "Mutating Grid : [";
		while (value != difficulty - 1 && value != difficulty && value != difficulty + 1 && loop <= 50)
		{
			int holderValue = 10000;
			int index = -1;
			for (int i = 0; i < poolDepth; i++)
			{
				temps.at(i).MutateGrid();
				int temp = difficulty - temps.at(i).PrefabDifficulty();
				if (temp <= 0)
				{
					temp *= -1;
				}
				if (temp < holderValue)
				{
					holderValue = temp;
					value = temps.at(i).PrefabDifficulty();
					index = i;
				}
			}
			holder = temps.at(index);
			temps.clear();
			for (int i = 0; i < poolDepth; i++)
			{
				temps.push_back(holder);
			}
			std::cout << "#";
			loop++;
		}
		for (int i = 0; i < 50 - loop; i++)
		{
			std::cout << "#";
		}
		std::cout << "]" << std::endl;

		holder.GeneratePath();
		holder.ApplyPath();
		holder.ApplyDeadEnds();
		temps.clear();
		for (int i = 0; i < poolDepth; i++)
		{
			temps.push_back(holder);
		}

		value = -10;
		loop = 0;
		holder.ApplyHazards(difficulty);
		temps.clear();
		for (int i = 0; i < poolDepth; i++)
		{
			temps.push_back(holder);
		}
		std::cout << "Mutating Hazards: [";
		while (value != difficulty - (loop / 10) && value != difficulty && value != difficulty + (loop / 10) && loop <= 50)
		{
			std::cout << "N";
			int holderValue = 10000;
			int index = -1;
			for (int i = 0; i < poolDepth; i++)
			{
				temps.at(i).MutateHazards(difficulty);
				int temp = difficulty - temps.at(i).HazardDifficulty();
				if (temp <= 0 && temps.at(i).HazardDifficulty() >= difficulty)
				{
					temp *= -1;
				}
				if (temp < holderValue)
				{
					holderValue = temp;
					value = temps.at(i).HazardDifficulty();
					index = i;
				}
			}
			holder = temps.at(index);
			temps.clear();
			for (int i = 0; i < poolDepth; i++)
			{
				temps.push_back(holder);
			}
			loop++;
		}
		for (int i = 0; i < 50 - loop; i++)
		{
			std::cout << "#";
		}
		std::cout << "]" << std::endl;
		for (int i = 0; i < holder.LargeMap().Width(); i++)
		{
			for (int j = 0; j < holder.LargeMap().Height(); j++)
			{
				if (holder.LargeMap().GetCell(i, j) == "H")
				{
					resultNotAchieved = false;
				}
			}
		}
	}
	holder.ApplyLadders();
	return holder;
}
