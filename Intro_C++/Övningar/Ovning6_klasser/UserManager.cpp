#include "UserManager.h"
#include <iostream>

UserManager::UserManager() : myUserArr() {}

void UserManager::init(User newUserArr[5])
{
}

void UserManager::AddUser(User userToAdd)
{
	for (int i = 0; i < std::size(myUserArr); i++) {
		if (myUserArr[i].GetUserName() == "")
		{
			myUserArr[i] = userToAdd;
			break;
		}
	}
}

void UserManager::ViewAllUsers() const
{
	for (int i = 0; i < std::size(myUserArr); i++) {

	}
}
