/*
* Filename:		VehicleEvent.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "VehicleEvent.h"
#include "Station.h"
#include "Train.h"


VehicleEvent::VehicleEvent(std::shared_ptr<Station> station, std::shared_ptr<Train> train, Time time, EventType type)
	:
	station(station),
	train(train),
	time(time),
	type(type)
{
}


VehicleEvent::~VehicleEvent()
{
}

std::shared_ptr<Train> VehicleEvent::GetTrain()
{
	return train.lock();
}

std::shared_ptr<Station> VehicleEvent::GetStation()
{
	return station.lock();
}

Time VehicleEvent::GetTime()
{
	return time;
}

EventType VehicleEvent::GetType()
{
	return type;
}
