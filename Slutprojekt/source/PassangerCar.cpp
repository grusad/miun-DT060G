/*
* Filename:		PassangerCar.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "PassangerCar.h"

PassangerCar::PassangerCar(Type type, int id) : Vehicle(id, type)
{
}

PassangerCar::~PassangerCar()
{
}

int DayCar::GetSeatSize() const {
	return seatSize;
}

bool DayCar::HasInternet() const
{
	return internetConnection;
}

int NightCar::GetBedSize() const
{
	return bedSize;
}