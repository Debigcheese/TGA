#pragma once
#include "GameStructs.h"
#include "GameEnums.h"

class Player;

class Enemy
{
public:
	Enemy();
	Enemy(float aMaxHealth, float aDamage, EnemyType aType);
	void TakeDamage(const float aDamage);
	void Attack(Player& player) const;

	float GetMaxHealth() const;
	float GetDamage() const;
	float GetCurrentHealth() const;
	bool IsDead() const;
	void SetId(int aId);
	int GetId() const;
	EnemyType GetType()const;

private:
	int myId;
	EnemyAttributes myAttributes;
	EnemyType myType;
	float myCurrentHealth;
	bool myIsDead;
};

