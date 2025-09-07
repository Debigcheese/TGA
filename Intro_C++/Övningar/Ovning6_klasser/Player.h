#pragma once

#include <iostream>
#include <string>
#include "Weapon.h"

class Player
{
private:
	std::string myName;
	int myHealth;
	Weapon myWeapon;

public:
	Player();

	void Init(const std::string& newName, int newHealth, Weapon newWeapon);
	void PrintStats() const;

	std::string GetName();
	Weapon GetWeapon() const;


};

