// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "Bow.h"
#include "Sword.h"

int main()
{
	std::cout << "Welcome to Swords and sandelz\n";
	std::cout << "Enter your name: ";

	std::string name;
	std::cin >> name;

	std::vector<Weapon*> myWeapons;
	std::vector<Sword*> mySwords;

	auto* sword = new Sword();
	sword->SetDamage(5);
	sword->SetName("Iron Sword");

	myWeapons.push_back(sword);

	auto* godSword = new Sword();
	godSword->SetDamage(20);
	godSword->SetName("GodSword");

	myWeapons.push_back(godSword);

	auto* bow = new Bow();
	bow->SetDamage(20);
	bow->SetRange(10);
	bow->SetName("Goddess bow");

	myWeapons.push_back(bow);
	myWeapons.push_back(bow);

	for (const auto& weapon : myWeapons)
	{
		std::cout << weapon->GetName() << "\n";
	}

	for (int i = static_cast<int>(myWeapons.size() - 1); i >= 0; --i)
	{
		if (myWeapons[i]->GetDamage() >= 20)
		{
			myWeapons.erase(myWeapons.begin() + i);
		}
	}


	//std::erase_if(myWeapons, [](Weapon* weapon)
	//{
	//	return weapon->GetDamage() >= 20;
	//});


	for (const auto& weapon : myWeapons)
	{
		std::cout << weapon->GetName() << "\n";
	}
}
