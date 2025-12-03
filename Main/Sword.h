#pragma once
#include "Weapon.h"

class Sword : public Weapon
{
public:
	Sword();
	~Sword();

	void ActivateSwordBuff() { myDamage += myBuffDamage; }

private:
	int myBuffDamage = 10;
};
