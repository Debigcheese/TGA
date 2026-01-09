#include "UserManager.h"
#include <string>
#include <iostream>
#include <random>

UserManager::UserManager() : myUserArr() {}

void UserManager::init()
{
	for (int i = 0; i < std::size(myUserArr); i++)
	{
		myUserArr[i] = User();
	}
}

void UserManager::AddUser()
{
	User userToAdd;

	std::cout << "\nEnter username: ";

	std::string userName = "";
	std::cin >> userName;

	userToAdd.SetUserName(userName);

	std::cout << "\nEnter phonenumber: ";

	std::string phoneNumber = "";
	std::cin >> phoneNumber;

	userToAdd.SetPhoneNumber(phoneNumber);

	int randomId = GetRandomID();
	userToAdd.SetId(randomId);

	std::cout << "\nUser added!\n";

	for (User& u : myUserArr)
	{
		if (u.GetId() == 0 && u.GetId() != userToAdd.GetId())
		{
			u = userToAdd;// checks if the array has a spot empty & the user doesnt already exist
			break;
		}
	}

	//for (int i = 0; i < std::size(myUserArr); i++)
	//{
	//	if (myUserArr[i].GetId() == 0 && myUserArr[i].GetId() != userToAdd.GetId()) // checks if the array has a spot empty & the user doesnt already exist
	//	{
	//		myUserArr[i] = userToAdd;
	//		break;
	//	}
	//}
}

void UserManager::ViewAllUsers() const
{
	std::cout << "\n";

	for (int i = 0; i < std::size(myUserArr); i++)
	{
		std::cout
			<< "|" << i + 1 << "| "
			<< "Name: " << myUserArr[i].GetUserName() << "\t"
			<< "PhoneNumber: " << myUserArr[i].GetPhoneNumber() << "\n";
	}
}

void UserManager::ViewUser() const
{
	std::cout << "Search user by name or phonenumber\n"
		<< "(1) Name\n"
		<< "(2) Phonenumber\n";

	int choice = ReadIntInRange(1, 2);

	User userToView;

	if (choice == 1)
	{
		userToView = FindUserBySearch(true, false);

	}
	else
	{
		userToView = FindUserBySearch(false, true);
	}

	if (userToView.GetId() == 0)
	{
		std::cout << "No user found.\n";
	}
	else
	{
		PrintUser(userToView);
	}
}

void UserManager::RemoveUser()
{
	std::cout << "Remove user by name or phonenumber\n"
		<< "(1) Name\n"
		<< "(2) Phonenumber\n";

	int choice = ReadIntInRange(1, 2);

	User userToRemove;

	if (choice == 1)
	{
		userToRemove = FindUserBySearch(true, false);
	}
	else
	{
		userToRemove = FindUserBySearch(false, true);
	}

	for (User& u : myUserArr)
	{
		if (u.GetId() != 0 && u.GetId() == userToRemove.GetId())  // checks if the array has a spot empty & the user exists
		{
			u.Reset();
			std::cout << "\nUser Removed!\n";
			return;
		}
	}
	std::cout << "\nUser not found.\n";
}

int UserManager::GetRandomID() const
{
	std::random_device global_rd;
	std::mt19937 global_gen(global_rd());
	std::uniform_int_distribution<int>dist(0, 10000);

	int randomGenID = dist(global_gen);

	for (User u : myUserArr)
	{
		if (u.GetId() != randomGenID)
		{
			return randomGenID;
		}
	}

	return 0;
}

//------------------- helpers ----------------
int UserManager::ReadIntInRange(int aMin, int aMax) const
{
	while (true)
	{
		int value = 0;
		std::cin >> value;
		if (std::cin.fail() || value < aMin || value > aMax)
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "\nInvalid choice, choose between (" << aMin << " - " << aMax << "): ";
			continue;
		}
		return value;
	}
}

void UserManager::PrintUser(User UserToPrint) const
{
	std::cout
		<< "Name: " << UserToPrint.GetUserName() << "\t"
		<< "PhoneNumber: " << UserToPrint.GetPhoneNumber() << "\n";
}

User UserManager::FindUserBySearch(bool findByName, bool findByNumber) const
{
	std::cout << "\nSearch: ";

	while (true)
	{
		std::string inputUserToView = "";
		std::cin >> inputUserToView;
		ToLowerCase(inputUserToView);

		for (User u : myUserArr)
		{
			std::string userName = u.GetUserName();
			if (inputUserToView == ToLowerCase(userName) && findByName)
			{
				return u;
			}
			else if (inputUserToView == u.GetPhoneNumber() && findByNumber)
			{
				return u;
			}
		}
		break;
	}

	return User();
}

std::string UserManager::ToLowerCase(std::string& s) const
{
	for (char& c : s)
	{
		c = std::tolower(static_cast<unsigned char>(c));
	}
	return s;
}
