/*
* Filename:		Vehicle.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <list>
#include "VehicleEvent.h"

enum class Type{UNKNOWN, DIESEL_ENGINE, ELECTRIC_ENGINE, NIGHT_COACH, DAY_COACH, OPEN_CARGO, CLOSED_CARGO };

// the base class of all vehicles
class Vehicle 
{
public:
	Vehicle(int id, Type type);
	virtual ~Vehicle() = 0;

	int GetID() const;
	Type GetType() const;
	bool operator< (const Vehicle& other);
	bool operator> (const Vehicle& other);
	std::string GetTypeAsString();
	void PushEvent(VehicleEvent event);
	VehicleEvent& GetLatestEvent();
	std::list<VehicleEvent> GetEvents()  const { return events; }; // returns all events from vehicle


private:
	int vehicleID;
	Type vehicleType;
	std::list<VehicleEvent> events;
};

#endif // !VEHICLE_H