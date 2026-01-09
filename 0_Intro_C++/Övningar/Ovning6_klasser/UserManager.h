#pragma once
#include "User.h"

class UserManager
{
private:
	User myUserArr[5];


public:
	UserManager();

	void init();
	void AddUser();
	void ViewAllUsers() const;
	void ViewUser() const;
	void RemoveUser();
	int GetRandomID() const;

	//helpers
	void PrintUser(User userToPrint) const;
	int ReadIntInRange(int aMin, int aMax) const;
	User FindUserBySearch(bool findByName, bool findByNumber) const;
	std::string ToLowerCase(std::string& s) const;
};

