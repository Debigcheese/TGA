#include "EnemyFactory.h"
#include "Utils.h"
#include "EnemyType.h"

EnemyFactory::EnemyFactory()
	: myTypes({})
{
	InitFactory();
}

EnemyFactory& EnemyFactory::GetFactory()
{
	static EnemyFactory instance;
	return instance;
}

Enemy EnemyFactory::Create(EnemyKey aKey)
{
	if (aKey <= EnemyKey::None || aKey >= EnemyKey::Count || static_cast<int>(aKey) >= static_cast<int>(myTypes.size()))
	{
		aKey = static_cast<EnemyKey>(Utils::GenerateRandomNumber
			(static_cast<int>(EnemyKey::None) + 1,
			 static_cast<int>(myTypes.size()) - 1));
	}
	EnemyType& type = myTypes[static_cast<int>(aKey)];
	return {(&type), myNextId++}; // returns Item address with pointer to type
}

void EnemyFactory::InitFactory()
{
	myTypes.resize(static_cast<int>(EnemyKey::Count));

	myTypes[static_cast<int>(EnemyKey::None)].SetAttributes(
		{EnemyKey::None, "None", 0.0f, 0.0f}
	);

	myTypes[static_cast<int>(EnemyKey::Bat)].SetAttributes(
		{EnemyKey::Bat, "Bat", 5.0f, 40.0f}
	);

	myTypes[static_cast<int>(EnemyKey::Skeleton)].SetAttributes(
		{EnemyKey::Skeleton, "Skeleton", 10.0f, 100.0f}
	);

	myTypes[static_cast<int>(EnemyKey::Undead)].SetAttributes(
		{EnemyKey::Undead, "Undead", 12.0f, 130.0f}
	);

	myTypes[static_cast<int>(EnemyKey::Beast)].SetAttributes(
		{EnemyKey::Beast, "Beast", 16.0f, 200.0f}
	);

	myTypes[static_cast<int>(EnemyKey::Humanoid)].SetAttributes(
		{EnemyKey::Humanoid, "Humanoid", 17.0f, 250.0f}
	);

	myTypes[static_cast<int>(EnemyKey::Elemental)].SetAttributes(
		{EnemyKey::Elemental, "Elemental", 25.0f, 300.0f}
	);

	myTypes[static_cast<int>(EnemyKey::Demon)].SetAttributes(
		{EnemyKey::Demon, "Demon", 40.0f, 1000.0f}
	);
}
