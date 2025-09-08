#pragma once
#include <string>

class User
{

private:
	int myID;
	std::string myUserName;
	std::string myPhoneNumber;

public:
	User();
	void Init(std::string newUserName, std::string newPhoneNumber);
	void PrintPersonalInfo() const;
	void Reset();
	void SetUserName(std::string newUserName);
	void SetPhoneNumber(std::string newPhoneNumber);
	void SetId(int newId);

	bool operator==(const User& other) const;
	std::string GetUserName() const;
	std::string GetPhoneNumber() const;
	int GetId() const;

};

