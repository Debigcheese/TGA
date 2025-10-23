#include "CombatController.h"
#include "Player.h"
#include "Enemy.h"
#include "Utils.h"

#include <vector>
#include <iostream>

#include "ConsoleUI.h"

CombatController::CombatController(Player& aPlayer) :
	myPlayer(aPlayer),
	myCurrentRoom(nullptr),
	myAttackData()
{
}

void CombatController::UpdateCombat(Room* aCurrentRoom)
{
	myCurrentRoom = aCurrentRoom;
	if (!myCurrentRoom->DoesEnemiesExist())
	{
		std::cout << "No monsters in this room...\n";
		std::cout << "Choose another action.\n";
		ConsoleUI::Pause();
		return;
	}

	while (true && !myPlayer.IsDead())
	{
		ConsoleUI::PrintCombatUI(*this, myPlayer, myCurrentRoom);
		ChooseTarget();

		ConsoleUI::PrintCombatUI(*this, myPlayer, myCurrentRoom);
		ChooseAttack();

		ConsoleUI::PrintCombatUI(*this, myPlayer, myCurrentRoom);
		Attack();

		auto& enemies = myCurrentRoom->GetEnemies();
		auto& targetEnemy = enemies[GetAttackData().targetIndex];

		for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; --i)
		{
			if (enemies[i].IsDead())
			{
				enemies[i].OnDeath(myCurrentRoom);
				myCurrentRoom->RemoveEnemyFromRoom(enemies[i].GetId());
				if (i == 0)
				{
					ConsoleUI::Pause();
				}
			}
		}

		ConsoleUI::Clear();
		ConsoleUI::PrintPlayerUI(myPlayer, myCurrentRoom);

		if (targetEnemy.IsDead())
		{
			SetAttackData({PLAYER_ATTACK_INDEX_INVALID, GetAttackData().attackType});
			myCurrentRoom->PrintEnemies();
		}
		else
		{
			myCurrentRoom->PrintEnemiesWithTarget(GetAttackData().targetIndex);
		}

		if (myCurrentRoom->GetEnemies().empty())
		{
			std::cout << "\nYou have slain all enemies in this room!\n";
			ConsoleUI::Pause();
			break;
		}
		ConsoleUI::PrintCombatUI(*this, myPlayer, myCurrentRoom);
		std::cout << "\n";
		for (const Enemy& enemy : myCurrentRoom->GetEnemies())
		{
			enemy.Attack(myPlayer);
		}
		if (!myPlayer.IsDead())
		{
			ConsoleUI::Pause();
		}
	}
}

void CombatController::Attack() const
{
	std::vector<Enemy>& enemies = myCurrentRoom->GetEnemies();
	int targetIndex = GetAttackData().targetIndex;

	float damage = GetDamageFromAttackType();

	std::vector<float> enemiesOldHp;

	std::vector<int> targetIdx = {};
	if (GetAttackData().attackType == AttackType::SlashAttack)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			targetIdx.push_back(i);
			enemiesOldHp.push_back(enemies[i].GetCurrentHealth());
		}
	}
	else
	{
		targetIdx.push_back(targetIndex);
		enemiesOldHp.push_back(enemies[targetIndex].GetCurrentHealth());
	}

	for (const int idx : targetIdx)
	{
		enemies[idx].TakeDamage(damage);
		std::cout << "\nYou dealt "
			<< std::round(damage)
			<< " dmg to "
			<< enemies[idx].GetEnemyAttributes().name;
		std::cout << " ("
			<< std::round(enemiesOldHp[idx])
			<< "hp -> "
			<< std::round(enemies[idx].GetCurrentHealth())
			<< "hp)"
			<< "";
	}
	std::cout << "\n";

	ConsoleUI::Pause();
}

void CombatController::ChooseTarget()
{
	if (!IsInvalidAttackIndex() || myCurrentRoom->GetEnemies().size() <= PLAYER_ATTACK_INDEX_INVALID)
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

void CombatController::ChooseAttack()
{
	while (true)
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
			static_cast<int>(AttackType::AttackInfo));
		SetAttackData({GetAttackData().targetIndex, static_cast<AttackType>(attackIndex)});

		auto type = static_cast<AttackType>(attackIndex);

		if (type == AttackType::AttackInfo)
		{
			ConsoleUI::PrintCombatUI(*this, myPlayer, myCurrentRoom);
			ConsoleUI::PrintAttackTypeInfo(*this, myPlayer);
		}
		else
		{
			break;
		}
	}
}

float CombatController::GetDamageFromAttackType() const
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

const AmountRange& CombatController::GetHeavyDamageRange() const
{
	AmountRange heavyDamageRange;
	heavyDamageRange.min = static_cast<int>(
		std::round(myPlayer.GetAttributes().damage * HEAVY_MULTI_MIN));
	heavyDamageRange.max = static_cast<int>(
		std::round(myPlayer.GetAttributes().damage * HEAVY_MULTI_MAX));

	return heavyDamageRange;
}

float CombatController::GetDefenseMultiplier() const
{
	return (DEFENSE_BASE_MULTI + (myPlayer.GetAttributes().defense / DEFENSE_SCALING_FACTOR));
	// (defense {20-198} /200) 
}

bool CombatController::IsInvalidAttackIndex() const
{
	return GetAttackData().targetIndex < PLAYER_ATTACK_INDEX_ZERO;
}
