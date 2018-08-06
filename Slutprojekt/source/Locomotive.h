/*
* Filename:		Locomotive.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include "Vehicle.h"

// different locomotive vehicles
class Locomotive : public Vehicle
{
public:
	Locomotive(int id, Type type, int maxSpeed);
	~Locomotive() = 0;

	int GetMaxSpeed();

private:
	int maxSpeed;
};

class ElectricLocomotive : public Locomotive
{
public:
	ElectricLocomotive(int id, int maxSpeed, int kilowatt);

	int GetKilowatt();

private:
	int kilowatt;
};

class DieselLocomotive : public Locomotive
{
public:
	DieselLocomotive(int id, int maxSpeed, int fuelUsage);

	int GetFuelUsage();

private:
	int fuelUsage; //liters per hour
};

#endif 