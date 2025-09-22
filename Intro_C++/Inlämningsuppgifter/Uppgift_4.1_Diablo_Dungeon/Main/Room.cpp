#include "Room.h"
#include "iostream"
#include "Utils.h"

using namespace Utils;

Room::Room()
{
}

Room::Room(int aRoomId, std::string aRoomName, std::vector<Enemy> aEnemies) :
	myRoomId(aRoomId), myRoomName(aRoomName), myDoors(), myEnemies(aEnemies)
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
	for (int i = 0; i < myEnemies.size(); i++)
	{
		if (myEnemies[i].GetId() == aEnemyID)
		{
			myEnemies.erase(myEnemies.begin() + i);
			break;
		}
	}
}

bool Room::DoesEnemiesExist() const
{
	return !myEnemies.empty();
}

void Room::AddDoor(const Door& door)
{
	myDoors.push_back(door);
}

const std::vector<Door>& Room::GetDoorsConnected() const
{
	return myDoors;
}

std::vector<Door>& Room::GetDoorsConnected()
{
	return myDoors;
}

void Room::PrintRoomName() const
{
	std::cout << "Room: " << myRoomName;
}

void Room::PrintEnemies() const
{
	if (myEnemies.size() <= 0)
	{
		std::cout << "\n[No monsters in room]\n";
		return;
	}
	std::cout << "\n[Monsters in room]\n";
	for (int i = 0; i < myEnemies.size(); i++)
	{
		std::cout << "[" << i + 1 << "]" << " - "
			<< EnemyTypeToString(myEnemies[i].GetType()) << ": "
			<< static_cast<int>(myEnemies[i].GetCurrentHealth()) << "/"
			<< static_cast<int>(myEnemies[i].GetMaxHealth()) << " hp | "
			<< static_cast<int>(myEnemies[i].GetDamage()) << " AD" << "\n";
	}
}

void Room::PrintEnemiesWithTarget(const int& aTargetIndex) const
{
	if (myEnemies.size() <= 0)
	{
		std::cout << "\n[No monsters in room]\n";
		return;
	}

	const char* RED = "\x1b[31m";
	const char* RESET = "\x1b[0m";
	std::cout << "\n[Monsters in room]\n";
	for (int i = 0; i < myEnemies.size(); i++)
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
			<< "[" << i + 1 << "]" << " - "
			<< EnemyTypeToString(myEnemies[i].GetType()) << ": "
			<< static_cast<int>(myEnemies[i].GetCurrentHealth()) << "/"
			<< static_cast<int>(myEnemies[i].GetMaxHealth()) << " hp | "
			<< static_cast<int>(myEnemies[i].GetDamage()) << " AD"
			<< RESET << "\n";

	}
}

