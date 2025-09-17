#include "Player.h"

Player::Player()
{
	myAttributes.myCurrentHealth = GetMaxHealth();
}

void Player::Update()
{
}

void Player::EnterRoom(int aRoomId)
{
}

float Player::GetDamage() const
{
	return myAttributes.strength * myAttributes.agility;
}

float Player::GetMaxHealth() const
{
	return (myAttributes.endurance * 4) + (myAttributes.strength * 6) + (myAttributes.agility * 3);
}

float Player::GetCurrentHealth() const
{
	return myAttributes.myCurrentHealth;
}

float Player::GetCarryCapacity() const
{
	return myAttributes.strength + (myAttributes.agility / 3);
}

float Player::GetDefense() const
{
	return myAttributes.endurance + myAttributes.agility;
}
