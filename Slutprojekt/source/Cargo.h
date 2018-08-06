/*
* Filename:		Cargo.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef CARGO_H
#define CARGO_H

#include "Vehicle.h"

// different cargo types
class Cargo : public Vehicle
{
public:
	Cargo(Type type, int id);
	~Cargo() = 0;

};

class OpenCargo : public Cargo 
{

public:

	OpenCargo(int loadCapacity, int loadArea, int id);

	int GetLoadArea() const;
	int GetLoadCapacity() const;

private:

	int loadCapacity; // ton
	int loadArea; // kvadratmeter
};

class ClosedCargo : public Cargo 
{
public:

	ClosedCargo(int loadVolume, int id);

	int GetLoadVolume() const;

private:

	int loadVolume; // kubikmeter

};

#endif // !CARGO_H
