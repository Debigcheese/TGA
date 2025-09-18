#include "Diablo.h"
#include "WorldMap.h"
#include "Room.h" 
#include "Enemy.h"
#include "Utils.h"
#include "Print.h"

#include <iostream>

using namespace Print;
using namespace Utils;

Diablo::Diablo()
{
}

void Diablo::RunDiablo()
{
	myWorldMap.GenerateWorld();

	PrintIntro();
	PrintMainMenu();
	int menuChoice = ReadIntInRange(1, 2);

	system("cls");
	std::vector<Room> myRooms = myWorldMap.GetRooms();
	std::vector<Door> myDoors = myWorldMap.GetDoors();
	myPlayer.EnterRoom(0);

	std::cout << "Location: ";
	std::string n = myRooms.at(0).GetRoomName();
	std::cout << n << "\n";

	std::cout
		<< "\n<--- Navigation --->\n"
		<< "1) Left\n"
		<< "2) Middle\n"
		<< "3) Right\n"
		<< "4) Return back\n"
		<< "Choice: ";

	//myDoors.at myPlayer.OpenDoor();
}
