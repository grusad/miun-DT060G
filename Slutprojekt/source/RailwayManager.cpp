#include "RailwayManager.h"
#include <sstream>
#include <iostream>
void RailwayManager::AssembleRailways() 
{
	std::ifstream trainMap(TRAIN_MAP);
	
	if (trainMap.is_open())
	{

		std::string str;
		while (std::getline(trainMap, str)) 
		{
			std::stringstream stream(str);
			std::string pointA, pointB;
			int distance;

			stream >> pointA >> pointB >> distance;
			
			railways.emplace_back(std::make_unique<Railway>(pointA, pointB, distance));
			
		}
	}

	
}

void RailwayManager::UpdateRailways()
{

	for (auto& railway : railways)
	{
		// Handle all trains on the railways.
	}
	
}
