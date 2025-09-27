#include "Diablo.h"
#include "PlayerController.h"
#include "Player.h"
#include "GameConstants.h"
#include <iostream>

using namespace GameConstants;

Diablo::Diablo() : myWorldMap(), myPlayer(myWorldMap), myPlayerController(myWorldMap, myPlayer)
{
}

void Diablo::RunDiablo()
{
	myWorldMap.GenerateWorld();

	//Welcome();
	//EnterUsername(myPlayer);
	//system("cls");
	//Intro(myPlayer);

	myPlayerController.UpdateAction();
}

void Diablo::Intro(const Player& aPlayer)
{
	std::cout << "You wake up in a dungeon...\n";
	system("pause");
	std::cout << "\nSlay the enemies in this room (" << myWorldMap.GetRoomWithId(0)->GetRoomName() <<
		") in order to proceed.\n";
	system("pause");
	std::cout << "\nAnd try your best to get the hell out of here " << aPlayer.GetName() << "!\n";
	system("pause");
}

void Diablo::Welcome()
{
	std::cout << "<--- Welcome to Diablo --->";
}

void Diablo::EnterUsername(Player& aPlayer)
{
	char name[PLAYER_NAME_ARRAY_SIZE];
	while (true)
	{
		std::cout << "\nEnter your name (2-16 letters): ";
		std::cin.get(name, PLAYER_NAME_ARRAY_SIZE);

		if (std::cin.fail())
		{
			std::cin.clear(); // clear failbit
			std::cin.ignore(CIN_IGNORE, '\n'); // discard leftover characters
		}

		int length = static_cast<int>(strlen(name));
		bool valid = (length >= PLAYER_NAME_MIN_LENGTH && length <= PLAYER_NAME_MAX_LENGTH); // 2-16 characters

		for (int i = 0; i < length && valid; i++)
		{
			if (!isalpha(static_cast<unsigned char>(name[i])))
			{
				valid = false;
			}
		}
		if (valid)
		{
			aPlayer.SetName(name);
			break;
		}
		std::cout << "Invalid name. Use only letters, 2-16 characters.\n";
	}
}
