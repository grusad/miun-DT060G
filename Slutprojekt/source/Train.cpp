/*
* Filename:		Train.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "Train.h"
#include "RailroadManager.h"

Train::Train(int id, std::string departureName, std::string destinationName, Time departureTime, Time destinationTime,
	int maxSpeed, std::queue<int> bluePrint)
	:
	trainID(id),
	departure(departureName),
	destination(destinationName),
	departureTime(departureTime),
	destinationTime(destinationTime),
	vehicleBlueprint(std::move(bluePrint)),
	delay(00, 00, 00),
	maxSpeed(maxSpeed),
	currentSpeed(0)
{
	state = State::NOT_ASSEMBLED;
}

void Train::SetState(State state)
{
	this->state = state;
}

State Train::GetState() const
{
	return state;
}

std::string Train::GetStateAsString(State state) const
{
	switch (state)
	{
	case State::NOT_ASSEMBLED:	return "NOT ASSEMBLED";
	case State::INCOMPLETE:		return "INCOMPLETE";
	case State::ASSEMBLED:		return "ASSEMBLED";
	case State::READY:			return "READY";
	case State::RUNNING:		return "RUNNING";
	case State::ARRIVED:		return "ARRIVED";
	case State::FINISHED:		return "FINISHED";
	default:					return "ERROR_STATE";
	}
}

int Train::GetTrainID() const
{
	return trainID;
}

int Train::GetCurrentSpeed() const
{
	return currentSpeed;
}

void Train::SetCurrentSpeed(const int speed)
{
	this->currentSpeed = speed;
}

Time Train::GetDepartureTime() const
{
	return departureTime;
}

Time Train::GetDestinationTime() const
{
	return destinationTime;
}

int Train::GetMaxSpeed() const
{
	return maxSpeed;
}



Time Train::GetDelay() const
{
	return delay;
}

void Train::SetDelay(const Time time)
{
	this->delay = time;
}

std::string Train::GetDeparture() const
{
	return departure;
}

std::string Train::GetDestination() const
{
	return destination;
}

// attach a vehicle to train
void Train::AttachVehicle(std::shared_ptr<Vehicle> vehicle)
{
	vehicles.emplace_back(std::move(vehicle));
	vehicleBlueprint.pop();
}

// detaches a vehicle from train
std::shared_ptr<Vehicle> Train::DetachVehicle()
{
	if (vehicles.size() > 0)
	{
		std::shared_ptr<Vehicle> train = std::move(vehicles.front());
		vehicles.erase(vehicles.begin());
		return train;
	}

	return nullptr;
}

// returns the next vehcile id from trains blueprint
bool Train::GetBlueprint(int& next)
{
	if (!vehicleBlueprint.empty())
	{
		next = vehicleBlueprint.front();
		return true;
	}
	return false;
}

std::vector<int> Train::GetVehicleIDs()
{
	std::vector<int> ids;

	for (auto& i : vehicles)
	{
		ids.push_back(i->GetID());
	}

	return ids;
}

std::vector<int> Train::GetMissingVehicleIDs()
{
	std::vector<int> ids;
	std::queue<int> bp = vehicleBlueprint;
	while (!bp.empty())
	{
		ids.push_back(bp.front());
		bp.pop();
	}
	return ids;
}

void Train::UpdateVehicleEvents(VehicleEvent vEvent)
{
	for (auto& vehicle : vehicles)
	{
		vehicle->PushEvent(vEvent);
	}
}
