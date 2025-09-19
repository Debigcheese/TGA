#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include "Door.h"
#include "WorldMap.h"

class Player
{
public:
	Player(WorldMap aWorldMap);
	void Update();

	int GetRoomId() const;
	void SetRoomId(const int& aNewRoomId);

	float GetDamage() const;
	float GetMaxHealth() const;
	float GetCurrentHealth() const;
	float GetCarryCapacity() const;
	float GetDefense() const;

	void PrintAttributes() const;

private:
	WorldMap myWorldMap;
	PlayerAttributes myAttributes;
	int myRoomId;

};

