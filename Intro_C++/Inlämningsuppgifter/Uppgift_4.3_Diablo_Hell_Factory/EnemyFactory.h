#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include "Enemy.h"
#include "Utils.h"

#include <vector>

class EnemyFactory
{
public:
	static EnemyFactory& GetFactory();
	EnemyFactory();
	Enemy Create(const EnemyKey aKey);

private:
	int myNextId;
	std::vector<EnemyAttributes> myTypes;
};
