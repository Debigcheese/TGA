#pragma once
#include "Player.h"

class Enemy;

class CombatManager
{
public:
	CombatManager(Player& aPlayer);
	void UpdateCombat(Room* aCurrentRoom);

	void Attack() const;
	void ChooseTarget();
	void ChooseAttack();

	float GetDamageFromAttackType() const;
	const AmountRange& GetHeavyDamageRange() const;
	float GetSlashDamage() const { return myPlayer.GetAttributes().damage / 2.5f; }
	bool IsInvalidAttackIndex() const;
	float GetDefenseMultiplier() const;

	void SetAttackData(AttackData aAttackData) { myAttackData = aAttackData; }
	const AttackData& GetAttackData() const { return myAttackData; }

	void PrintCombatUI() const;

private:
	//CONSTANTS
	static constexpr float DEFAULT_BASE_ATTRIBUTE = 8.0f;
	Player& myPlayer;
	Room* myCurrentRoom;
	AttackData myAttackData;
};
