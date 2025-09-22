#include "Player.h"
#include "GameStructs.h"
#include "WorldMap.h"
#include "Enemy.h"
#include "Utils.h"
#include <vector>
#include <iostream>

using namespace Utils;

Player::Player(WorldMap& aWorldMap) : myWorldMap(aWorldMap), myRoomId(0), myTargetIndex(-1), myIsDead(false), myName("(-)")
{
	myAttributes.myCurrentHealth = GetMaxHealth();
}

void Player::Update()
{
	while (true)
	{
		Room* currentRoom = myWorldMap.GetRoomWithId(myRoomId);
		std::vector<Enemy>& enemies = currentRoom->GetEnemies();

		if (myTargetIndex < 0 && enemies.size() > 1)
		{
			PrintPlayerUI();
			currentRoom->PrintEnemies();
			ChooseTarget();
			system("cls");
		}
		else
		{
			myTargetIndex = 0;
		}

		PrintPlayerUI();
		currentRoom->PrintEnemiesWithTarget(myTargetIndex);
		ChooseAttack();
		system("cls");

		PrintPlayerUI();
		currentRoom->PrintEnemiesWithTarget(myTargetIndex);

		int damage = GetDamageFromAttackType(myAttackIndex);
		int enemyOldHp = enemies[myTargetIndex].GetCurrentHealth();

		enemies[myTargetIndex].TakeDamage(damage);
		std::cout << "\nYou dealt " << damage << " dmg to " << EnemyTypeToString(enemies[myTargetIndex].GetType());
		std::cout << " (" << enemyOldHp << "hp -> " << enemies[myTargetIndex].GetCurrentHealth() << "hp)" << "\n";
		system("pause");

		if (enemies[myTargetIndex].IsDead())
		{
			std::cout << "\n" << EnemyTypeToString(enemies[myTargetIndex].GetType()) << " has been slained!\n";
			system("pause");
		}

		system("cls");
		PrintPlayerUI();
		bool shouldChangeTarget = false;

		if (enemies[myTargetIndex].IsDead() && !enemies.empty())
		{
			currentRoom->RemoveEnemyFromRoom(enemies[myTargetIndex].GetId());
			enemies = currentRoom->GetEnemies();
			myTargetIndex = -1;
			currentRoom->PrintEnemies();
		}
		else
		{
			currentRoom->PrintEnemiesWithTarget(myTargetIndex);
		}

		if (enemies.empty())
		{
			std::cout << "\nYou have slain all enemies in this room!\n";
			myTargetIndex = -1;
			system("pause");
			break;
		}
		else
		{

			std::cout << "\n";
			for (Enemy& enemy : enemies)
			{
				enemy.Attack(*this);
			}
			system("pause");
		}
	}
}

void Player::EnterCombat()
{
	if (myWorldMap.GetRoomWithId(myRoomId)->DoesEnemiesExist())
	{
		Update();
	}
}

void Player::ChooseTarget()
{
	std::cout
		<< "\n<--- Choose Target --->\n"
		<< "Choice: ";
	int enemyCount = myWorldMap.GetRoomWithId(myRoomId)->GetEnemies().size();
	myTargetIndex = ReadIntInRange(1, enemyCount) - 1;
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
	if (myAttributes.myCurrentHealth <= 0.0f)
	{
		myAttributes.myCurrentHealth = 0.0f;
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

void Player::SetName(std::string aNewName)
{
	myName = aNewName;
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
	return (1.0f + (GetDefense() / 150.0f)); // (defense {20-198} /200) 
}

bool Player::IsDead() const
{
	return myIsDead;
}

void Player::PrintTarget(const Enemy& aEnemy) const
{
	std::cout << static_cast<int>(aEnemy.GetCurrentHealth()) << "/" << static_cast<int>(aEnemy.GetMaxHealth()) << " hp";
}

void Player::PrintHealth() const
{
	std::cout << "Health: " << static_cast<int>(GetCurrentHealth()) << "/" << static_cast<int>(GetMaxHealth()) << " hp";
}

void Player::PrintUserName() const
{
	std::cout << "Username: " << myName;
}

void Player::PrintPlayerUI() const
{
	system("cls");
	PrintUserName();
	std::cout << "\n";
	PrintHealth();
	std::cout << "\n";
	std::cout << "Room: " << myWorldMap.GetRoomWithId(myRoomId)->GetRoomName();
	std::cout << "\n";

}

void Player::PrintAttributes() const
{
	std::cout << "Player Username: " << myName << "\n\n";

	std::cout << "[Base Attributes] " << "\n";
	std::cout << "Strength:  " << static_cast<int>(myAttributes.strength) << "/99" << "\n";
	std::cout << "Agility:   " << static_cast<int>(myAttributes.agility) << "/99" << "\n";
	std::cout << "Endurance: " << static_cast<int>(myAttributes.endurance) << "/99" << "\n\n";

	std::cout << "[Derived Attributes] " << "\n";
	std::cout << "Attack Damage: " << static_cast<int>(GetDamage()) << " AD" << "\n";
	std::cout << "Max-Health :   " << static_cast<int>(GetMaxHealth()) << " hp" << "\n";
	std::cout << "Defense:       " << static_cast<int>(GetDefense()) << "\n";
	std::cout << "Carry Capacity " << static_cast<int>(GetCarryCapacity()) << "\n\n";

}

void Player::PrintDerivedAttributes() const
{
	std::cout << "Player Username: " << myName << "\n\n";

	std::cout << "[Base Attributes] " << "\n";
	std::cout << "Strength:  " << static_cast<int>(myAttributes.strength) << "/99" << "\n";
	std::cout << "Agility:   " << static_cast<int>(myAttributes.agility) << "/99" << "\n";
	std::cout << "Endurance: " << static_cast<int>(myAttributes.endurance) << "/99" << "\n\n";

	std::cout << "[Derived Attributes] " << "\n";
	std::cout << "Attack Damage: " << static_cast<int>(GetDamage()) << " AD" << " (Strength * Agility)" << "\n";
	std::cout << "Max-Health:    " << static_cast<int>(GetMaxHealth()) << " hp" << " (Endurance * 4 + Strength * 6 + Agility * 3)" << "\n";
	std::cout << "Defense:       " << static_cast<int>(GetDefense()) << " (Endurance + Agility)" << "\n";
	std::cout << "Carry Capacity " << static_cast<int>(GetCarryCapacity()) << " (Strength + Agility / 3)" << "\n\n";
}

void Player::EnterAttributesMenu()
{
	while (true)
	{
		system("cls");
		myWorldMap.GetRoomWithId(myRoomId)->PrintRoomName();
		std::cout << "\n";
		PrintHealth();
		std::cout << "\n";

		std::cout
			<< "\n<--- Attributes --->\n"
			<< "1) Attributes\n"
			<< "2) Derived Attributes Info\n"
			<< "3) Return\n"
			<< "Choice: ";

		int AttriMenuChoice = ReadIntInRange(1, 3);
		bool shouldExit = false;
		system("cls");

		switch (AttriMenuChoice)
		{
		case 1:
		{
			PrintAttributes();
			system("pause");
			break;
		}
		case 2:
		{
			PrintDerivedAttributes();
			system("pause");
			break;
		}
		case 3:
		{
			shouldExit = true;
			break;
		}
		}
		if (shouldExit)
		{
			break;
		}
	}

}
