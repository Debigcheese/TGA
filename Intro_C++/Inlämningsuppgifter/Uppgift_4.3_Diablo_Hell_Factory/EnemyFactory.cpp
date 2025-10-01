#include "EnemyFactory.h"

EnemyFactory::EnemyFactory()
	: myNextId(0), myTypes{
		  {
			  {EnemyKey::None, EnemyType::None, "None", 0.0f, 0.0f},
			  {EnemyKey::Bat, EnemyType::Bat, "Bat", 5.0f, 40.0f},
			  {EnemyKey::Skeleton, EnemyType::Skeleton, "Skeleton", 10.0f, 100.0f},
			  {EnemyKey::Undead, EnemyType::Undead, "Undead", 12.0f, 130.0f},
			  {EnemyKey::Beast, EnemyType::Beast, "Beast", 16.0f, 200},
			  {EnemyKey::Humanoid, EnemyType::Humanoid, "Humanoid", 17.0f, 250.0f},
			  {EnemyKey::Elemental, EnemyType::Elemental, "Elemental", 25.0f, 300.0f},
			  {EnemyKey::Demon, EnemyType::Demon, "Demon", 40.0f, 1500.0f}
		  }
	  }
{
}

EnemyFactory& EnemyFactory::GetFactory()
{
	static EnemyFactory instance;
	return instance;
}

Enemy EnemyFactory::Create(const EnemyKey aKey)
{
	return Enemy(myTypes[static_cast<int>(aKey)], myNextId++);
}
