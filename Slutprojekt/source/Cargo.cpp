/*
* Filename:		Cargo.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "Cargo.h"

Cargo::Cargo(Type type, int id) : Vehicle(id, type)
{	
}

Cargo::~Cargo()
{
}

OpenCargo::OpenCargo(int loadCapacity, int loadArea, int id) : Cargo(Type::OPEN_CARGO, id)
{
	this->loadArea = loadArea;
	this->loadCapacity = loadCapacity;
};

int OpenCargo::GetLoadArea() const
{
	return loadArea;
}

int OpenCargo::GetLoadCapacity() const
{
	return loadCapacity;
}

ClosedCargo::ClosedCargo(int loadVolume, int id) : Cargo(Type::CLOSED_CARGO, id)
{
	this->loadVolume = loadVolume;
}

int ClosedCargo::GetLoadVolume() const
{
	return loadVolume;
}