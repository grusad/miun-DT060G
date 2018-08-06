/*
* Filename:		Railway.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "RailWay.h"
#include <algorithm>

void Railway::AddTrain(std::shared_ptr<Train> train) 
{
	trains.push_back(std::move(train)); 
}

std::string Railway::GetPointA() const
{
	return pointA;
}

std::string Railway::GetPointB() const
{
	return pointB;
}

int Railway::GetDistance() const
{
	return distance;
}

// removes a train from railway
void Railway::RemoveTrain(int trainID)
{
	auto it = std::find_if(trains.begin(), trains.end(),
		[trainID](const std::shared_ptr<Train>& t1) {return t1->GetTrainID() == trainID; });
	if (it != trains.end())
	{
		trains.erase(it);
	}
}