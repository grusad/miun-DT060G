/*
* Filename:		PassangerCar.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#ifndef PASSANGER_CAR_H
#define PASSANGER_CAR_H

#include "Vehicle.h"


// different passaanger vehicles
class PassangerCar : public Vehicle
{

public:

	PassangerCar(Type type, int id);
	virtual ~PassangerCar() = 0;


};


class DayCar : public PassangerCar
{
	
public:

	DayCar(int seatSize, bool internetConnection, int id)
		: PassangerCar(Type::DAY_COACH, id) {
		this->internetConnection = internetConnection;
		this->seatSize = seatSize;
	};

	bool HasInternet() const;
	int GetSeatSize() const;


private:

	bool internetConnection;
	int seatSize;

};

class NightCar : public PassangerCar
{

public:

	NightCar(int bedSize, int id)
		: PassangerCar(Type::NIGHT_COACH, id) { this->bedSize = bedSize; };

	int GetBedSize() const;

private:

	int bedSize;

};



#endif // !PASSANGER_CAR_H
