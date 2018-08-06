/*
* Filename:		Station.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef STATION_H
#define STATION_H

#include "Vehicle.h"
#include "Train.h"
#include "Time.h"
#include <map>
#include <list>
#include <memory>
#include <vector>
#include "Event.h"


class Station : public std::enable_shared_from_this<Station>
{
public:
	Station(std::string name, std::map<Type, std::vector<std::shared_ptr<Vehicle>>> vehiclePool, std::list<std::shared_ptr<Train>> trains);
	~Station();
	Station(const Station&) = delete;
	Station& operator=(const Station&) = delete;

	//must be used to initialize events
	void InitVehicleEvents();

	bool AssembleTrain(std::shared_ptr<Train> train);
	bool AssembleUncompletedTrain(std::shared_ptr<Train> train);

	//generally used to send a train to a railway
	std::shared_ptr<Train> SendTrain();
	void ReceiveTrain(std::shared_ptr<Train> train);
	void DisassembleTrain(std::shared_ptr<Train> train);
	std::string GetName();

	//used with search by id functions in railroadManager to loop through every train/vehicle on a station
	std::vector<int> GetTrainIDs();
	std::vector<int> GetVehicleIDs();

private:
	Type FindType(int type);

private:
	std::map<Type, std::vector<std::shared_ptr<Vehicle>>> vehiclePool;
	std::string name;
	std::list<std::shared_ptr<Train>> trains;
	std::list<std::shared_ptr<Train>> completedTrains;
	std::list<std::shared_ptr<Train>> uncompletedTrains;
	std::list<std::shared_ptr<Train>> finishedTrains;

};

#endif // !STATION_H