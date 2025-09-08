#include "User.h"
#include <iostream>

User::User() : myUserName(""), myPhoneNumber("112") {}

void User::Init(std::string newUserName, std::string newPhoneNumber)
{
	myUserName = newUserName;
	myPhoneNumber = newPhoneNumber;
}

void User::PrintPersonalInfo() const
{
	std::cout << "Username: " << myUserName
		<< "Phone number: " << myPhoneNumber;
}

std::string User::GetUserName() const
{
	return myUserName;
}

std::string User::GetPhoneNumber() const
{
	return myPhoneNumber;
}

