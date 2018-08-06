/*
* Filename:		RailroadManager.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef RAILROAD_MANAGER_H
#define RAILROAD_MANAGER_H


#include "Station.h"
#include "RailWay.h"
#include <vector>
#include <fstream>
#include <memory>
#include "Event.h"


// the main manager of the application
class RailroadManager
{
public:
	RailroadManager() = default;
	~RailroadManager();
	RailroadManager(const RailroadManager&) = delete;
	RailroadManager& operator=(const RailroadManager&) = delete;
	
	//reads data and sets the manager to a valid state, may throw
	void InitRailroad(const Time startTime, const Time stopTime);
	//resets the object to an uninitialized state
	void Clear();


	//used to push new events to the event queue
	void PushEvent(Event* event);
	std::shared_ptr<Railway> GetRailway(std::string start, std::string end);
	std::shared_ptr<Station> GetStation(std::string name);

	//updates the simulation time and executes events in the time window
	void TimeUpdate(Time& time);
	bool HasEventsToProcess();
	void UpdateNextEvent(Time& time);
	std::shared_ptr<Train> GetTrainByID(int id);
	std::shared_ptr<Train> GetTrainByVehicle(int id);

	//used together with GetStationByName to loop through every station
	std::vector<std::string> GetStationNames();
	std::shared_ptr<Station> GetStationByName(std::string name);
	
	std::shared_ptr<Vehicle> FindVehicleByID(int id);
	bool IsInitalized() const;

	//returns size of trainTracker
	size_t GetNumberOfTrains();
	//returns size of vehicleTracker
	size_t GetNumberOfVehicles();

private:
	std::vector<std::shared_ptr<Station>> stations;
	std::vector <std::shared_ptr<Railway>> railways;
	std::map<int, std::shared_ptr<Vehicle>> vehicleTracker;
	std::map<int, std::shared_ptr<Train>> trainTracker;
	const std::string TRAINZ = "Trains.txt";
	const std::string TRAIN_STATIONS = "TrainStations.txt";
	const std::string TRAIN_MAP = "TrainMap.txt";
	bool initialized = false;

	Time stopTime;
	
	std::priority_queue<Event*, std::vector<Event*>, EventComparison> events;


};

#endif 

