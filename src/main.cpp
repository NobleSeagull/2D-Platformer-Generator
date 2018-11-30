#define SDL_MAIN_HANDLED

#include "stdafx.h"
#include "JSONReader.h"
#include "GeneticAlgMapGenerator.h"
#include <iostream>
#include <fstream>

#include "Box.h"

#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main()
{
	srand(time(NULL));

	std::ofstream file;
	std::string holderString;

	int x, y;
	std::string textureName;
	std::string fileName;

	std::cout << "Input Width : ";
	std::cin >> x;
	std::cout << "" << std::endl;

	std::cout << "Input Height : ";
	std::cin >> y;
	std::cout << "" << std::endl;

	std::cout << "Input File Name : ";
	std::cin >> fileName;
	std::cout << "" << std::endl;

	std::cout << "Input Texture TSX name : ";
	std::cin >> textureName;
	std::cout << "" << std::endl;

	ManagedGridMap map = GeneticAlgMapGenerator().Generate(x, y, 8, 3);

	SDL_Window* gameWindow = SDL_CreateWindow("World Generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	//Testing Purposes
	std::vector<Box*> map_draw;
	for (int i = 0; i < map.Width() * 16; i++)
	{
		for (int j = 0; j < map.Height() * 16; j++)
		{
			if (map.LargeMap().GetCell(i, j) == "W" || map.LargeMap().GetCell(i, j) == "X")
			{
				map_draw.push_back(new Box(8, 8, SDL_Point{ i * 8, j * 8 }, SDL_Color{ 255,255,255,255 }));
			}
			else if (map.LargeMap().GetCell(i, j) == "H")
			{
				map_draw.push_back(new Box(8, 8, SDL_Point{ i * 8, j * 8 }, SDL_Color{ 255,0,0,255 }));
			}
			else if (map.LargeMap().GetCell(i, j) == "C")
			{
				map_draw.push_back(new Box(8, 8, SDL_Point{ i * 8, j * 8 }, SDL_Color{ 255,255,0,255 }));
			}
			else if (map.LargeMap().GetCell(i, j) == "L")
			{
				map_draw.push_back(new Box(8, 8, SDL_Point{ i * 8, j * 8 }, SDL_Color{ 200,200,100,255 }));
			}
			else if (map.LargeMap().GetCell(i, j) == "E")
			{
				map_draw.push_back(new Box(8, 8, SDL_Point{ i * 8, j * 8 }, SDL_Color{ 250,250,0,255 }));
			}
		}
	}
	//

	std::cout << "Press 'Space' to output map as JSON file" << std::endl;

	//
	while (true)
	{

		while (SDL_PollEvent(e) != 0)
		{
			switch (e->type)
			{
			case SDL_KEYDOWN:
			{
				switch (e->key.keysym.sym)
				{
				case SDLK_SPACE:
					file.open(fileName + ".json");
					file << "{ \"height\":" << y*16 << ",\n";
					file << "\"infinite\":false,\n";
					file << "\"layers\":[\n";
					//
					file << "\t{\n";
					file << "\t\"data\":[";
					holderString.clear();
					for (int i = 0; i < map.Width() * 16; i++)
					{
						for (int j = 0; j < map.Height() * 16; j++)
						{
							if (map.LargeMap().GetCell(i, j) == "W" || map.LargeMap().GetCell(i, j) == "X")
							{
								holderString += "2, ";
							}
							else if (map.LargeMap().GetCell(i, j) == "H")
							{
								holderString += "1, ";
							}
							else if (map.LargeMap().GetCell(i, j) == "C")
							{
								holderString += "1, ";
							}
							else if (map.LargeMap().GetCell(i, j) == "L")
							{
								holderString += "1, ";
							}
							else if (map.LargeMap().GetCell(i, j) == "E")
							{
								holderString += "1, ";
							}
							else
							{
								holderString += "1, ";
							}
						}
					}
					holderString.pop_back();
					holderString.pop_back();
					file << holderString << "],\n";
					file << "\t\"height\":" << x * 16 << ",";
					file << "\t\"name\":\"LayerOne\",\n";
					file << "\t\"opacity\":1,\n";
					file << "\t\"type\":\"tilelayer\",\n";
					file << "\t\"visible\":true,\n";
					file << "\t\"width\":" << y * 16 << ",\n";
					file << "\t\"x\":0,\n";
					file << "\t\"y\":0\n";
					file << "\t},\n";
					//
					file << "\t{\n";
					file << "\t\"data\":[";
					holderString.clear();
					for (int i = 0; i < map.Width() * 16; i++)
					{
						for (int j = 0; j < map.Height() * 16; j++)
						{
							if (map.LargeMap().GetCell(i, j) == "W" || map.LargeMap().GetCell(i, j) == "X")
							{
								holderString += "0, ";
							}
							else if (map.LargeMap().GetCell(i, j) == "H")
							{
								holderString += "6, ";
							}
							else if (map.LargeMap().GetCell(i, j) == "C")
							{
								holderString += "5, ";
							}
							else if (map.LargeMap().GetCell(i, j) == "L")
							{
								holderString += "4, ";
							}
							else if (map.LargeMap().GetCell(i, j) == "E")
							{
								holderString += "3, ";
							}
							else
							{
								holderString += "0, ";
							}
						}
					}
					holderString.pop_back();
					holderString.pop_back();
					file << holderString << "],\n";
					file << "\t\"height\":" << x * 16 << ",";
					file << "\t\"name\":\"LayerOne\",\n";
					file << "\t\"opacity\":1,\n";
					file << "\t\"type\":\"tilelayer\",\n";
					file << "\t\"visible\":true,\n";
					file << "\t\"width\":" << y * 16 << ",\n";
					file << "\t\"x\":0,\n";
					file << "\t\"y\":0\n";
					file << "\t}],\n";

					file << "\"nextobjectid\":1,\n";
					file << "\"orientation\" : \"orthogonal\",\n";
					file << "\"renderorder\" : \"right-down\",\n";
					file << "\"tiledversion\" : \"1.1.4\",\n";
					file << "\"tileheight\" : 32,\n";
					file << "\"tilesets\" : [\n";
					file << "\t{\n";
					file << "\t\"firstgid\":1,\n";
					file << "\t\"source\" : \"" << textureName << ".tsx\"\n";
					file << "\t}],\n";

					file << "\"tilewidth\":" << 32 << ",\n";
					file << "\"type\":\"map\",\n";
					file << "\"version\":1,\n";
					file << "\"width\":" << y * 16 << "\n";
					file << "}";

					file.close();
					break;
				default:
					break;
				}
				break;
			}
			}
		}

		SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gameRenderer);
		//Draw Code Here

		for (int i = 0; i < map_draw.size(); i++)
		{
			map_draw.at(i)->Draw(*gameRenderer);
		}

		//
		SDL_RenderPresent(gameRenderer);
	}

    return 0;
}

