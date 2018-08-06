/*
* Filename:		Application.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "Application.h"
#include "RailroadManager.h"
#include "Log.h"
#include "Input.h"
#include <sstream>
#include <iostream>
#include <vector>


// constructor initalizes all the menues and their items
Application::Application()
	: 
	startTime(00, 00, 00), 
	stopTime(00, 23, 59), 
	intervalMins(10),
	main("Main Menu"),
	simMenu("Simulation Menu"),
	trainMenu("Train Menu"),
	stationMenu("Station Menu"),
	vehicleMenu("Vehicle Menu"),
	logMenu("Log Menu")
{
	main.AddItem(MenuItem("Set start time", [&]() { SetStartTime(); }), 1);
	main.AddItem(MenuItem("Set stop time", [&]() { SetStopTime(); }), 2);
	main.AddItem(MenuItem("Run simulation", [&]() { RunApplication(); }), 3);

	simMenu.AddItem(MenuItem("Change interval", [&]() { ChangeInterval(); }), 1);
	simMenu.AddItem(MenuItem("Run next interval", [&]() { RunNextInterval(); }), 2);
	simMenu.AddItem(MenuItem("Next Event", [&]() { RunNextEvent(); }), 3);
	simMenu.AddItem(MenuItem("Complete simulation", [&]() { CompleteSimulation(); }), 4);
	simMenu.AddItem(MenuItem("Change log level", [&]() { ChangeLogLevel(); }), 5);
	simMenu.AddItem(MenuItem("Train menu", [&]() { RunTrainMenu(); }), 6);
	simMenu.AddItem(MenuItem("Station menu", [&]() { RunStationMenu(); }), 7);
	simMenu.AddItem(MenuItem("Vehicle menu", [&]() { RunVehicleMenu(); }), 8);

	trainMenu.AddItem(MenuItem("Search train by number", [&]() { PrintTrainByTrainID(); }), 1);
	trainMenu.AddItem(MenuItem("Search train by vehicle id", [&]() { PrintTrainByVehicleID(); }), 2);
	trainMenu.AddItem(MenuItem("Show all trains", [&]() { PrintAllTrains(); }), 3);

	stationMenu.AddItem(MenuItem("Show station names", [&]() { PrintStationNames(); }), 1);
	stationMenu.AddItem(MenuItem("Show station by name", [&]() { PrintStationByName(); }), 2);
	stationMenu.AddItem(MenuItem("Show all station", [&]() { PrintAllStations(); }), 3);

	vehicleMenu.AddItem(MenuItem("Show vehicle by id", [&]() { PrintVehicle(); }), 1);
	vehicleMenu.AddItem(MenuItem("Show all vehicle", [&]() {PrintAllVehicles(); }), 2);
	vehicleMenu.AddItem(MenuItem("Show vehicleposition by id", [&]() { PrintVehiclePosition(); }), 3);
	vehicleMenu.AddItem(MenuItem("Show vehicle history", [&]() { PrintVehicleHistory(); }), 3);

	logMenu.AddItem(MenuItem("Low", [&]() {logLevel = LogLevel::LOW; std::cout << "Log level set to LOW" << std::endl; Input::Prompt(); }), 1);
	logMenu.AddItem(MenuItem("High", [&]() {logLevel = LogLevel::HIGH; std::cout << "Log level set to HIGH" << std::endl; Input::Prompt(); }), 2);

}

// runs the start menu
void Application::ShowMenu()
{
	main.ShowMain();
}

// runs the main program
void Application::RunApplication()
{
	if (manager.IsInitalized())
	{
		simMenu.SetItemState(1, true);
		simMenu.SetItemState(2, true);
		simMenu.SetItemState(3, true);
		simMenu.SetItemState(4, true);
		manager.Clear();
	}

	try
	{
		manager.InitRailroad(startTime, stopTime);
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		Input::Prompt();
		return;
	}
	
	simulationTime = startTime;

	simMenu.ShowSub();

}


// lets the user set the start time of simulation
void Application::SetStartTime()
{
	Menu::ClearScreen();
	std::cout << " Set start time - Current: " + startTime.ToString() << std::endl;

	int hour = Input::GetInteger("Enter hour: ", 0, 23);
	int minute = Input::GetInteger("Enter minute: ", 0, 59);;

	startTime.SetHour(hour);
	startTime.SetMinute(minute);

	Input::Prompt();
}

// lets the user set the stop time of simulation
void Application::SetStopTime()
{

	Menu::ClearScreen();
	std::cout << " Set stop time - Current: " + stopTime.ToString() << std::endl;

	Time newTime;
	int hour;
	int minute;

	while (true)
	{
		hour = Input::GetInteger("Enter hour: ", 0, 23);
		minute = Input::GetInteger("Enter minute: ", 0, 59);
		newTime.SetHour(hour);
		newTime.SetMinute(minute);

		if (startTime.GetHour() == 23 && startTime.GetMinute() == 59)
		{
			stopTime = startTime;
			break;
		}
		else if (newTime < startTime) // if stop time < start time
		{
			std::cout << "Stop time must be later than the start time. Start time: [" << startTime << "]." << std::endl;
		}
		else // valid inputs 
		{
			stopTime.SetHour(hour);
			stopTime.SetMinute(minute);
			break;
		}

	}

	Input::Prompt();
}

// lets the user set the time interval of simulation
void Application::ChangeInterval() 
{
	Menu::ClearScreen();
	intervalMins = Input::GetInteger("Enter the length of interval in minutes - Current: " + std::to_string(intervalMins),1 , std::numeric_limits<int>::max());
}

// completes the simulation
void Application::CompleteSimulation()
{

	while (manager.HasEventsToProcess())
	{
		Log::SimInterval(simulationTime, intervalMins);
		simulationTime += intervalMins;
		manager.TimeUpdate(simulationTime);
	}
	CloseMenuItems();

	PrintStatistics();
}

// runs the next interval of simulation
void Application::RunNextInterval()
{
	if (manager.HasEventsToProcess())
	{
		Log::SimInterval(simulationTime, intervalMins);
		simulationTime += intervalMins;
		manager.TimeUpdate(simulationTime);
		Input::Prompt();
	}
	else
	{
		CloseMenuItems();
		PrintStatistics();
	}
	
}

// runs the next event of simulation
void Application::RunNextEvent()
{
	if (manager.HasEventsToProcess() && (simulationTime < stopTime))
	{
		manager.UpdateNextEvent(simulationTime);
		Input::Prompt();
	}
	else
	{
		manager.TimeUpdate(simulationTime);
		CloseMenuItems();
		PrintStatistics();
	}
}

void Application::RunTrainMenu()
{
	trainMenu.ShowSub();
}

void Application::RunStationMenu()
{
	stationMenu.ShowSub();
}

void Application::RunVehicleMenu()
{
	vehicleMenu.ShowSub();
}

// prints all station names
void Application::PrintStationNames()
{
	for (auto& name : manager.GetStationNames())
	{
		std::cout << name << std::endl;
	}
	Input::Prompt();
}


// print a specific station by its name
void Application::PrintStationByName()
{
	auto station = manager.GetStationByName(Input::GetString("Enter station name"));
	if (station)
	{
		Log::PrintStation(&manager, station, logLevel);
	}
	else
	{
		std::cout << "Could not find a station with the given name." << std::endl;
	}

	Input::Prompt();
}

// prints all stations and their information
void Application::PrintAllStations()
{
	auto allStations = manager.GetStationNames();
	for (auto& i : allStations)
	{
		Log::PrintStation(&manager, manager.GetStation(i), logLevel);
	}

	Input::Prompt();
}

// prints a train by a specific id
void Application::PrintTrainByTrainID()
{
	try
	{
		std::shared_ptr<Train> train = manager.GetTrainByID(Input::GetInteger("Enter train id"));
		if (train) Log::PrintTrain(&manager, train, logLevel);
		else std::cout << "Could not find a train with the given id." << std::endl;
	}
	catch (std::out_of_range& e)
	{
		std::cerr << "Index out of range " << e.what() << std::endl;
	}
	Input::Prompt();
}

// prints a train by a specific vehicle id
void Application::PrintTrainByVehicleID()
{
	std::shared_ptr<Train> train = manager.GetTrainByVehicle(Input::GetInteger("Enter vehicle id"));
	if (train) Log::PrintTrain(&manager, train, logLevel);
	else std::cout << "Could not find a train with the given vehicle id." << std::endl;
	Input::Prompt();
}

// prints all trains in simulation
void Application::PrintAllTrains()
{
	for (int i = 1; i <= manager.GetNumberOfTrains(); ++i)
	{
		Log::PrintTrain(&manager, manager.GetTrainByID(i), logLevel);
		std::cout << std::endl;
	}

	Input::Prompt();
}

// prints a vehicle
void Application::PrintVehicle()
{
	try
	{
		std::shared_ptr<Vehicle> vehicle = manager.FindVehicleByID(Input::GetInteger("Enter vehicle id"));
		if (vehicle)
		{
			Log::PrintVehicle(vehicle, logLevel);
		}
		else
		{
			std::cout << "Could not find a vehicle with the given id." << std::endl;
		}
	}
	catch (std::out_of_range& e)
	{
		std::cerr << "Index out of range " << e.what() << std::endl;
	}

	Input::Prompt();
}

// prints all vehicles in simulation
void Application::PrintAllVehicles()
{
	for (int i = 1; i <= manager.GetNumberOfVehicles(); ++i)
	{
		Log::PrintVehicle(manager.FindVehicleByID(i), logLevel);
		std::cout << std::endl;
	}

	Input::Prompt();
}

// sets the log level of simulation - low or high
void Application::ChangeLogLevel()
{
	logMenu.ShowSub();
}

// prints the final results
void Application::PrintStatistics()
{
	Log::PrintStatistics(&manager);
	Input::Prompt();
}

// print a vehicles position
void Application::PrintVehiclePosition()
{
	try
	{
		std::shared_ptr<Vehicle> vehicle = manager.FindVehicleByID(Input::GetInteger("Enter vehicle id"));
		if (vehicle)
		{
			Log::PrintVehiclePosition(vehicle);
		}
		else
		{
			std::cout << "Could not find a vehicle with the given id." << std::endl;
		}
	}
	catch (std::out_of_range& e)
	{
		std::cerr << "Index out of range " << e.what() << std::endl;
	}

	Input::Prompt();
}

// at the end of simulation sets the menu items to false
void Application::CloseMenuItems()
{
	simMenu.SetItemState(1, false);
	simMenu.SetItemState(2, false);
	simMenu.SetItemState(3, false);
	simMenu.SetItemState(4, false);
}

// print all history for a specific vehicle
void Application::PrintVehicleHistory()
{
	try
	{
		std::shared_ptr<Vehicle> vehicle = manager.FindVehicleByID(Input::GetInteger("Enter vehicle id"));
		if (vehicle)
		{
			Log::PrintVehicleHistory(vehicle);
		}
		else
		{
			std::cout << "Could not find a vehicle with the given id." << std::endl;
		}
	}
	catch (std::out_of_range& e)
	{
		std::cerr << "Index out of range " << e.what() << std::endl;
	}

	Input::Prompt();
}
