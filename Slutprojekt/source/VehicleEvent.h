/*
* Filename:		VehicleEvent.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef VEHICLE_EVENT_H
#define VEHICLE_EVENT_H


#include <memory>
#include "Time.h"

class Station;
class Train;

enum class EventType{ENTER_STATION, ATTACH_TRAIN, LEFT_STATION, ARRIVED_STATION};

// a vehicle event
class VehicleEvent
{
public:
	VehicleEvent(std::shared_ptr<Station> station, std::shared_ptr<Train> train, Time time, EventType type);
	~VehicleEvent();

	std::shared_ptr<Train> GetTrain();
	std::shared_ptr<Station> GetStation();
	Time GetTime();
	EventType GetType();

private:
	std::weak_ptr<Train> train;
	std::weak_ptr<Station> station;
	Time time;
	EventType type;
};

#endif // !VEHICLE_EVENT_H





