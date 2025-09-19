#include "Navigation.h"
#include "Diablo.h"
#include "WorldMap.h"
#include "Room.h" 
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "Print.h"

#include <iostream>

using namespace Print;
using namespace Utils;

Navigation::Navigation(WorldMap aWorldMap, Player aPlayer) : myWorldMap(aWorldMap), myPlayer(aPlayer)
{
}

void Navigation::UpdateNavigation()
{
	myNav.currentRoom.SetRoomId(0);
	myNav.currentRoom = myWorldMap.GetRoomWithId(myNav.currentRoom.GetRoomId());


	while (true)
	{

		myPlayer.SetRoomId(myNav.currentRoom.GetRoomId());
		PrintLocation(myPlayer.GetRoomId());

		PrintNavigation();
		int navChoice = ReadIntInRange(1, 4);

		myNav.currentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId()); // gets current room
		myNav.doorsInRoom = myNav.currentRoom.GetDoorsConnected(); // gets all doors in current room

		if (navChoice == 4)
		{
			myPlayer.GetRoomId()
				myPlayer.SetRoomId(otherRoomId);
			myNav.currentRoom = myWorldMap.GetRoomWithId(otherRoomId);
		}

		int direction = myNav.currentRoom.GetRoomId() - navChoice;
		if (direction < 0)
		{
			direction = -direction;
		}
		myNav.currentDirection = static_cast<Direction>(direction);//if available door directions == direction chosen 
		myNav.doorDirections = GetValidDirections();

		if (!DoesDoorExistInDirection())
		{
			std::cout << "There is no door in that direction.\n";
			system("pause");
			system("cls");
			continue;
		}

		std::cout << "\nPlayer walks from room: " << myNav.currentRoom.GetRoomName()
			<< " - ";

		for (int i = 0; i < myNav.doorsInRoom.size();i++)
		{
			if (myNav.doorDirections.at(i) == myNav.currentDirection) //if direction == Other roomId
			{
				int otherRoomId = myNav.doorsInRoom.at(i).GetOtherRoomId(myNav.currentRoom.GetRoomId());
				myPlayer.SetRoomId(otherRoomId);
				myNav.currentRoom = myWorldMap.GetRoomWithId(otherRoomId);
				break;
			}
		}

		std::cout << myNav.currentRoom.GetRoomName()
			<< "\n";

		system("pause");
		system("cls");
	}
}


std::vector<Direction> Navigation::GetValidDirections()
{
	myNav.doorDirections.clear();
	for (int i = 0; i < myNav.doorsInRoom.size();i++)
	{
		myNav.doorDirections.push_back(myNav.doorsInRoom.at(i).GetDoorPOSFromCurrentRoomId(myNav.currentRoom.GetRoomId())); // gets available door positions
	}
	return myNav.doorDirections;
}

void Navigation::PrintNavigation()
{
	std::cout
		<< "\n<--- Navigation --->\n"
		<< "1) Left\n"
		<< "2) Middle\n"
		<< "3) Right\n"
		<< "4) Return back\n"
		<< "Choice: ";
}

void Navigation::PrintLocation(const int aRoomId)
{
	std::cout << "Location: ";
	std::string location = myNav.currentRoom.GetRoomName();
	std::cout << location << "\n";
}

bool Navigation::DoesDoorExistInDirection()
{
	for (Direction d : myNav.doorDirections)
	{
		if (d == Direction::Left)
		{
			return true;
		}
		else if (d == Direction::Front)
		{
			return true;
		}
		else if (d == Direction::Right)
		{
			return true;
		}
		else if (d == Direction::Back)
		{
			return true;
		}

	}
	return false;
}

