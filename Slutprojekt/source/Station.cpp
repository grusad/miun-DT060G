/*
* Filename:		Station.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "Station.h"
#include <assert.h>
#include "RailroadManager.h"

#include <iostream>
Station::Station(std::string name, std::map<Type, std::vector<std::shared_ptr<Vehicle>>> vehiclePool, std::list<std::shared_ptr<Train>> trains)
	:
	name(name),
	vehiclePool(std::move(vehiclePool)),
	trains(std::move(trains))
{
}


Station::~Station()
{
}

void Station::InitVehicleEvents()
{
	for (auto& pool : vehiclePool)
	{
		for (auto& v : pool.second)
		{
			v->PushEvent(VehicleEvent(shared_from_this(), nullptr, Time(), EventType::ENTER_STATION));
		}
	}
}
// assemble a train object
bool Station::AssembleTrain(std::shared_ptr<Train> train)
{
	int nextVehicle;

	for (auto& i : trains)
	{
		if (i->GetTrainID() == train->GetTrainID()) // if train id is equal to id
		{

			for (auto& v : vehiclePool) // sort the vehicle pool
			{
				std::sort(v.second.begin(), v.second.end(),
					[](const std::shared_ptr<Vehicle>& lhs, const std::shared_ptr<Vehicle>& rhs)
				{ return lhs->GetID() > rhs->GetID(); });
			}

			while (i->GetBlueprint(nextVehicle)) // if trains need a vehicle
			{
				Type type = FindType(nextVehicle);
				if (vehiclePool.at(type).empty()) // if vehicle does not exists
				{

					i->SetState(State::INCOMPLETE);
					uncompletedTrains.push_back((i));
					trains.remove(i);
					return false;
				}
				else
				{	// attatch vehicle to train
					i->AttachVehicle(std::move(vehiclePool[type].back()));
					vehiclePool[type].pop_back();
				}
			}

			i->SetState(State::ASSEMBLED);
			completedTrains.push_back(i);
			trains.remove(i);
			
			break;
		}
	}

	return true;

}

// assemble a incomplete train
bool Station::AssembleUncompletedTrain(std::shared_ptr<Train> train)
{

	int nextVehicle;

	for (auto& i : uncompletedTrains)
	{
		if (i->GetTrainID() == train->GetTrainID())
		{

			for (auto& v : vehiclePool)
			{
				std::sort(v.second.begin(), v.second.end(),
					[](const std::shared_ptr<Vehicle>& lhs, const std::shared_ptr<Vehicle>& rhs)
				{ return lhs->GetID() > rhs->GetID(); });
			}

			while (i->GetBlueprint(nextVehicle))
			{
				Type type = FindType(nextVehicle);
				if (vehiclePool.at(type).empty())
				{
					return false;
				}
				else
				{
					i->AttachVehicle(std::move(vehiclePool[type].back()));
					vehiclePool[type].pop_back();
				}
			}

			i->SetState(State::ASSEMBLED);
			completedTrains.push_back(i);
			uncompletedTrains.remove(i);
			break;
		}
	}

	return true;
}

// sends a train from station
std::shared_ptr<Train> Station::SendTrain()
{
	std::shared_ptr<Train> train = std::move(completedTrains.front());
	train->SetState(State::RUNNING);
	completedTrains.pop_front();

	return std::move(train);
}

// receives a train to station
void Station::ReceiveTrain(std::shared_ptr<Train> train)
{
	train->SetState(State::ARRIVED);
	finishedTrains.push_back(std::move(train));
}

// diassembles the vehicle from train
void Station::DisassembleTrain(std::shared_ptr<Train> train)
{
	while (true)
	{
		std::shared_ptr<Vehicle> vehicle = train->DetachVehicle();
		if (!vehicle)
		{
			break;
		}
		vehiclePool[vehicle->GetType()].push_back(std::move(vehicle));
	}

	train->SetState(State::FINISHED);
}

Type Station::FindType(int type)
{
	switch (type)
	{
	case 0: return Type::DAY_COACH;
	case 1: return Type::NIGHT_COACH;
	case 2: return Type::OPEN_CARGO;
	case 3: return Type::CLOSED_CARGO;
	case 4: return Type::ELECTRIC_ENGINE;
	case 5: return Type::DIESEL_ENGINE;
	default: return Type::UNKNOWN;
	}	
}


std::vector<int> Station::GetTrainIDs()
{
	std::vector<int> ids;

	for (auto& t : trains)
	{
		ids.push_back(t->GetTrainID());
	}

	for (auto& t : uncompletedTrains)
	{
		ids.push_back(t->GetTrainID());
	}

	for (auto& t : completedTrains)
	{
		ids.push_back(t->GetTrainID());
	}

	for (auto& t : finishedTrains)
	{
		ids.push_back(t->GetTrainID());
	}

	return ids;
}


std::vector<int> Station::GetVehicleIDs()
{
	std::vector<int> ids;
	for (auto& i : vehiclePool)
	{
		for (auto& j : i.second)
		{
			ids.push_back(j->GetID());
		}
	}
	return ids;
}

std::string Station::GetName()
{
	return name;
}

