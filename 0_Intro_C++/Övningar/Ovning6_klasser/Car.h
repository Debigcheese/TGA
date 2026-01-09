#pragma once

enum class CarState {
	idle,
	hasStarted,
	destroyed,
};

class Car
{

	CarState state;
	int gasCounter; 
	void Start();
	void Gas();
	void Repair();

};

