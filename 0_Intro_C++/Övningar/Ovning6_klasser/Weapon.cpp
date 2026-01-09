#include "Weapon.h"

Weapon::Weapon() : myName("Unknown"), myDamage(0), myType(Type::Dagger){}

void Weapon::Init(std::string newName, Type newType, int newDamage)
{
	myName = newName;
	myType = newType;
	SetDamage(newDamage);
}

std::string Weapon::GetName() const
{
	return myName;
}

std::string Weapon::GetWeaponTypeName() const
{
    switch(myType)
    {
    case Type::Dagger: return "Dagger";
    case Type::Bow: return "Bow";
    case Type::Sword: return "Sword";
    }
}

int Weapon::GetDamage() const
{
	return myDamage;
}

void Weapon::SetDamage(int newDamage) {
    switch (myType) {
    case Type::Dagger:
        if (newDamage < 10) newDamage = 10;
        if (newDamage > 20) newDamage = 20;
        break;
    case Type::Bow:
        if (newDamage < 10) newDamage = 10;
        if (newDamage > 40) newDamage = 40;
        break;
    case Type::Sword:
        if (newDamage < 30) newDamage = 30;
        if (newDamage > 100) newDamage = 100;
        break;
    }
    myDamage = newDamage;
}
