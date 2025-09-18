#pragma once
#include "Door.h"
#include "Enemy.h"
#include <string>
#include <vector>

class Room
{
public:
	Room(int aRoomId, std::string aRoomName, std::vector<int> aDoorIds, std::vector<Enemy> aEnemies);
	int GetRoomId() const;
	void SetRoomId(int aRoomId);
	std::string GetRoomName() const;
	std::vector<Enemy> GetEnemies() const;
	void AddEnemyToRoom(const Enemy& aEnemyToAdd);
	std::vector<int> GetDoorIds();

private:
	int myRoomId;
	std::string myRoomName;
	std::vector<int> myDoorIds;
	std::vector<Enemy> myEnemies;
};

