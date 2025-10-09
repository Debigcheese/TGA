#pragma once
#include "Player.h"

class WorldMap;
class Enemy;

class CombatManager
{
public:
	CombatManager(Player& aPlayer, Room* aCurrentRoom);

	void UpdateCombat();

	void Attack() const;
	void ChooseTarget();
	void ChooseAttack();
	void TakeDamage(const float aDamage);

	float GetDamageFromAttackType(int aAttackIndex) const;
	bool IsInvalidAttackIndex() const;

	//combat
	void SetAttackData(AttackData aAttackData) { myAttackData = aAttackData; }
	AttackData GetAttackData() const { return myAttackData; }

	void PrintHealth() const;
	void PrintUserName() const;
	void PrintPlayerUI() const;
	void PrintAttributes() const;
	void PrintBaseAttributes() const;
	void PrintDerivedAttributes() const;

private:
	//CONSTANTS
	static constexpr float DEFAULT_BASE_ATTRIBUTE = 8.0f;
	Player& myPlayer;
	Room* myCurrentRoom;
	AttackData myAttackData;
};
