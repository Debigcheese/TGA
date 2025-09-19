#pragma once
#include "Door.h"
#include "Enemy.h"
#include "GameStructs.h"
#include <string>
#include <vector>

class Door;

class Room
{
public:
	Room();
	Room(int aRoomId, std::string aRoomName, std::vector<Enemy> aEnemies);

	int GetRoomId() const;
	void SetRoomId(int aRoomId);
	std::string GetRoomName() const;

	const std::vector<Enemy>& GetEnemies() const;
	std::vector<Enemy>& GetEnemies();

	void AddEnemyToRoom(const Enemy& aEnemyToAdd);

	void AddDoor(const Door& door);
	const std::vector<Door>& GetDoorsConnected() const;
	std::vector<Door>& GetDoorsConnected();

private:
	int myRoomId;
	std::string myRoomName;
	std::vector<Door> myDoors;
	std::vector<Enemy> myEnemies;
};

