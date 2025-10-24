#include "WorldMap.h"
#include "Utils.h"
#include "GameStructs.h"

#include <iostream>

using namespace Utils;

WorldMap::WorldMap() :
    myRooms(),
    myDoors()
{
}

void WorldMap::InitWorldMap(std::vector<Room> aRooms, std::vector<Door> aDoors)
{
    myRooms = std::move(aRooms);
    myDoors = std::move(aDoors);
}

std::vector<Door>& WorldMap::GetDoors()
{
    return myDoors;
}

std::vector<Room>& WorldMap::GetRooms()
{
    return myRooms;
}

Room* WorldMap::GetRoomWithId(const int aRoomId)
{
    for (Room& room : myRooms)
    {
        if (room.GetRoomId() == aRoomId)
        {
            return &room;
        }
    }
    return nullptr;
}

const Room* WorldMap::GetRoomWithId(int aRoomId) const
{
    for (const Room& room : myRooms)
    {
        if (room.GetRoomId() == aRoomId)
        {
            return &room;
        }
    }
    return nullptr;
}

std::vector<int> WorldMap::GetRoomIds() const
{
    std::vector<int> roomIds;
    for (const auto& room : myRooms)
    {
        roomIds.push_back(room.GetRoomId());
    }
    return roomIds;
}

bool WorldMap::HasRoom(int x, int y)
{
    for (const auto& p : ROOM_POS_FROM_ID)
    {
        if (p.X == x && p.Y == y)
        {
            return true;
        }
    }
    return false;
}

void WorldMap::PrintMap(const Position player)
{
    constexpr int minX = -2;
    constexpr int maxX = 2;
    constexpr int minY = -1;
    constexpr int maxY = 3;

    std::cout << '\n';
    for (int y = maxY; y >= minY; --y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            if (!HasRoom(x, y))
            {
                std::cout << "   ";
                continue;
            }
            if (ROOM_POS_FROM_ID[ROOM_WIN_ID] == Position{x, y})
            {
                std::cout << "[X]";
            }
            else
            {
                std::cout << ((player.X == x && player.Y == y) ? "[O]" : "[ ]");
            }
        }
        std::cout << '\n';
    }
}

bool WorldMap::GetReachedWinRoom(const Position& aPosition) const
{
    return aPosition == GetRoomWithId(ROOM_WIN_ID)->GetPosition();
}

std::vector<Position> WorldMap::GetRoomPositions() const
{
    std::vector<Position> positions;
    positions.reserve(ROOM_SIZE);
    for (const auto& room : myRooms)
    {
        positions.push_back(room.GetPosition());
    }
    return positions;
}


//Crypt of the Forgotten
//The Hollow Catacombs
//Bloodfang Caverns
//Sanctum of Ashes
//The Withered Halls
//Pits of Torment
//Obsidian Spire
//Den of the Blighted
//The Shattered Sepulcher
//Abyss of Eternal Hunger
