#pragma once
#include <string>

class User
{

private:
	std::string myUserName;
	std::string myPhoneNumber;

public:
	User();
	void Init(std::string newUserName, std::string newPhoneNumber);

	void PrintPersonalInfo() const;

	std::string GetUserName() const;
	std::string GetPhoneNumber() const;

};

