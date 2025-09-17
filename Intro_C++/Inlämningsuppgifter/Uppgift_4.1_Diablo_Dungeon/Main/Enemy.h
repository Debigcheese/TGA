#pragma once
class Enemy
{
public:
	Enemy(float aMaxHealth, float aDamage);
	float GetMaxHealth() const;
	float GetDamage() const;
	float GetCurrentHealth() const;
	void TakeDamage(const float aDamage);
	bool IsDead() const;

private:
	float myMaxHealth;
	float myCurrentHealth;
	float myDamage;
	bool myIsDead;
};

