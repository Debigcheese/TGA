#pragma once
#include "User.h"

class UserManager
{

private:
	User myUserArr[5];

public:
	UserManager();

	void init(User newUserArr[5]);
	void AddUser(User userToAdd);
	void ViewAllUsers() const;
	void ViewUser() const;
	void RemoveUser();

};

