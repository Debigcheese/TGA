#include "Room.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;


Room::Room(int aRoomId, std::string aRoomName, Position aPosition, std::vector<Enemy> aEnemies) :
	myRoomId(aRoomId), myRoomName(aRoomName), myPos{aPosition.X, aPosition.Y}, myEnemies(aEnemies), myChests(),
	mySpells()
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
	myEnemies.erase(std::remove_if(myEnemies.begin(), myEnemies.end(), [aEnemyID](const Enemy& enemy)
	                {
		                return enemy.GetId() == aEnemyID;
	                }),
	                myEnemies.end());
}

bool Room::DoesEnemiesExist() const
{
	return !myEnemies.empty();
}

void Room::AddItemToRoom(const Item& aItemToAdd)
{
	myLoot.push_back(aItemToAdd);
}

const std::vector<Item>& Room::GetLootInRoom() const
{
	return myLoot;
}

std::vector<Item>& Room::GetLootInRoom()
{
	return myLoot;
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

void Room::PrintRoomName() const
{
	std::cout << "Room: " << myRoomName;
}

void Room::PrintEnemies() const
{
	if (static_cast<int>(myEnemies.size()) <= ARRAY_COUNT_ZERO)
	{
		std::cout << "\n[No monsters in room]\n";
		return;
	}
	std::cout << "\n[Monsters in room]\n";
	for (int i = 0; i < static_cast<int>(myEnemies.size()); i++)
	{
		std::cout << "[" << i + ARRAY_INDEX_OFFSET << "]" << " - "
			<< myEnemies[i].GetName() << ": "
			<< static_cast<int>(myEnemies[i].GetCurrentHealth()) << "/"
			<< static_cast<int>(myEnemies[i].GetMaxHealth()) << " hp | "
			<< static_cast<int>(myEnemies[i].GetDamage()) << " AD" << "\n";
	}
}

void Room::PrintEnemiesWithTarget(const int& aTargetIndex) const
{
	if (static_cast<int>(myEnemies.size()) <= ARRAY_COUNT_ZERO)
	{
		std::cout << "\n[No monsters in room]\n";
		return;
	}

	const char* RED = "\x1b[31m";
	const char* RESET = "\x1b[0m";
	std::cout << "\n[Monsters in room]\n";
	for (int i = 0; i < static_cast<int>(myEnemies.size()); i++)
	{
		if (aTargetIndex == i)
		{
			RED = "\x1b[31m";
			RESET = "\x1b[0m";
		}
		else
		{
			RED = "";
			RESET = "";
		}
		std::cout << RED
			<< "[" << i + ARRAY_INDEX_OFFSET << "]" << " - "
			<< myEnemies[i].GetName() << ": "
			<< static_cast<int>(myEnemies[i].GetCurrentHealth()) << "/"
			<< static_cast<int>(myEnemies[i].GetMaxHealth()) << " hp | "
			<< static_cast<int>(myEnemies[i].GetDamage()) << " AD"
			<< RESET << "\n";
	}
}
