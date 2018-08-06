/*
* Filename:		Event.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "Event.h"
#include "Station.h"
#include "RailroadManager.h"
#include "RailWay.h"
#include "Log.h"

void AssembleEvent::processEvent()
{
	if (station->AssembleTrain(train)) // is given train got assembled
	{
		// push a departure event
		manager->PushEvent(new DepartureEvent(manager, station, manager->GetRailway(train->GetDeparture(), train->GetDestination()), train, train->GetDepartureTime()));
		manager->PushEvent(new NotifyReadyEvent(manager, train, train->GetDepartureTime() -= 10));

		Log::TrainInfo(train, time, "Is now assembled.");
		train->UpdateVehicleEvents(VehicleEvent(station, train, time, EventType::ATTACH_TRAIN)); // log to history
	}
	else 
	{

		train->UpdateVehicleEvents(VehicleEvent(station, train, time, EventType::ATTACH_TRAIN));
		manager->PushEvent(new AssembleUncompletedEvent(manager, station, train, time));

	}
}

void AssembleUncompletedEvent::processEvent()
{

	if (station->AssembleUncompletedTrain(train)) // if incomplete train got assembled.
	{
		Time departureTime = time;
		departureTime += 30; // departure in 30 mins
		Time notifyTime = time;
		notifyTime += 20; // set train to ready in 20 mins.
		// push events
		manager->PushEvent(new DepartureEvent(manager, station, manager->GetRailway(train->GetDeparture(), train->GetDestination()), train, departureTime));
		manager->PushEvent(new NotifyReadyEvent(manager, train, notifyTime));
		Log::TrainInfo(train, time, "Went from incomplete to assembled.");
	}
	else
	{
		train->SetDelay(train->GetDelay() += 10); // delay of train increment with 10 minutes.
		Time retryTime = time;
		retryTime += 10;
		manager->PushEvent(new AssembleUncompletedEvent(manager, station, train, retryTime)); // new try in 10 min.
		Log::TrainInfo(train, time, "Is now incomplete, next try in 10 minutes.");
	}
}

void DepartureEvent::processEvent()
{

	Time arrivalTime; 

	if (train->GetDelay().ToMinutes() > 0) // if train has delay
	{

		if (time > train->GetDestinationTime()) // if currenttime is greater than the trains destination time
		{
			int tripTime = (60 * railway->GetDistance()) / train->GetMaxSpeed(); // travel time at max speed
			arrivalTime = time;
			arrivalTime += tripTime;

			train->SetCurrentSpeed(train->GetMaxSpeed());
			Time delayTime = arrivalTime;
			train->SetDelay(delayTime -= train->GetDestinationTime().ToMinutes());
		}
		else if (time > train->GetDepartureTime()) // if current time is greater than the trains departure time
		{
			int tripTime = (60 * railway->GetDistance()) / (time.ToMinutes() + train->GetDestinationTime().ToMinutes());
			int reqSpd = (60 * railway->GetDistance()) / tripTime; // calculate the required speed to get to destination in time
			if (reqSpd > train->GetMaxSpeed()) // if required speed is greater than max speed
			{
				tripTime = (60 * railway->GetDistance()) / train->GetMaxSpeed();
				arrivalTime = time;
				arrivalTime += tripTime;
				train->SetCurrentSpeed(train->GetMaxSpeed());
				Time delayTime = arrivalTime;
				train->SetDelay(delayTime -= train->GetDestinationTime().ToMinutes());
			}
			else
			{
				train->SetCurrentSpeed(reqSpd);
			}
		}

	}
	else
	{
		// no delay
		int tripTime = train->GetDestinationTime().ToMinutes() - train->GetDepartureTime().ToMinutes();
		// sets the normal speed
		train->SetCurrentSpeed((60 * railway->GetDistance()) / tripTime);
		arrivalTime = train->GetDestinationTime();
	}
	
	railway->AddTrain(station->SendTrain()); // sends the train from station to railway
	manager->PushEvent(new ArrivalEvent(manager, manager->GetStation(train->GetDestination()), railway, train, arrivalTime));

	Log::TrainInfo(train, time, "Now departing");
	train->UpdateVehicleEvents(VehicleEvent(station, train, time, EventType::LEFT_STATION));
}

void ArrivalEvent::processEvent()
{
	railway->RemoveTrain(train->GetTrainID()); // removes train from railway
	station->ReceiveTrain(train);			// sends train to station
	Time diassembleTime = time;
	diassembleTime += 20; // diassemble event in 20 minutes
	manager->PushEvent(new DiassembleEvent(manager, station, train, diassembleTime));

	Log::TrainInfo(train, time, "Now arriving.");
	train->UpdateVehicleEvents(VehicleEvent(station, train, time, EventType::ARRIVED_STATION));
}

void DiassembleEvent::processEvent()
{
	train->UpdateVehicleEvents(VehicleEvent(station, train, time, EventType::ENTER_STATION));
	station->DisassembleTrain(train); // diassembles the train
	Log::TrainInfo(train, time, "Is now diassembled.");
}

void NotifyReadyEvent::processEvent()
{
	train->SetState(State::READY); // set state of train to ready
	Log::TrainInfo(train, time, "Has arrived to platform.");
}
