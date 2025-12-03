#pragma once
#include <string>

class Weapon
{
public:
	Weapon();
	~Weapon();

	std::string GetName() const { return myName; }
	int GetDamage() const { return myDamage; }

	void SetDamage(int aDamage) { myDamage = aDamage; }
	void SetName(std::string aName) { myName = aName; }

protected:
	std::string myName;
	int myDamage;
	float myAttackSpeed;
};
