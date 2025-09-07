#pragma once
#include <string>

enum class Type{
	Sword,
	Dagger,
	Bow,
};

class Weapon
{
private:
	std::string myName;
	Type myType;
	int myDamage;

public: 
	Weapon();

	void Init(std::string name, Type type, int damage);
	void SetDamage(int newDamage);

	int GetDamage() const;
	std::string GetName() const;
	std::string GetWeaponTypeName() const;


};

