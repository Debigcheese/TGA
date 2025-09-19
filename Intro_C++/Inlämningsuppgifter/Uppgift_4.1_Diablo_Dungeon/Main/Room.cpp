#include "Room.h"

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

std::vector<Enemy> Room::GetEnemies() const
{
	return myEnemies;
}

void Room::AddEnemyToRoom(const Enemy& aEnemyToAdd)
{
	myEnemies.push_back(aEnemyToAdd);
}

void Room::AddDoor(Door door)
{
	myDoors.push_back(door);
}

const std::vector<Door> Room::GetDoorsConnected() const
{
	return myDoors;
}
