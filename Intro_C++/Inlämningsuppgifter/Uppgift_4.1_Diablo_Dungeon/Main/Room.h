#pragma once
#include "Door.h"
#include "Enemy.h"
#include <string>
#include <vector>

class Room
{
public:
	Room(int aRoomId, std::string aRoomName, std::vector<Door> aDoors, std::vector<Enemy> aEnemies);
	int GetRoomId() const;
	void SetRoomId(int aRoomId);
	std::string GetRoomName() const;
	std::vector<Enemy> GetEnemies() const;
	void AddEnemyToRoom(const Enemy& aEnemyToAdd);
	std::vector<Door> GetDoors();

private:
	int myRoomId;
	std::string myRoomName;
	std::vector<Door> myDoors;
	std::vector<Enemy> myEnemies;
};

