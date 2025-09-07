#include "Player.h"

Player::Player() : myName("Unknown"), myHealth(100), myWeapon() {}

void Player::Init(const std::string& newName, int newHealth, Weapon newWeapon)
{
	myName = newName;
	myHealth = newHealth;
	myWeapon = newWeapon;
}	

void Player::PrintStats() const
{
	std::cout
		<< myName << " stats:\n"
		<< "Health: " << myHealth << "\n"
		<< "Weapon: " << GetWeapon().GetName() << "\n"
		<< "Damage: " << GetWeapon().GetDamage() << "\n";

}

std::string Player::GetName()
{
	return myName;
}

Weapon Player::GetWeapon() const
{
	return myWeapon;
}
