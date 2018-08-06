/*
* Filename:		Log.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "Log.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "PassangerCar.h"
#include "Cargo.h"
#include "Locomotive.h"

static std::ofstream logFile("Trainsim.log");

// prints train information and writes to file
void Log::TrainInfo(std::shared_ptr<Train> train, Time currentTime, std::string message)
{

	std::stringstream stream;
	stream << currentTime << " Train [" << train->GetTrainID() << "] "
		<< "(" << train->GetStateAsString(train->GetState()) << ")" << std::endl;
	stream << "From " << train->GetDeparture() << " " << train->GetDepartureTime() << " "
		<< "to " << train->GetDestination() << " " << train->GetDestinationTime() << ". "
		<< "delay [" << train->GetDelay() << "]" << "speed: " << train->GetCurrentSpeed() << " km/h."<< std::endl;
	stream << message << std::endl;
	stream << "---------------------------------------------------------" << std::endl;
	std::cout << stream.str();
	if (logFile.is_open()) logFile << stream.str();

}

// prints simulation time and writes to file
void Log::SimInterval(Time currentTime, int interval)
{
	std::stringstream stream;
	Time toTime = currentTime;
	toTime += interval;
	stream << std::endl <<"*******   SIMULATION INTERVAL: " << currentTime << " to " << toTime << "   *******" << std::endl << std::endl;
	std::cout << stream.str();
	if (logFile.is_open()) logFile << stream.str();

}
// prints information about a train
void Log::PrintTrain(RailroadManager* manager, const std::shared_ptr<Train>& train, LogLevel logLevel)
{

	std::cout << "Train [" << train->GetTrainID() << "] " << "(" << train->GetStateAsString(train->GetState()) << ")"
		<< "From " << train->GetDeparture() << " " << train->GetDepartureTime() << " "
		<< "to " << train->GetDestination() << " " << train->GetDestinationTime() << ". " << " speed: " << train->GetCurrentSpeed() << "km/h" << std::endl;
	if (train->GetVehicleIDs().size() > 0 )
	{
		std::cout << "Vehicles: " << std::endl;
		for (auto &i : train->GetVehicleIDs())
		{
			PrintVehicle(manager->FindVehicleByID(i), logLevel);
		}
	}

	if (train->GetMissingVehicleIDs().size() > 0)
	{
		std::cout << "Missing vehicles:" << std::endl;
		for (auto j : train->GetMissingVehicleIDs())
		{

			switch (j)
			{
			case 0: std::cout << "\tDay coach" << std::endl;
				break;
			case 1: std::cout << "\tNtight coach" << std::endl;
				break;
			case 2: std::cout << "\tOpen cargo" << std::endl;
				break;
			case 3: std::cout << "\tClosed cargo" << std::endl;
				break;
			case 4: std::cout << "\tElectric engine" << std::endl;
				break;
			case 5: std::cout << "\tDiesel engine" << std::endl;
				break;
			default: std::cout << "Unknown" << std::endl;
				break;
			}
		}
	}

}

// prints information about a station
void Log::PrintStation(RailroadManager* manager, const std::shared_ptr<Station>& station, LogLevel logLevel) 
{
	std::cout << "**** STATION: " << station->GetName() << " ****"<<std::endl;
	std::cout << std::endl;
	std::vector<int> ids = station->GetVehicleIDs();
	std::cout << "Vehicles avalible at station: [" << ids.size() << "]" << std::endl;;
	for (auto& i : ids)
	{
		PrintVehicle(manager->FindVehicleByID(i), logLevel);
	}
	std::cout << std::endl;

	std::cout << "Trains currently at station: [" << station->GetTrainIDs().size() << "]" << std::endl;
	
	for (auto& i : station->GetTrainIDs())
	{
		PrintTrain(manager, manager->GetTrainByID(i), logLevel);
	}

}

// prints a vehicle
void Log::PrintVehicle(const std::shared_ptr<Vehicle>& vehicle, LogLevel logLevel) 
{
	std::cout << "\t";
	switch (logLevel)
	{
	case LogLevel::LOW:

		std::cout << vehicle->GetTypeAsString() << " [" << vehicle->GetID() << "] " << std::endl;

		break;

	case LogLevel::HIGH:

		std::cout << vehicle->GetTypeAsString() << " [" << vehicle->GetID() << "] ";

		Type vehicleType = vehicle->GetType(); // prints detaild information about a specific vehicle
		switch (vehicleType)
		{
		case Type::CLOSED_CARGO:
		{
			std::shared_ptr<ClosedCargo> closedCargo = std::dynamic_pointer_cast<ClosedCargo>(vehicle);
			std::cout << "Cargo volume: "<< closedCargo->GetLoadVolume() << " m^3. " << std::endl;
			break;
		}
		case Type::DAY_COACH:
		{
			std::shared_ptr<DayCar> dayCar = std::dynamic_pointer_cast<DayCar>(vehicle);
			std::cout << "Seats: " << dayCar->GetSeatSize() << ". Internet: ";
			if (dayCar->HasInternet()) std::cout << " Yes." << std::endl;
			else std::cout << " No." << std::endl;
			break;
		}
		case Type::DIESEL_ENGINE:
		{
			std::shared_ptr<DieselLocomotive> diesel = std::dynamic_pointer_cast<DieselLocomotive>(vehicle);
			std::cout << "Max speed: " << diesel->GetMaxSpeed() << "km/h. Fuel Consumption: " << diesel->GetFuelUsage() << std::endl;
			break;
		}
		case Type::ELECTRIC_ENGINE:
		{
			std::shared_ptr<ElectricLocomotive> electric = std::dynamic_pointer_cast<ElectricLocomotive>(vehicle);
			std::cout << "Max speed: " << electric->GetMaxSpeed() << "km/h. Power: " << electric->GetKilowatt() << "kw." << std::endl;
			break;
		}
		case Type::NIGHT_COACH:
		{
			std::shared_ptr<NightCar> nightCar = std::dynamic_pointer_cast<NightCar>(vehicle);
			std::cout << "Beds: " << nightCar->GetBedSize() << std::endl;
			break;
		}
		case Type::OPEN_CARGO: 
		{
			std::shared_ptr<OpenCargo> openCargo = std::dynamic_pointer_cast<OpenCargo>(vehicle);
			std::cout << "Cargo capacity: " << openCargo->GetLoadCapacity() << "ton. Cargo area: " << openCargo->GetLoadArea() << "m^2." << std::endl;
			break;
		}
		}

		break;
	}
}

// prints position of a vehicle
void Log::PrintVehiclePosition(std::shared_ptr<Vehicle>& vehicle)
{
	auto event = vehicle->GetLatestEvent();

	switch (event.GetType())
	{
	case EventType::ENTER_STATION:
	{
		std::cout << vehicle->GetTypeAsString() << " [" << vehicle->GetID() << "] " <<
			"is currently on the station " << event.GetStation()->GetName() << "." << std::endl;
		break;
	}
	case EventType::ATTACH_TRAIN:
		std::cout << vehicle->GetTypeAsString() << " [" << vehicle->GetID() << "] " <<
			"is attatched to train [" << event.GetTrain()->GetTrainID() << "] scheduled to leave from " <<
			event.GetTrain()->GetDeparture() << " station at " << event.GetTrain()->GetDepartureTime() << "." << std::endl;
		break;

	case EventType::LEFT_STATION:
		std::cout << vehicle->GetTypeAsString() << " [" << vehicle->GetID() << "] " <<
			"is currently attatched to train [" << event.GetTrain()->GetTrainID() << "] on the railway between " <<
			event.GetTrain()->GetDeparture() << " and " << event.GetTrain()->GetDestination() << "." << std::endl;

		break;
	case EventType::ARRIVED_STATION:
		std::cout << vehicle->GetTypeAsString() << " [" << vehicle->GetID() << "] " <<
			"is attatched to train [" << event.GetTrain()->GetTrainID() << "]  that arrived at " <<
			event.GetTrain()->GetDestination() << " station at " << event.GetTrain()->GetDestinationTime() << "." << std::endl;
		break;
	}

}

// prints the final results
void Log::PrintStatistics(RailroadManager * manager)
{
	std::cout << std::endl << "******* STATISTICS *******" << std::endl << std::endl;
	
	try
	{
		std::vector<std::shared_ptr<Train>> uncompletedTrains;

		std::cout << "Completed trains: " << std::endl;

		for (int i = 1; i <= manager->GetNumberOfTrains(); ++i)
		{
			auto train = manager->GetTrainByID(i);
			if (train->GetState() == State::INCOMPLETE)
			{
				uncompletedTrains.push_back(train);
			}
			else if(train->GetState() == State::FINISHED)
			{
				PrintTrain(manager, train, LogLevel::LOW); // prints the completed trains
			}
		}
		
		std::cout << "\n\nUncompleted trains:" << std::endl;

		for (auto& i : uncompletedTrains)
		{
			PrintTrain(manager, i, LogLevel::LOW); // prints the uncompleted trains
			
		}

	}
	catch (std::out_of_range& e)
	{
		std::cerr << e.what();
	}
	std::cout << std::endl;
	Time totalDelay;
	std::cout << "Delayed Trains: " << std::endl;
	for (int i = 1; i <= manager->GetNumberOfTrains(); i++)
	{
		auto train = manager->GetTrainByID(i);
		if (train->GetDelay().ToMinutes() > 0 && train->GetState() != State::INCOMPLETE)
		{
			totalDelay += train->GetDelay().ToMinutes();

			Time delayDep = train->GetDepartureTime();
			delayDep += train->GetDelay().ToMinutes();

			Time delayDes = train->GetDestinationTime();
			delayDes += train->GetDelay().ToMinutes();

			std::cout << " Train [" << train->GetTrainID() << "] " << "(" << train->GetStateAsString(train->GetState()) << ")"
				<< "From " << train->GetDeparture() << train->GetDepartureTime() << " (" << delayDep << ") "
				<< "to " << train->GetDestination() << train->GetDestinationTime() << " (" << delayDes << "). Delay: " << train->GetDelay() << " Speed: " << train->GetCurrentSpeed() << "km/h" <<std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "Total delay time: " << totalDelay << std::endl; // prints the total delay time

}

// prints the full history of a vehicle
void Log::PrintVehicleHistory(std::shared_ptr<Vehicle>& vehicle)
{

	std::cout << "Vehicle history [" << vehicle->GetID()<< "]" << std::endl;

	for (auto& e : vehicle->GetEvents())
	{
		std::cout << "At [" << e.GetTime() << "]: ";

		switch (e.GetType()) {
		case EventType::ARRIVED_STATION:
			std::cout << " vehicle arrived to staion: " << e.GetStation()->GetName() << std::endl;
			break;
		case EventType::ATTACH_TRAIN:
			std::cout << " vehicle got attatched to train " << e.GetTrain()->GetTrainID() << std::endl;
			break;
		case EventType::ENTER_STATION:
			std::cout << " vehicle got diassebmled at station " << e.GetStation()->GetName() << std::endl;
			break;
		case EventType::LEFT_STATION:
			std::cout << " vehicle left station " << e.GetStation()->GetName() << " attached to train [" << e.GetTrain()->GetTrainID() << "]" << std::endl;
			break;
		}

	}
}

std::string Log::ToString(LogLevel logLevel)
{

	switch (logLevel)
	{
	case LogLevel::HIGH: return "HIGH";
	case LogLevel::LOW: return "LOW";
	default: return "INVALID";
	}
}


