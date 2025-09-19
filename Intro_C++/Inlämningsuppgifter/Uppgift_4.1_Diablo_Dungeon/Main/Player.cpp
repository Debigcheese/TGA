#include "Player.h"
#include "GameStructs.h"
#include <iostream>
#include "Utils.h"

using namespace Utils;

Player::Player(WorldMap aWorldMap) : myWorldMap(aWorldMap)
{
	myAttributes.myCurrentHealth = GetMaxHealth();
}

void Player::Update()
{
	while (true)
	{
		Room* currentRoom = myWorldMap.GetRoomWithId(myRoomId);
		std::vector<Enemy>& enemies = currentRoom->GetEnemies();

		if (enemies.empty())
		{
			std::cout << "\nNo enemies in this room...\n";
			system("pause");
			return;
		}

		int enemiesKilled = 0;
		for (Enemy& enemy : enemies)
		{
			if (enemy.IsDead())
			{
				enemiesKilled++;
				if (enemies.size() == enemiesKilled)
				{
					std::cout << "\nAll enemies are dead.\n";
					system("pause");
					return;
				}
			}
		}

		std::cout
			<< "\n<--- Navigation --->\n"
			<< "1) West\n"
			<< "2) North\n"
			<< "3) East\n"
			<< "4) South\n"
			<< "Choice: ";

		int combatChoice = ReadIntInRange(1, 4);

		system("pause");
	}
}

int Player::GetRoomId() const
{
	return myRoomId;
}

void Player::SetRoomId(const int& aNewRoomId)
{
	myRoomId = aNewRoomId;
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

void Player::PrintAttributes() const
{
	std::cout << "";
}
