#pragma once
#include <string>

enum class Weapon{
	Sword,
	Dagger,
	Bow,
};

class Player
{
	Player(std::string myName, int myHealth, int myWeapon);

	void Init();
	void PrintStats() const;

private:
	std::string myName;
	int myHealth;
	int myWeapon
};

