#pragma once
#include "Room.h"
#include "Door.h"
#include "Player.h"

class WorldMap
{
public:
    WorldMap();
    void InitWorldMap(std::vector<Room> aRooms, std::vector<Door> aDoors);

    //rooms & doors
    std::vector<Door>& GetDoors();
    std::vector<Room>& GetRooms();
    Room* GetRoomWithId(int aRoomId);
    const Room* GetRoomWithId(int aRoomId) const;
    std::vector<int> GetRoomIds() const;

    static bool HasRoom(int x, int y);
    void PrintMap(Position player);

    Position GetWinRoomPos() const { return GetRoomWithId(ROOM_WIN_ID)->GetPosition(); }
    bool GetReachedWinRoom(const Position& aPosition) const;

    std::vector<Position> GetRoomPositions() const;

private:
    std::vector<Room> myRooms;
    std::vector<Door> myDoors;

    //constants
    //ROOMS
    static constexpr int ROOM_0_ID = 0;
    static constexpr int ROOM_1_ID = 1;
    static constexpr int ROOM_2_ID = 2;
    static constexpr int ROOM_3_ID = 3;
    static constexpr int ROOM_4_ID = 4;
    static constexpr int ROOM_5_ID = 5;
    static constexpr int ROOM_WIN_ID = 6;

    static constexpr int ROOM_SIZE = 7;

    static constexpr Position ROOM_POS_FROM_ID[ROOM_SIZE] = {
        {0, 0},
        {1, 0},
        {0, 1},
        {1, 1},
        {0, 2},
        {-1, 2},
        {-1, 3}
    };
};
