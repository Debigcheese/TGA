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
                                      myName("(-)"), myPos{0, 0}
{
	myAttributes.strength = DEFAULT_BASE_ATTRIBUTE;
	myAttributes.agility = DEFAULT_BASE_ATTRIBUTE;
	myAttributes.endurance = DEFAULT_BASE_ATTRIBUTE;

	myAttributes.currentHealth = GetMaxHealth();
}

void Player::Attack() const
{
	Room* currentRoom = myWorldMap.GetRoomWithId(GetRoomId());
	std::vector<Enemy>& enemies = currentRoom->GetEnemies();

	PrintPlayerUI();
	currentRoom->PrintEnemiesWithTarget(myTargetIndex);

	float damage = GetDamageFromAttackType(myAttackIndex);
	float enemyOldHp = enemies[myTargetIndex].GetCurrentHealth();
	enemies[myTargetIndex].TakeDamage(damage);
	std::cout << "\nYou dealt " << std::lround(damage) << " dmg to "
		<< enemies[myTargetIndex].GetEnemyAttributes().name;
	std::cout << " (" << std::lround(enemyOldHp) << "hp -> " << std::lround(enemies[myTargetIndex].
		GetCurrentHealth()) << "hp)" << "\n";
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

	for (int i = 0; i < static_cast<int>(mySpells.size()); i++)
	{
		mySpells[i].UpdateOnHitCount();
		if (mySpells[i].GetSpellFinished())
		{
			RemoveSpell(i);
		}
	}
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
			const int heavyMinMulti = static_cast<int>(std::round(GetAttributes().damage * HEAVY_MULTI_MIN));
			const int heavyMaxMulti = static_cast<int>(std::round(GetAttributes().damage * HEAVY_MULTI_MAX));
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

bool Player::IsInvalidAttackIndex() const
{
	return myAttackIndex < PLAYER_ATTACK_INDEX_ZERO;
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

const Attributes& Player::GetBuffedAttributes() const
{
	Attributes buffedAttributes = {};
	buffedAttributes += GetEquipment().GetAttributes();
	for (const auto& spell : mySpells)
	{
		//buffedAttributes += spell.GetAttributes();
	}
	return buffedAttributes;
}

Attributes Player::GetAttributes() const
{
	return {

		GetBaseAttributes().strength + GetBuffedAttributes().strength,
		GetBaseAttributes().agility + GetBuffedAttributes().agility,
		GetBaseAttributes().endurance + GetBuffedAttributes().endurance,
		GetBaseAttributes().maxHealth + GetBuffedAttributes().maxHealth,
		GetBaseAttributes().currentHealth + GetBuffedAttributes().currentHealth,
		GetBaseAttributes().carryCapacity + GetBuffedAttributes().carryCapacity,
		GetBaseAttributes().damage + GetBuffedAttributes().damage,
		GetBaseAttributes().defense + GetBuffedAttributes().defense
	};
}

bool Player::CanPickupItem(const Item& aItem) const
{
	if (GetAttributes().carryCapacity >= myInventory.GetInventoryWeight() + aItem.GetItemAttributes().weight)
	{
		return true;
	}
	return false;
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

//prints attributes after items + buffs
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
	std::cout << "Defense:       " << static_cast<int>(GetAttributes().defense) << " def" << "\n";
	std::cout << "Carry Capacity: " << static_cast<int>(GetAttributes().carryCapacity) << "kg" << "\n\n";
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
	std::cout << "Defense:       " << static_cast<int>(GetDefense()) << " def" << "\n";
	std::cout << "Carry Capacity: " << static_cast<int>(GetCarryCapacity()) << "kg" << "\n\n";
}

//prints base attributes + derived calculation
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
	std::cout << "Defense:       " << static_cast<int>(GetDefense()) << " def" << " (Endurance + Agility)" << "\n";
	std::cout << "Carry Capacity: " << static_cast<int>(GetCarryCapacity()) << "kg " << " (Strength + Agility / 3)" <<
		"\n\n";
}

void Player::PrintSpells() const
{
	std::cout << "\n<--- Active Spells --->\n";
	if (mySpells.empty())
	{
		std::cout << "Empty...\n";
	}

	for (const auto& spell : mySpells)
	{
		spell.PrintSpellOnDisplay();
		std::cout << " \n";
	}

	std::cout << mySpells.size() + 1 << ") Return\n"
		<< "Choice: ";
}
