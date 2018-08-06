/*
* Filename:		Vehicle.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/
#include "Vehicle.h"


Vehicle::Vehicle(int id, Type type) : vehicleID(id), vehicleType(type)
{
}

Vehicle::~Vehicle()
{
}

int Vehicle::GetID() const
{
	return vehicleID;
}

Type Vehicle::GetType() const
{
	return vehicleType;
}

bool Vehicle::operator<(const Vehicle & other)
{
	return this->GetID() < other.GetID();
}

bool Vehicle::operator>(const Vehicle & other)
{
	return this->GetID() > other.GetID();
}

std::string Vehicle::GetTypeAsString()
{
	switch (vehicleType)
	{
	case Type::DIESEL_ENGINE: return "Diesel engine";
	case Type::ELECTRIC_ENGINE: return "Electric engine";
	case Type::NIGHT_COACH:		return "Night coach";
	case Type::DAY_COACH:		return "Day coach";
	case Type::OPEN_CARGO:		return "Open cargo";
	case Type::CLOSED_CARGO:	return "Closed cargo";
	default:					return "Error type";
	}
}

void Vehicle::PushEvent(VehicleEvent event)
{
	events.push_back(event);
}

VehicleEvent & Vehicle::GetLatestEvent()
{
	return events.back();
}


