#include "Car.h"
#include <iostream>

void Car::Start()
{
	state = CarState::hasStarted;
}

void Car::Gas()
{
	if (state == CarState::hasStarted && state != CarState::destroyed) {
		std::cout << "VROOOM";
		gasCounter++;
	}
	if (gasCounter >= 3) {
		state == CarState::destroyed;
	}

}

void Car::Repair()
{
	gasCounter = 0;
	state = CarState::hasStarted;
}
