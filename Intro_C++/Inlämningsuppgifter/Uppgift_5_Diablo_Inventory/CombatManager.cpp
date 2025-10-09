#include "CombatManager.h"
#include "Player.h"
#include "Enemy.h"

#include "Utils.h"
#include "Cheats.h"

#include <vector>
#include <iostream>

CombatManager::CombatManager(Player& aPlayer, Room* aCurrentRoom) :
	myPlayer(aPlayer),
	myCurrentRoom(aCurrentRoom),
	myAttackData()
{
}

void CombatManager::UpdateCombat()
{
	if (!myWorldMap.GetRoomWithId(myPlayer.GetRoomId())->DoesEnemiesExist())
	{
		std::cout << "No monsters in this room...\n";
		std::cout << "Choose another action.\n";
		system("pause");
		return;
	}

	while (true && !myPlayer.IsDead())
	{
		std::vector<Enemy>& enemies = currentRoom->GetEnemies();

		if (myPlayer.IsInvalidAttackIndex() || enemies.size() > 1)
		{
			PrintUI();
			myPlayer.ChooseTarget();
			system("cls");
		}
		else
		{
			myPlayer.SetTargetIndex(PLAYER_ATTACK_INDEX_ZERO);
		}

		auto& targetEnemy = enemies[myPlayer.GetTargetIndex()];

		myPlayer.PrintPlayerUI();
		currentRoom->PrintEnemiesWithTarget(myPlayer.GetTargetIndex());
		myPlayer.ChooseAttack();
		system("cls");

		myPlayer.Attack();

		system("pause");

		if (targetEnemy.IsDead())
		{
			std::cout << "\n" << targetEnemy.GetEnemyAttributes().name << " has been slained!\n";
			if (targetEnemy.HasItems())
			{
				std::cout << targetEnemy.GetEnemyAttributes().name << " dropped an item!\n";
			}
			targetEnemy.DropItem(currentRoom);
			system("pause");
		}

		system("cls");
		myPlayer.PrintPlayerUI();

		if (targetEnemy.IsDead())
		{
			currentRoom->RemoveEnemyFromRoom(targetEnemy.GetId());
			enemies = currentRoom->GetEnemies();
			myPlayer.SetTargetIndex(PLAYER_ATTACK_INDEX_INVALID);
			currentRoom->PrintEnemies();
		}
		else
		{
			currentRoom->PrintEnemiesWithTarget(myPlayer.GetTargetIndex());
		}

		if (enemies.empty())
		{
			std::cout << "\nYou have slain all enemies in this room!\n";
			system("pause");
			break;
		}

		std::cout << "\n";
		for (Enemy& enemy : enemies)
		{
			enemy.Attack(myPlayer);
		}
		if (!myPlayer.IsDead())
		{
			system("pause");
		}
	}
}

void Player::Attack() const
{
	Room* currentRoom = myWorldMap.GetRoomWithId(GetRoomId());
	std::vector<Enemy>& enemies = currentRoom->GetEnemies();

	const AttackData& attackData = GetAttackData();

	PrintPlayerUI();
	currentRoom->PrintEnemiesWithTarget(attackData.targetIndex);

	float damage = GetDamageFromAttackType(static_cast<int>(attackData.attackType));
	float enemyOldHp = enemies[attackData.targetIndex].GetCurrentHealth();
	enemies[attackData.targetIndex].TakeDamage(damage);
	std::cout << "\nYou dealt " << std::lround(damage) << " dmg to "
		<< enemies[attackData.targetIndex].GetEnemyAttributes().name;
	std::cout << " (" << std::lround(enemyOldHp) << "hp -> " << std::lround(enemies[attackData.targetIndex].
		GetCurrentHealth()) << "hp)" << "\n";
}

void Player::ChooseTarget()
{
	std::cout
		<< "\n<--- Choose Target --->\n"
		<< "Choice: ";
	int enemyCount = static_cast<int>(myWorldMap.GetRoomWithId(myRoomId)->GetEnemies().size());
	int targetIndex = Utils::ReadIntInRange(PLAYER_TARGET_ENEMY_MIN, enemyCount) -
		PLAYER_TARGET_INDEX_OFFSET;
	SetAttackData({targetIndex, GetAttackData().attackType});
}

void Player::ChooseAttack()
{
	std::cout
		<< "\n<--- Choose Attack --->\n"
		<< "1) Quick attack" << "\n"
		<< "2) Heavy attack\n"
		<< "3) Slash attack\n"
		<< "Choice: ";
	int attackIndex = Utils::ReadIntInRange(
		static_cast<int>(AttackType::QuickAttack),
		static_cast<int>(AttackType::HeavyAttack)) - PLAYER_ATTACK_INDEX_OFFSET;
	SetAttackData({GetAttackData().targetIndex, static_cast<AttackType>(attackIndex)});
}

void Player::TakeDamage(const float aDamage)
{
	if (Cheats::GetCheats().invincible)
	{
		return;
	}
	const float dmgFloat = aDamage / GetDefenseMultiplier();
	myAttributes.currentHealth -= dmgFloat;

	mySpellBook.UpdateSpellsOnHitCount();

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
				newDamage = static_cast<float>(Utils::GenerateRandomNumber(heavyMinMulti, heavyMaxMulti));
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
