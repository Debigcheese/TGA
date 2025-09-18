#pragma once

#include "GameStructs.h"
#include "GameEnums.h"
#include "Door.h"

class Player
{
public:
	Player();
	void Update();
	void EnterRoom(int aRoomId);
	int OpenDoorWithID(int aDoorId);
	void OpenDoor(Door door);

	float GetDamage() const;
	float GetMaxHealth() const;
	float GetCurrentHealth() const;
	float GetCarryCapacity() const;
	float GetDefense() const;

private:
	PlayerAttributes myAttributes;
	int myRoomId;

};

