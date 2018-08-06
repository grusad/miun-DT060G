/*
* Filename:		Locomotive.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "Locomotive.h"



Locomotive::Locomotive(int id, Type type, int maxSpeed) 
	:
	Vehicle(id, type),
	maxSpeed(maxSpeed)
{
}

Locomotive::~Locomotive()
{
}

int Locomotive::GetMaxSpeed()
{
	return maxSpeed;
}

ElectricLocomotive::ElectricLocomotive(int id, int maxSpeed, int kilowatt)
	:
	Locomotive(id, Type::ELECTRIC_ENGINE, maxSpeed),
	kilowatt(kilowatt)
{
}

int ElectricLocomotive::GetKilowatt()
{
	return kilowatt;
}

DieselLocomotive::DieselLocomotive(int id, int maxSpeed, int fuelUsage)
	:
	Locomotive(id, Type::DIESEL_ENGINE, maxSpeed),
	fuelUsage(fuelUsage)
{
}

int DieselLocomotive::GetFuelUsage()
{
	return fuelUsage;
}
