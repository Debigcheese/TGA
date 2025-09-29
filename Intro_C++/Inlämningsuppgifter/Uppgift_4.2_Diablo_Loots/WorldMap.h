#pragma once
#include "Room.h"
#include "Door.h"
#include "Enemy.h"
#include "Item.h"
#include "Chest.h"
#include "Spell.h"

class WorldMap
{
public:
	WorldMap();
	WorldMap(std::vector<Room> aRooms);

	std::vector<Door>& GetDoors();
	std::vector<Room>& GetRooms();
	Room* GetRoomWithId(int aRoomId);
	Room* GetRoomWithId(int aRoomId) const;

	void AddRoom(const Room& aRoomToAdd);

	void GenerateWorld();
	Enemy GenerateEnemy(const EnemyType& aEnemyType);
	void GiveEnemyUniqueId(Enemy& aEnemy);
	void GenerateDoors();
	void GenerateRooms();

	//items
	void GenerateItems();
	void AddItemsToRoomId(int aRoomId, const std::vector<Item>& aItemsToRoom);
	std::vector<Item> GetItemsUpToRarity(int aMinAmount, int aMaxAmount, const Rarity aRarity) const;
	//std::vector<Item> GenerateItemsWithRarity(const std::vector<Rarity>& aItemRarities) const;

	//chests
	void GenerateChests();
	void CreateChests(int aRoomId, int aAmount, Rarity aRarity);
	void AddChestsToRoomId(int aRoomId, const std::vector<Chest>& aChestsToRoom);

	void GenerateSpells();
	void AddSpellsToRoomId(int aRoomId, const std::vector<Spell>& aSpellsToRoom);
	std::vector<Spell> GetSpellsUpToRarity(int aMinAmount, int aMaxAmount, const Rarity aRarity) const;

private:
	int myNextEnemyId;
	std::vector<Room> myRooms;
	std::vector<Door> myDoors;
};
