#pragma once
#include "Enemy.h"
#include "GameStructs.h"
#include <string>
#include <vector>

class Item;

class Room
{
public:
	Room();
	Room(int aRoomId, std::string aRoomName, Position aPosition, std::vector<Enemy> aEnemies);

	int GetRoomId() const;
	void SetRoomId(int aRoomId);
	std::string GetRoomName() const;
	Position GetPosition() const;

	//enemies
	const std::vector<Enemy>& GetEnemies() const;
	std::vector<Enemy>& GetEnemies();
	void AddEnemyToRoom(const Enemy& aEnemyToAdd);
	void RemoveEnemyFromRoom(int aEnemyID);
	bool DoesEnemiesExist() const;

	//items
	void AddItemToRoom(const Item& aItemToAdd);
	const std::vector<Item>& GetLootInRoom() const;

	void PrintRoomName() const;
	void PrintEnemies() const;
	void PrintEnemiesWithTarget(const int& aTargetIndex) const;

private:
	int myRoomId;
	std::string myRoomName;
	Position myPos;
	std::vector<Enemy> myEnemies;
	std::vector<Item> myLoot;
};
