#include "Player.h"
#include "WorldMap.h"
#include "Enemy.h"
#include "Utils.h"
#include "Cheats.h"
#include "GameConstants.h"
#include "Item.h"

#include <vector>
#include <iostream>

using namespace Utils;
using namespace GameConstants;

Player::Player(WorldMap& aWorldMap) : myWorldMap(aWorldMap), myRoomId(0), myTargetIndex(-1), myIsDead(false),
                                      myName("(-)"), myPos{0, 0}, myInventory()
{
	myAttributes.currentHealth = GetMaxHealth();
	myItemAttributes = {};
}

void Player::Update()
{
	while (true && !IsDead())
	{
		Room* currentRoom = myWorldMap.GetRoomWithId(myRoomId);
		std::vector<Enemy>& enemies = currentRoom->GetEnemies();

		if (IsInvalidAttackIndex() || enemies.size() > 1)
		{
			PrintPlayerUI();
			currentRoom->PrintEnemies();
			ChooseTarget();
			system("cls");
		}
		else
		{
			myTargetIndex = PLAYER_ATTACK_INDEX_ZERO;
		}

		PrintPlayerUI();
		currentRoom->PrintEnemiesWithTarget(myTargetIndex);
		ChooseAttack();
		system("cls");

		PrintPlayerUI();
		currentRoom->PrintEnemiesWithTarget(myTargetIndex);

		float damage = GetDamageFromAttackType(myAttackIndex);
		float enemyOldHp = enemies[myTargetIndex].GetCurrentHealth();
		enemies[myTargetIndex].TakeDamage(damage);
		std::cout << "\nYou dealt " << static_cast<int>(damage) << " dmg to " << enemies[myTargetIndex].GetName();
		std::cout << " (" << static_cast<int>(enemyOldHp) << "hp -> " << static_cast<int>(enemies[myTargetIndex].
			GetCurrentHealth()) << "hp)" << "\n";
		system("pause");

		if (enemies[myTargetIndex].IsDead())
		{
			std::cout << "\n" << enemies[myTargetIndex].GetName() << " has been slained!\n";
			system("pause");
		}

		system("cls");
		PrintPlayerUI();

		if (enemies[myTargetIndex].IsDead())
		{
			currentRoom->RemoveEnemyFromRoom(enemies[myTargetIndex].GetId());
			enemies = currentRoom->GetEnemies();
			myTargetIndex = PLAYER_ATTACK_INDEX_INVALID;
			currentRoom->PrintEnemies();
		}
		else
		{
			currentRoom->PrintEnemiesWithTarget(myTargetIndex);
		}

		if (enemies.empty())
		{
			std::cout << "\nYou have slain all enemies in this room!\n";
			myTargetIndex = PLAYER_ATTACK_INDEX_INVALID;
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
	int enemyCount = static_cast<int>(myWorldMap.GetRoomWithId(myRoomId)->GetEnemies().size());
	myTargetIndex = ReadIntInRange(PLAYER_TARGET_ENEMY_MIN, enemyCount) - PLAYER_TARGET_INDEX_OFFSET;
}

void Player::ChooseAttack()
{
	std::cout
		<< "\n<--- Choose Attack --->\n"
		<< "1) Quick attack" << "\n"
		<< "2) Heavy attack\n"
		<< "Choice: ";
	myAttackIndex = ReadIntInRange(
		static_cast<int>(AttackType::QuickAttack),
		static_cast<int>(AttackType::HeavyAttack)) - PLAYER_ATTACK_INDEX_OFFSET;
}

void Player::TakeDamage(const float aDamage)
{
	if (Cheats::GetCheats().invincible)
	{
		return;
	}
	const float dmgFloat = aDamage / GetDefenseMultiplier();
	myAttributes.currentHealth -= dmgFloat;
	if (myAttributes.currentHealth <= HEALTH_ZERO)
	{
		myAttributes.currentHealth = HEALTH_ZERO;
		myIsDead = true;
		std::cout << "\n" << "You died!";
		std::cout << "\n" << "Quitting game...\n";
		system("pause");
		return;
	}
}

float Player::GetDamageFromAttackType(int aAttackIndex) const
{
	float newDamage = DAMAGE_ZERO;
	AttackType atkType = static_cast<AttackType>(aAttackIndex + PLAYER_ATTACK_INDEX_OFFSET);
	switch (atkType)
	{
	case AttackType::QuickAttack:
		{
			newDamage = GetAttributes().damage;
			break;
		}
	case AttackType::HeavyAttack:
		{
			const int heavyMinMulti = static_cast<int>(GetAttributes().damage * HEAVY_MULTI_MIN);
			const int heavyMaxMulti = static_cast<int>(GetAttributes().damage * HEAVY_MULTI_MAX);
			newDamage = static_cast<float>(GenerateRandomNumber(heavyMinMulti, heavyMaxMulti));
			break;
		}
	case AttackType::None:
		{
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

void Player::SetName(const std::string& aNewName)
{
	myName = aNewName;
}

void Player::SetIsDead(bool aIsDead)
{
	myIsDead = aIsDead;
}

void Player::SetPosition(const Position& aNewPosition)
{
	myPos = aNewPosition;
}

void Player::SetItemAttributes(const Attributes& aItemAttributes)
{
	myItemAttributes = aItemAttributes;
}

float Player::GetDamage() const
{
	if (Cheats::GetCheats().oneShot)
	{
		return myAttributes.strength * myAttributes.agility * CHEATS_ONESHOT_MULTI;
	}
	return myAttributes.strength * myAttributes.agility;
}

float Player::GetMaxHealth() const
{
	return (myAttributes.endurance * ATTRI_GET_HEALTH_ENDURANCE_MULTI) +
		(myAttributes.strength * ATTRI_GET_HEALTH_STRENGTH_MULTI) +
		(myAttributes.agility * ATTRI_GET_HEALTH_AGILITY_MULTI);
}

float Player::GetCarryCapacity() const
{
	return myAttributes.strength + (myAttributes.agility / ATTRI_GET_CARRY_AGILITY_DIV);
}

float Player::GetDefense() const
{
	return myAttributes.endurance + myAttributes.agility;
}

float Player::GetDefenseMultiplier() const
{
	return (DEFENSE_BASE_MULTI + (GetAttributes().defense / DEFENSE_SCALING_FACTOR)); // (defense {20-198} /200) 
}

bool Player::IsDead() const
{
	return myIsDead;
}

bool Player::IsInvalidAttackIndex() const
{
	return myAttackIndex < PLAYER_ATTACK_INDEX_ZERO;
}

std::string Player::GetName() const
{
	return myName;
}

const Attributes& Player::GetBaseAttributes() const
{
	return {

		myAttributes.strength,
		myAttributes.agility,
		myAttributes.endurance,
		GetMaxHealth(),
		myAttributes.currentHealth,
		GetCarryCapacity(),
		GetDamage(),
		GetDefense(),
	};
}

Attributes Player::GetAttributes() const
{
	return {

		GetBaseAttributes().strength + myItemAttributes.strength,
		myAttributes.agility + myItemAttributes.agility,
		myAttributes.endurance + myItemAttributes.endurance,
		GetMaxHealth() + myItemAttributes.maxHealth,
		myAttributes.currentHealth + myItemAttributes.currentHealth,
		GetCarryCapacity() + myItemAttributes.carryCapacity,
		GetDamage() + myItemAttributes.damage,
		GetDefense() + myItemAttributes.defense
	};
}

Position Player::GetPosition() const
{
	return myPos;
}

void Player::PrintHealth() const
{
	std::cout << "Health: "
		<< static_cast<int>(GetAttributes().currentHealth) << "/"
		<< static_cast<int>(GetAttributes().maxHealth) << " hp";
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
	std::cout << "Strength:  " << static_cast<int>(GetAttributes().strength) << "/99" << "\n";
	std::cout << "Agility:   " << static_cast<int>(GetAttributes().agility) << "/99" << "\n";
	std::cout << "Endurance: " << static_cast<int>(GetAttributes().endurance) << "/99" << "\n\n";

	std::cout << "[Derived Attributes] " << "\n";
	std::cout << "Attack Damage: " << static_cast<int>(GetAttributes().damage) << " AD" << "\n";
	std::cout << "Max-Health :   " << static_cast<int>(GetAttributes().maxHealth) << " hp" << "\n";
	std::cout << "Defense:       " << static_cast<int>(GetAttributes().defense) << "\n";
	std::cout << "Carry Capacity " << static_cast<int>(GetAttributes().carryCapacity) << "\n\n";
}

void Player::PrintBaseAttributes() const
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
	std::cout << "Max-Health:    " << static_cast<int>(GetMaxHealth()) << " hp" <<
		" (Endurance * 4 + Strength * 6 + Agility * 3)" << "\n";
	std::cout << "Defense:       " << static_cast<int>(GetDefense()) << " (Endurance + Agility)" << "\n";
	std::cout << "Carry Capacity " << static_cast<int>(GetCarryCapacity()) << " (Strength + Agility / 3)" << "\n\n";
}

void Player::EnterAttributesMenu() const
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

		AttriMenu AttriMenuChoice = static_cast<AttriMenu>(ReadIntInRange(
			static_cast<int>(AttriMenu::Attributes),
			static_cast<int>(AttriMenu::Return)));

		bool shouldExit = false;
		system("cls");

		switch (AttriMenuChoice)
		{
		case AttriMenu::Attributes:
			{
				PrintAttributes();
				system("pause");
				break;
			}
		case AttriMenu::DerivedAttributes:
			{
				PrintDerivedAttributes();
				system("pause");
				break;
			}
		case AttriMenu::Return:
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
