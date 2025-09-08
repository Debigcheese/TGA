// Ovning6_klasser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Car.h"
#include "Player.h"
#include "Weapon.h"
#include "UserManager.h"

Player globalPlayer;
Weapon globalWeapon;
std::vector<Weapon> globalShop(3);

UserManager globalUserManager;

int ReadIntInRange(int aMin, int aMax);
void WeaponMenu();
void UserMenu();

int ReadIntInRange(int aMin, int aMax)
{
	int value;
	while (true)
	{
		std::cin >> value;
		if (std::cin.fail() || value < aMin || value > aMax)
		{
			std::cout << "\nInvalid choice, choose between (" << aMin << " - " << aMax << "): ";
			std::cin.ignore(10000, '\n');
			std::cin.clear();
			continue;
		}
		return value;
	}
}

void WeaponMenu()
{
	std::cout
		<< "<--- WEAPON MENU ---> \n";

	for (int i = 0; i < globalShop.size(); i++)
	{
		std::cout
			<< "Weapon (" << i + 1 << "): "
			<< globalShop[i].GetName() << "\t"
			<< globalShop[i].GetWeaponTypeName() << "\t"
			<< globalShop[i].GetDamage() << "\n";
	}

	std::cout << "\nWeapon Choice: ";

	int weaponIndex = ReadIntInRange(1, 3);
	weaponIndex--;
	globalWeapon = globalShop[weaponIndex];
}

void UserMenu()
{
	while (true)
	{
		std::cout
			<< "<--- USER MENU ---> \n"
			<< "(1) Add user" << "\n"
			<< "(2) View all users" << "\n"
			<< "(3) View a single user" << "\n"
			<< "(4) Remove a user" << "\n"
			<< "(5) Exit" << "\n";

		int userMenuIndex = ReadIntInRange(1, 5);

		switch (userMenuIndex)
		{
		case 1:globalUserManager.AddUser(); break;
		case 2:globalUserManager.ViewAllUsers(); break;
		case 3:globalUserManager.ViewUser(); break;
		case 4:globalUserManager.RemoveUser(); break;
		case 5: return;
		}
		system("pause");
		system("cls");
	}
}

int main()
{

	system("cls");
	UserMenu();

	//std::cout << "Choose name: ";

	//std::string playerName;
	//std::cin >> playerName;

	////init shop by adding weapons
	//globalShop[0].Init("Steel Dagger", Type::Dagger, 18); // clamped 10–20
	//globalShop[1].Init("Hunter Bow  ", Type::Bow, 35);  // clamped 10–40
	//globalShop[2].Init("Longsword   ", Type::Sword, 85);  // clamped 30–100

	//WeaponMenu();

	//system("cls");

	//Player(player);
	//player.Init(playerName, 100, globalWeapon);

	//player.PrintStats();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
