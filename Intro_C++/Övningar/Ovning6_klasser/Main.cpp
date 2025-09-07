// Ovning6_klasser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Car.h"
#include "Player.h"
#include "Weapon.h"

Player globalPlayer;
Weapon globalWeapon;
std::vector<Weapon> globalShop(3);

int ReadIntToRange(int aMin, int aMax);
void WeaponMenu();

int ReadIntToRange(int aMin, int aMax) 
{
    int value;
    while (true) 
    {
        std::cin >> value;
        if (std::cin.fail() || value < aMin || value > aMax) 
        {
            std::cout << "Invalid choice, choose between (" << aMin << " - " << aMax << "): ";
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
        << "Weapon (" << i+1 << "): "
            << globalShop[i].GetName() << "\t"
            << globalShop[i].GetWeaponTypeName() << "\t"
            << globalShop[i].GetDamage() << "\n";
    }

    std::cout << "\nWeapon Choice: ";

    globalWeapon = globalShop[ReadIntToRange(1, 3)];
}

int main()
{
    std::cout << "Choose name: ";

    std::string playerName;
    std::cin >> playerName;

    system("cls");

    //init shop by adding weapons
    globalShop[0].Init("Steel Dagger", Type::Dagger, 18); // clamped 10–20
    globalShop[1].Init("Hunter Bow  ", Type::Bow, 35);  // clamped 10–40
    globalShop[2].Init("Longsword   ", Type::Sword, 85);  // clamped 30–100

    WeaponMenu();

    system("cls");

    Weapon(dagger);
    dagger.Init("Dagger", Type::Dagger, 15);

    Weapon(Bow);
    Bow.Init("Bow", Type::Bow, 30);

    Weapon(Sword);
    Sword.Init("Sword", Type::Sword, 60);

    Player(player);
    player.Init("Lucas", 100, dagger);

    player.PrintStats();
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
