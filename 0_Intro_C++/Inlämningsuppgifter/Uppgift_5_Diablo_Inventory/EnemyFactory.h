#pragma once
#include "GameEnums.h"
#include "Enemy.h"

#include <vector>

class EnemyFactory
{
public:
	static EnemyFactory& GetFactory();
	EnemyFactory();
	Enemy Create(EnemyKey aKey);
	void InitFactory();

private:
	int myNextId;
	std::vector<EnemyType> myTypes;
};
