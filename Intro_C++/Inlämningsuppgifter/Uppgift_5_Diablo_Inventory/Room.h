#pragma once
#include "Enemy.h"
#include "GameStructs.h"
#include "Item.h"
#include "Chest.h"
#include "Spell.h"

#include <string>
#include <vector>

class Room
{
public:
    struct RoomMeta
    {
        int ID;
        std::string roomName;
        Position pos;
    };

    struct RoomObjects
    {
        std::vector<Enemy> enemies;
        std::vector<Item> items;
        std::vector<Chest> chests;
        std::vector<Spell> spells;
    };

    Room(const RoomMeta& aRoomMeta, const RoomObjects& aRoomObjects);
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
    std::vector<Item>& GetLootInRoom();

    void AddChestToRoom(const Chest& aChestToAdd);
    std::vector<Chest>& GetChestInRoom();

    //spells
    void AddSpellToRoom(const Spell& aSpellToAdd);
    const std::vector<Spell>& GetSpellsInRoom() const;
    std::vector<Spell>& GetSpellsInRoom();

    void PrintRoomName() const;
    void PrintEnemies() const;
    void PrintEnemiesWithTarget(const int& aTargetIndex) const;

private:
    int myRoomId;
    std::string myRoomName;
    Position myPos;
    std::vector<Enemy> myEnemies;
    std::vector<Item> myItems;
    std::vector<Chest> myChests;
    std::vector<Spell> mySpells;
};
