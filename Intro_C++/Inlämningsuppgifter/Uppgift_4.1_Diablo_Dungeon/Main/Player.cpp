#include "Player.h"
#include "GameStructs.h"
#include "WorldMap.h"
#include "Enemy.h"
#include "Utils.h"
#include <vector>
#include <iostream>

using namespace Utils;

Player::Player(WorldMap aWorldMap) : myWorldMap(aWorldMap), myRoomId(0), myTargetIndex(-1), myIsDead(false)
{
	myAttributes.myCurrentHealth = GetMaxHealth();
}

void Player::Update()
{
	while (true)
	{
		system("cls");
		Room* currentRoom = myWorldMap.GetRoomWithId(myRoomId);
		std::vector<Enemy>& enemies = currentRoom->GetEnemies();

		if (myTargetIndex < 0)
		{
			currentRoom->PrintRoomName();
			std::cout << "\n";
			PrintHealth();
			std::cout << "\n";
			currentRoom->PrintEnemies();
			std::cout << "\n\n";
			ChooseTarget(enemies);
		}

		system("cls");
		currentRoom->PrintRoomName();
		std::cout << "\n";
		PrintHealth();
		std::cout << "\n";
		PrintTarget(enemies[myTargetIndex]);
		std::cout << "\n\n";
		ChooseAttack();

		system("cls");
		currentRoom->PrintRoomName();
		std::cout << "\n";
		PrintHealth();
		std::cout << "\n";
		currentRoom->PrintEnemiesWithTarget(myTargetIndex);
		std::cout << "\n\n";

		int damage = GetDamageFromAttackType(myAttackIndex);
		int enemyOldHp = enemies[myTargetIndex].GetCurrentHealth();

		enemies[myTargetIndex].TakeDamage(damage);
		std::cout << EnemyTypeToString(enemies[myTargetIndex].GetType()) << " took " << damage << "dmg\n";
		std::cout << "Health: " << enemyOldHp << " -> " << enemies[myTargetIndex].GetCurrentHealth();
		system("pause");

		system("cls");
		currentRoom->PrintRoomName();
		std::cout << "\n";
		PrintHealth();
		std::cout << "\n";

		if (enemies[myTargetIndex].IsDead() && !enemies.empty())
		{
			currentRoom->RemoveEnemyFromRoom(enemies[myTargetIndex].GetId());
			myTargetIndex = -1;
		}
		PrintTarget(enemies[myTargetIndex]);
		std::cout << "\n\n";
		if (enemies.empty())
		{
			std::cout << "\nAll enemies are dead.\n";
			myTargetIndex = -1;
			system("pause");
			break;
		}
		else
		{
			for (Enemy& enemy : enemies)
			{
				enemy.Attack(*this);
			}
		}
	}
}

void Player::EnterCombat()
{
	Update();
}

void Player::ChooseTarget(const std::vector<Enemy>& aEnemies)
{
	std::cout
		<< "\n<--- Choose Target --->\n";
	for (int i = 0; i < aEnemies.size(); i++)
	{
		std::cout << i + 1 << ") "
			<< EnemyTypeToString(aEnemies[i].GetType()) << " "
			<< static_cast<int>(aEnemies[i].GetCurrentHealth()) << "/"
			<< static_cast<int>(aEnemies[i].GetMaxHealth()) << " HP | "
			<< static_cast<int>(aEnemies[i].GetDamage()) << " AD" << "\n";
	}
	std::cout
		<< "Choice: ";
	myTargetIndex = ReadIntInRange(1, aEnemies.size()) - 1;
}

void Player::ChooseAttack()
{
	std::cout
		<< "\n<--- Choose Attack --->\n"
		<< "1) Quick attack" << "\n"
		<< "2) Heavy attack\n"
		<< "Choice: ";
	myAttackIndex = ReadIntInRange(1, 2) - 1;
}

void Player::TakeDamage(const float aDamage)
{
	float newDamage = aDamage / GetDefenseMultiplier();
	myAttributes.myCurrentHealth -= newDamage;
	if (myAttributes.myCurrentHealth <= 0)
	{
		myAttributes.myCurrentHealth = 0;
		myIsDead = true;
		IsDead();
	}
}

float Player::GetDamageFromAttackType(const int& aAttackIndex) const
{
	float newDamage = 0.0f;
	switch (aAttackIndex)
	{
	case 0:
	{
		newDamage = static_cast<float>(GenerateRandomNumber(GetDamage(), GetDamage()));
		break;
	}
	case 1:
	{
		newDamage = static_cast<float>(GenerateRandomNumber(GetDamage() * 0.8f, GetDamage() * 1.2f));
		break;
	}
	}
	return newDamage;
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

float Player::GetDefenseMultiplier() const
{
	return (1 + (GetDefense() / 150)); // (defense {20-198} /200) 
}

bool Player::IsDead() const
{
	return myIsDead;
}

void Player::PrintTarget(const Enemy& aEnemy) const
{
	std::cout << static_cast<int>(aEnemy.GetCurrentHealth()) << "/" << static_cast<int>(aEnemy.GetMaxHealth()) << " HP";
}

void Player::PrintHealth() const
{
	std::cout << static_cast<int>(GetCurrentHealth()) << "/" << static_cast<int>(GetMaxHealth()) << " HP";
}

void Player::PrintAttributes() const
{
	std::cout << "";
}
