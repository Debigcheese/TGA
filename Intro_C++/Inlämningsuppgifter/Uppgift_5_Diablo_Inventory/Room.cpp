#include "Room.h"

Room::Room(const RoomMeta& aRoomMeta, const RoomObjects& aRoomObjects) :
    myRoomId(aRoomMeta.ID),
    myRoomName(aRoomMeta.roomName),
    myPos{aRoomMeta.pos.X, aRoomMeta.pos.Y},
    myEnemies(aRoomObjects.enemies),
    myItems(aRoomObjects.items),
    myChests(aRoomObjects.chests),
    mySpells(aRoomObjects.spells)
{
}


int Room::GetRoomId() const
{
    return myRoomId;
}

void Room::SetRoomId(int aRoomId)
{
    myRoomId = aRoomId;
}

std::string Room::GetRoomName() const
{
    return myRoomName;
}

Position Room::GetPosition() const
{
    return myPos;
}

const std::vector<Enemy>& Room::GetEnemies() const
{
    return myEnemies;
}

std::vector<Enemy>& Room::GetEnemies()
{
    return myEnemies;
}

void Room::AddEnemyToRoom(const Enemy& aEnemyToAdd)
{
    myEnemies.push_back(aEnemyToAdd);
}

void Room::RemoveEnemyFromRoom(int aEnemyID)
{
    std::erase_if(myEnemies, [aEnemyID](const Enemy& enemy)
    {
        return enemy.GetId() == aEnemyID;
    });
}

bool Room::DoesEnemiesExist() const
{
    return !myEnemies.empty();
}

void Room::AddItemToRoom(const Item& aItemToAdd)
{
    myItems.push_back(aItemToAdd);
}

const std::vector<Item>& Room::GetLootInRoom() const
{
    return myItems;
}

std::vector<Item>& Room::GetLootInRoom()
{
    return myItems;
}

void Room::AddChestToRoom(const Chest& aChestToAdd)
{
    myChests.push_back(aChestToAdd);
}

std::vector<Chest>& Room::GetChestInRoom()
{
    return myChests;
}

void Room::AddSpellToRoom(const Spell& aSpellToAdd)
{
    mySpells.push_back(aSpellToAdd);
}

const std::vector<Spell>& Room::GetSpellsInRoom() const
{
    return mySpells;
}

std::vector<Spell>& Room::GetSpellsInRoom()
{
    return mySpells;
}
