#include "User.h"
#include <iostream>

User::User() : myID(0), myUserName(""), myPhoneNumber("") {}

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

void User::Reset()
{
	SetId(0);
	SetUserName("");
	SetPhoneNumber("");
}

void User::SetUserName(std::string newUserName)
{
	myUserName = newUserName;
}

void User::SetPhoneNumber(std::string newPhoneNumber)
{
	myPhoneNumber = newPhoneNumber;
}

void User::SetId(int newId)
{
	myID = newId;
}

bool User::operator==(const User& other) const
{
	return myID == other.myID;
}

std::string User::GetUserName() const
{
	return myUserName;
}

std::string User::GetPhoneNumber() const
{
	return myPhoneNumber;
}

int User::GetId() const
{
	return myID;
}

