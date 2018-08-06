/*
* Filename:		Application.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "RailroadManager.h"
#include "Menu.h"
#include "Log.h"

// The main-program class
class Application
{
public:
	Application();
	
	void ShowMenu();
	void RunApplication();

private:
	void SetStartTime();
	void SetStopTime();
	void ChangeInterval();
	void CompleteSimulation();
	void RunNextInterval();
	void RunNextEvent();
	void RunTrainMenu();
	void RunStationMenu();
	void RunVehicleMenu();
	void PrintStationNames();
	void PrintStationByName();
	void PrintAllStations();
	void PrintTrainByTrainID();
	void PrintTrainByVehicleID();
	void PrintAllTrains();
	void PrintVehicle();
	void PrintAllVehicles();
	void ChangeLogLevel();
	void PrintStatistics();
	void PrintVehiclePosition();
	void CloseMenuItems();
	void PrintVehicleHistory();


private:
	Time simulationTime;
	Time startTime;
	Time stopTime;
	int intervalMins;
	RailroadManager manager;
	LogLevel logLevel = LogLevel::HIGH;

	Menu main;
	Menu simMenu;
	Menu trainMenu;
	Menu stationMenu;
	Menu vehicleMenu;
	Menu logMenu;
};

#endif // !APPLICATION_H
