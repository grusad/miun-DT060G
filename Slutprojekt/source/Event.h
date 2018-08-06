/*
* Filename:		Event.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#ifndef EVENT_H
#define EVENT_H

#include "Time.h"
#include <memory>
#include "Train.h"

class RailroadManager;
class Station;
class Railway;

// different event classes
class Event
{
public:
	Event(RailroadManager* manager, std::shared_ptr<Train> train, Time time) : manager(manager), train(train), time(time) {};
	virtual ~Event() {};

	virtual void processEvent() = 0;

	Time GetTime() const { return time; };
	State GetTrainState() const { return train->GetState(); };
	int getTrainID() const { return train->GetTrainID(); };
	
protected:
	Time time;
	RailroadManager* manager;
	std::shared_ptr<Train> train;
};

class AssembleEvent : public Event
{
public:
	AssembleEvent(RailroadManager* manager, std::shared_ptr<Station> station, std::shared_ptr<Train> train, Time time)
		: Event(manager, train, time), station(station) {};

	void processEvent() override;

private:
	std::shared_ptr<Station> station;
};

class AssembleUncompletedEvent : public Event
{
public:
	AssembleUncompletedEvent(RailroadManager* manager, std::shared_ptr<Station> station, std::shared_ptr<Train> train, Time time)
		: Event(manager, train, time), station(station) {};

	void processEvent() override;

private:
	std::shared_ptr<Station> station;
};

class DepartureEvent : public Event
{
public:
	DepartureEvent(RailroadManager* manager, std::shared_ptr<Station> station, std::shared_ptr<Railway> railway, std::shared_ptr<Train> train, Time time)
		: Event(manager, train, time), station(station), railway(railway) {};

	void processEvent() override;

private:
	std::shared_ptr<Station> station;
	std::shared_ptr<Railway> railway;
};

class ArrivalEvent : public Event
{
public:
	ArrivalEvent(RailroadManager* manager, std::shared_ptr<Station> station, std::shared_ptr<Railway> railway, std::shared_ptr<Train> train, Time time)
		: Event(manager, train, time), station(station), railway(railway) {};

	void processEvent() override;

private:
	std::shared_ptr<Station> station;
	std::shared_ptr<Railway> railway;
};

class DiassembleEvent : public Event
{
public:
	DiassembleEvent(RailroadManager* manager, std::shared_ptr<Station> station, std::shared_ptr<Train> train, Time time)
		: Event(manager, train, time), station(station) {};

	void processEvent() override;

private:
	std::shared_ptr<Station> station;
};

class NotifyReadyEvent : public Event
{
public:
	NotifyReadyEvent(RailroadManager* manager, std::shared_ptr<Train> train, Time time)
		: Event(manager, train, time) {};

	void processEvent() override;
};

// a functor for the main event priority queue
class EventComparison {
public:
	bool operator() (Event* left, Event* right) {
		return left->GetTime().ToMinutes() > right->GetTime().ToMinutes();
	}
};





#endif //-EVENT_H