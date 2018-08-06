/*
* Filename:		Train.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <string>
#include "Vehicle.h"
#include "Time.h"
#include <queue>
#include <memory>

class RailroadManager;

enum class State {
	NOT_ASSEMBLED, INCOMPLETE, ASSEMBLED, READY, RUNNING, ARRIVED, FINISHED
};

class Train 
{
public:

	Train(int id, std::string departureName, std::string destinationName, Time departureTime, Time destinationTime, 
		int maxSpeed, std::queue<int> bluePrint);

	Train(const Train&) = delete;
	Train& operator= (const Train&) = delete;

	void SetState(State state);
	State GetState() const;
	std::string GetStateAsString(State state) const;
	int GetTrainID() const;
	int GetCurrentSpeed() const;
	void SetCurrentSpeed(const int speed);
	Time GetDepartureTime() const;
	Time GetDestinationTime() const;
	int GetMaxSpeed() const;

	Time GetDelay() const;
	void SetDelay(const Time time);

	//returns departure stations name
	std::string GetDeparture() const;
	//returns destination stations name
	std::string GetDestination() const;

	void AttachVehicle(std::shared_ptr<Vehicle> vehicle);
	std::shared_ptr<Vehicle> DetachVehicle();

	//used to get the next vehicle type as int when assembling trains
	bool GetBlueprint(int& next);
	std::vector<int> GetVehicleIDs();
	std::vector<int> GetMissingVehicleIDs();

	//pushes new vehicle events to all vehicles attached to the train
	void UpdateVehicleEvents(VehicleEvent vEvent);

private:
	std::vector<std::shared_ptr<Vehicle>> vehicles;
	std::queue<int> vehicleBlueprint;
	State state;
	int trainID;
	int maxSpeed;
	int currentSpeed;

	Time departureTime;
	Time destinationTime;
	std::string departure;
	std::string destination;
	Time delay;
};

#endif // !TRAIN_H
