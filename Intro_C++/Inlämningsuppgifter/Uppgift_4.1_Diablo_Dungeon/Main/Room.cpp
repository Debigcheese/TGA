#include "Room.h"

Room::Room(int aRoomId, std::string aRoomName, std::vector<int> aDoorIds, std::vector<Enemy> aEnemies) :
	myRoomId(aRoomId), myRoomName(aRoomName), myDoorIds(aDoorIds), myEnemies(aEnemies)
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

std::vector<int> Room::GetDoorIds()
{
	return myDoorIds;
}
