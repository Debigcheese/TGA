#pragma once

#include "GameStructs.h"
#include "GameEnums.h"
#include "Door.h"

class Player
{
public:
	Player();
	void Update();
	//int OpenDoorWithID(int aDoorId);
	//void OpenDoor(Door door);
	int GetRoomId() const;
	void SetRoomId(const int& aNewRoomId);

	float GetDamage() const;
	float GetMaxHealth() const;
	float GetCurrentHealth() const;
	float GetCarryCapacity() const;
	float GetDefense() const;

private:
	PlayerAttributes myAttributes;
	int myRoomId;

};

