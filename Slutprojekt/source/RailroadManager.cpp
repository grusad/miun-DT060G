/*
* Filename:		RailroadManager.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "RailroadManager.h"
#include "Vehicle.h"
#include "PassangerCar.h"
#include "Cargo.h"
#include "Locomotive.h"
#include <sstream>
#include <memory>
#include <functional>
#include "Utils.h"

RailroadManager::~RailroadManager()
{
}

void RailroadManager::InitRailroad(const Time startTime, const Time stopTime)
{
	std::ifstream trainz(TRAINZ);
	std::ifstream trainStations(TRAIN_STATIONS);
	std::ifstream trainMap(TRAIN_MAP);

	std::string station;
	std::string train;
	std::getline(trainz, train); //prime read of trainz

	if (!(trainz.is_open() && trainStations.is_open() && trainMap.is_open()))
		throw std::runtime_error("Error opening files");

	while (std::getline(trainStations, station))
	{

		std::list<std::shared_ptr<Train>> trains;
		std::stringstream stream(station);
		std::string name;
		stream >> name;

		//using map with type as key for easy access to vehicles in stations
		std::map<Type, std::vector<std::shared_ptr<Vehicle>>> vehicles;
		vehicles.insert(std::make_pair(Type::OPEN_CARGO, std::vector<std::shared_ptr<Vehicle>>()));
		vehicles.insert(std::make_pair(Type::OPEN_CARGO, std::vector<std::shared_ptr<Vehicle>>()));
		vehicles.insert(std::make_pair(Type::DAY_COACH, std::vector<std::shared_ptr<Vehicle>>()));
		vehicles.insert(std::make_pair(Type::NIGHT_COACH, std::vector<std::shared_ptr<Vehicle>>()));
		vehicles.insert(std::make_pair(Type::DIESEL_ENGINE, std::vector<std::shared_ptr<Vehicle>>()));
		vehicles.insert(std::make_pair(Type::ELECTRIC_ENGINE, std::vector<std::shared_ptr<Vehicle>>()));

		while (true)
		{
			auto end = station.find_last_of(')');
			auto first = station.find('(');
			auto last = station.find(')');

			std::string data = station.substr(first + 1, last - 1 - first);
			station = station.substr(last + 1, end - last);

			stream.clear();
			stream.str(data);

			int id;
			int type;

			stream >> id >> type;


			//Creating and storing vehicle objects according to file data
			switch (type)
			{
			case 0:
			{
				int seats;
				int internet;

				stream >> seats >> internet;

				vehicles[Type::DAY_COACH].emplace_back(std::make_shared<DayCar>(seats, internet, id));
				vehicleTracker[id] = vehicles[Type::DAY_COACH].back();
				break;
			}
			case 1:
			{
				int beds;

				stream >> beds;

				vehicles[Type::NIGHT_COACH].emplace_back(std::make_shared<NightCar>(beds, id));
				vehicleTracker[id] = vehicles[Type::NIGHT_COACH].back();
				break;
			}
			case 2:
			{
				int capacity;
				int area;

				stream >> capacity >> area;

				vehicles[Type::OPEN_CARGO].emplace_back(std::make_shared<OpenCargo>(capacity, area, id));
				vehicleTracker[id] = vehicles[Type::OPEN_CARGO].back();
				break;
			}
			case 3:
			{
				int volume;

				stream >> volume;

				vehicles[Type::CLOSED_CARGO].emplace_back(std::make_shared<ClosedCargo>(volume, id));
				vehicleTracker[id] = vehicles[Type::CLOSED_CARGO].back();
				break;
			}
			case 4:
			{
				int maxSpeed;
				int kilowatts;

				stream >> maxSpeed >> kilowatts;

				vehicles[Type::ELECTRIC_ENGINE].emplace_back(std::make_shared<ElectricLocomotive>(id, maxSpeed, kilowatts));
				vehicleTracker[id] = vehicles[Type::ELECTRIC_ENGINE].back();
				break;
			}
			case 5:
			{
				int maxSpeed;
				int consumption;

				stream >> maxSpeed >> consumption;

				vehicles[Type::DIESEL_ENGINE].emplace_back(std::make_shared<DieselLocomotive>(id, maxSpeed, consumption));
				vehicleTracker[id] = vehicles[Type::DIESEL_ENGINE].back();
				break;
			}

			default:
				break;
			}

			if (last == end)
				break;

		}

		while (true)
		{

			stream.clear();
			stream.str(train);

			int trainID;
			std::string departureName;
			std::string destinationName;
			Time departureTime;
			Time destinationTime;
			int maxSpeed;
			std::queue<int> bluePrint;

			stream >> trainID >> departureName >> destinationName >> departureTime >> destinationTime >> maxSpeed;

			//creating the vehicle blueprint
			int bp;
			while (stream >> bp)
			{
				bluePrint.push(bp);
			}

			trains.push_back(std::make_shared<Train>(trainID, departureName, destinationName, departureTime, destinationTime, maxSpeed, bluePrint));
			trainTracker[trainID] = trains.back();

			if (std::getline(trainz, train))
			{
				std::string tempName;

				stream.clear();
				stream.str(train);

				stream >> trainID >> tempName;

				if (name != tempName) //break if train belongs to another station
				{
					break;
				}

			}
			else //break if no new trains
			{
				break;
			}

		}

		stations.emplace_back(std::make_shared<Station>(name, std::move(vehicles), std::move(trains)));

	}

	for (auto& s : stations)
	{
		s->InitVehicleEvents();
	}

	trainz.close();
	trainStations.close();


	std::string str;
	while (std::getline(trainMap, str))
	{
		std::stringstream stream(str);
		std::string pointA, pointB;
		int distance;

		stream >> pointA >> pointB >> distance;

		railways.emplace_back(std::make_shared<Railway>(pointA, pointB, distance));
	}

	trainMap.close();

	for (auto& station : stations)
	{
		for (auto& id : station->GetTrainIDs())
		{
			auto train = GetTrainByID(id);

			Time eventTime = train->GetDepartureTime() -= 30;
			if (eventTime < startTime || eventTime >= stopTime)
				continue; // Ignore events outside the time window

			PushEvent(new AssembleEvent(this, station, train, eventTime));
		}
	}

	initialized = true;
	this->stopTime = stopTime;
}


void RailroadManager::PushEvent(Event * event)
{
	events.push(event);
}

std::shared_ptr<Railway> RailroadManager::GetRailway(std::string start, std::string end)
{
	auto it = std::find_if(railways.begin(), railways.end(), [start, end](const std::shared_ptr<Railway>& r) 
	{
		return ((r->GetPointA() == start && r->GetPointB() == end) || (r->GetPointB() == start && r->GetPointA() == end));
	});

	if(it != railways.end())
		return *it;
	
	return nullptr;
}

std::shared_ptr<Station> RailroadManager::GetStation(std::string name)
{
	auto it = std::find_if(stations.begin(), stations.end(), [name](const std::shared_ptr<Station>& s)
	{
		return Utils::ToLower(s->GetName()) == Utils::ToLower(name);
	});

	if (it != stations.end())
		return *it;

	return nullptr;
}

// updated the simulation depending on time
void RailroadManager::TimeUpdate(Time & time)
{

	while (!events.empty() && time >= events.top()->GetTime())
	{
		if (events.top()->GetTime() >= stopTime && (events.top()->GetTrainState() == State::INCOMPLETE
			|| events.top()->GetTrainState() == State::READY || events.top()->GetTrainState() == State::ASSEMBLED))
		{
			Event* e = events.top();
			events.pop();
			delete e;
			continue;
		}

		Event* e = events.top();
		events.pop();
		e->processEvent();
		delete e;
	}
}


bool RailroadManager::HasEventsToProcess()
{
	return !events.empty();
}

void RailroadManager::UpdateNextEvent(Time& time)
{
	if (!events.empty())
	{

		time = events.top()->GetTime();
		events.top()->processEvent();
		delete events.top();
		events.pop();

	}
}

// clears the manager
void RailroadManager::Clear()
{
	initialized = false;
	stations.clear();
	railways.clear();
	vehicleTracker.clear();
	trainTracker.clear();
	while (!events.empty())
	{
		delete events.top();
		events.pop();
	}
}

std::shared_ptr<Train> RailroadManager::GetTrainByID(int id)
{

	return trainTracker.at(id);

}

std::shared_ptr<Train> RailroadManager::GetTrainByVehicle(int vehicleID)
{
	return vehicleTracker.at(vehicleID)->GetLatestEvent().GetTrain();
}

std::vector<std::string> RailroadManager::GetStationNames()
{
	std::vector<std::string> names;

	for (auto& station : stations)
	{
		names.push_back(station->GetName());
	}
	return names;
}

std::shared_ptr<Station> RailroadManager::GetStationByName(std::string name)
{
	auto it = std::find_if(stations.begin(), stations.end(), 
		[name](const std::shared_ptr<Station> station) 
	{
		return Utils::ToLower(station->GetName()) == Utils::ToLower(name);
	});
	
	if (it != stations.end()) return *it;
	return nullptr;
}



std::shared_ptr<Vehicle> RailroadManager::FindVehicleByID(int id)
{

	return vehicleTracker.at(id);
	
}

bool RailroadManager::IsInitalized() const
{
	return initialized;
}

size_t RailroadManager::GetNumberOfTrains()
{
	return trainTracker.size();
}

size_t RailroadManager::GetNumberOfVehicles()
{
	return vehicleTracker.size();
}
