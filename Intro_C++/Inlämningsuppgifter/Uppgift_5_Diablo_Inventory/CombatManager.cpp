#include "CombatManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Utils.h"

#include <vector>
#include <iostream>

CombatManager::CombatManager(Player& aPlayer) :
	myPlayer(aPlayer),
	myCurrentRoom(nullptr),
	myAttackData()
{
}

void CombatManager::UpdateCombat(Room* aCurrentRoom)
{
	myCurrentRoom = aCurrentRoom;
	if (!myCurrentRoom->DoesEnemiesExist())
	{
		std::cout << "No monsters in this room...\n";
		std::cout << "Choose another action.\n";
		system("pause");
		return;
	}

	while (true && !myPlayer.IsDead())
	{
		PrintCombatUI();
		ChooseTarget();

		PrintCombatUI();
		ChooseAttack();

		PrintCombatUI();
		Attack();

		std::vector<Enemy>& enemies = myCurrentRoom->GetEnemies();
		auto& targetEnemy = enemies[GetAttackData().targetIndex];
		if (targetEnemy.IsDead())
		{
			targetEnemy.OnDeath(myCurrentRoom);
			myCurrentRoom->RemoveEnemyFromRoom(targetEnemy.GetId());
			enemies = myCurrentRoom->GetEnemies();
			SetAttackData({PLAYER_ATTACK_INDEX_INVALID, GetAttackData().attackType});
			system("pause");
		}

		system("cls");
		myPlayer.PrintPlayerUI();

		if (targetEnemy.IsDead())
		{
			myCurrentRoom->PrintEnemies();
		}
		else
		{
			myCurrentRoom->PrintEnemiesWithTarget(GetAttackData().targetIndex);
		}

		if (enemies.empty())
		{
			std::cout << "\nYou have slain all enemies in this room!\n";
			system("pause");
			break;
		}
		PrintCombatUI();
		std::cout << "\n";
		for (const Enemy& enemy : enemies)
		{
			enemy.Attack(myPlayer);
		}
		if (!myPlayer.IsDead())
		{
			system("pause");
		}
	}
}

void CombatManager::Attack() const
{
	std::vector<Enemy>& enemies = myCurrentRoom->GetEnemies();
	int targetIndex = GetAttackData().targetIndex;

	float damage = GetDamageFromAttackType();
	float enemyOldHp = enemies[targetIndex].GetCurrentHealth();

	std::vector<int> targetIdx = {};
	if (GetAttackData().attackType == AttackType::SlashAttack)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			targetIdx.push_back(i);
		}
	}
	else
	{
		targetIdx.push_back(targetIndex);
	}

	for (const int idx : targetIdx)
	{
		enemies[idx].TakeDamage(damage);
		std::cout << "\nYou dealt "
			<< std::round_to_nearest(damage)
			<< " dmg to "
			<< enemies[idx].GetEnemyAttributes().name;
		std::cout << " ("
			<< std::round_to_nearest(enemyOldHp)
			<< "hp -> "
			<< std::round_to_nearest(enemies[idx].GetCurrentHealth())
			<< "hp)"
			<< "\n";
	}

	system("pause");
}

void CombatManager::ChooseTarget()
{
	if (!IsInvalidAttackIndex() || myCurrentRoom->GetEnemies().size() <= 1)
	{
		SetAttackData({PLAYER_ATTACK_INDEX_ZERO, GetAttackData().attackType});
		return;
	}

	std::cout
		<< "\n<--- Choose Target --->\n"
		<< "Choice: ";
	int enemyCount = static_cast<int>(myCurrentRoom->GetEnemies().size());
	int targetIndex = Utils::ReadIntInRange(
			PLAYER_TARGET_ENEMY_MIN,
			enemyCount) -
		PLAYER_TARGET_INDEX_OFFSET;
	SetAttackData({targetIndex, GetAttackData().attackType});
}

void CombatManager::ChooseAttack()
{
	std::cout
		<< "\n<--- Choose Attack --->\n"
		<< "1) Quick attack [" << myPlayer.GetAttributes().damage << "] AD" << "\n"
		<< "2) Heavy attack [" << GetHeavyDamageRange().min << " - " << GetHeavyDamageRange().max << "] AD" << "\n"
		<< "3) Slash attack [" << static_cast<int>(GetSlashDamage()) << "] AD" << "\n"
		<< "4) Attack Info\n"
		<< "Choice: ";
	int attackIndex = Utils::ReadIntInRange(
		static_cast<int>(AttackType::QuickAttack),
		static_cast<int>(AttackType::SlashAttack));
	SetAttackData({GetAttackData().targetIndex, static_cast<AttackType>(attackIndex)});
}

float CombatManager::GetDamageFromAttackType() const
{
	float newDamage = DAMAGE_ZERO;
	AttackType atkType = GetAttackData().attackType;
	switch (atkType)
	{
		case AttackType::QuickAttack:
		{
			newDamage = myPlayer.GetAttributes().damage;
			break;
		}
		case AttackType::HeavyAttack:
		{
			newDamage = static_cast<float>(Utils::GenerateRandomNumber(
				GetHeavyDamageRange().min, GetHeavyDamageRange().max));
			break;
		}
		case AttackType::SlashAttack:
		{
			newDamage = GetSlashDamage();
			break;
		}
		default:
		{
			break;
		}
	}
	return newDamage;
}

const AmountRange& CombatManager::GetHeavyDamageRange() const
{
	AmountRange heavyDamageRange;
	heavyDamageRange.min = static_cast<int>(
		std::round(myPlayer.GetAttributes().damage * HEAVY_MULTI_MIN));
	heavyDamageRange.max = static_cast<int>(
		std::round(myPlayer.GetAttributes().damage * HEAVY_MULTI_MAX));

	return heavyDamageRange;
}

float CombatManager::GetDefenseMultiplier() const
{
	return (DEFENSE_BASE_MULTI + (myPlayer.GetAttributes().defense / DEFENSE_SCALING_FACTOR));
	// (defense {20-198} /200) 
}

bool CombatManager::IsInvalidAttackIndex() const
{
	return GetAttackData().targetIndex < PLAYER_ATTACK_INDEX_ZERO;
}

void CombatManager::PrintCombatUI() const
{
	system("cls");
	myPlayer.PrintPlayerUI();
	const std::vector<Enemy>& enemies = myCurrentRoom->GetEnemies();
	if (IsInvalidAttackIndex())
	{
		myCurrentRoom->PrintEnemies();
		return;
	}
	const auto& targetEnemy = enemies[GetAttackData().targetIndex];
	if (targetEnemy.IsDead())
	{
		return;
	}
	myCurrentRoom->PrintEnemiesWithTarget(GetAttackData().targetIndex);
}
