/*
* Filename:		Log.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#ifndef LOG_H
#define LOG_H

#include "Train.h"
#include "Station.h"
#include <string>
#include "RailroadManager.h"

// Log level of application
enum class LogLevel
{
	LOW, HIGH,
};

// A log class for printing to screen and writing to file.
class Log
{
public:

	static void TrainInfo(std::shared_ptr<Train> train, Time currentTime, std::string message);
	static void SimInterval(Time currentTime, int interval);

	static void PrintTrain(RailroadManager* manager, const std::shared_ptr<Train> &train, LogLevel logLevel);
	static void PrintStation(RailroadManager* manager, const std::shared_ptr<Station>& station, LogLevel logLevel) ;
	static void PrintVehicle(const std::shared_ptr<Vehicle>& vehicle, LogLevel logLevel);
	static void PrintVehiclePosition(std::shared_ptr<Vehicle>& vehicle);
	static void PrintStatistics(RailroadManager* manager);
	static void PrintVehicleHistory(std::shared_ptr<Vehicle>& vehicle);

	static std::string ToString(LogLevel logl);

};



#endif