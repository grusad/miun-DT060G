/*
* Filename:		Railway.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef RAILWAY_H
#define RAILWAY_H


#include "Train.h"
#include <vector>
#include <queue>
#include <memory>

class Railway
{
public:
	Railway(std::string pointA, std::string pointB, int distance)
		: pointA(pointA), pointB(pointB), distance(distance) {};

	//used when trains are moved from a station to a railway
	void AddTrain(std::shared_ptr<Train> train);
	std::string GetPointA() const;
	std::string GetPointB() const;
	int GetDistance() const;
	void RemoveTrain(int trainID);

private:
	std::vector<std::shared_ptr<Train>> trains;
	std::string pointA;
	std::string pointB;
	int distance;
};


#endif // !RAILWAY_H