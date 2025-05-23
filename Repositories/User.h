#pragma once
#include "Date.h"
#include <string>

class User
{
public:

	User() = default;
	User(const std::string& name, const std::string password, unsigned registerDate, unsigned lastLogin);
	User(const User& other);
	User& operator=(const User& other);
	virtual ~User() = default;

	const std::string& getName() const;
	const std::string& getPassword() const;
	const Date& getRegisterDate() const;
	const Date& getLastLogin() const;

	void setName(const std::string& name);
	void setPassword(const std::string& password);
	void setRegisterDate(const Date& date);
	void setLastLogin(const Date& date);

	virtual User* clone();

private:

	std::string name;
	std::string password;
	Date registerDate;
	Date lastLogin;
};
