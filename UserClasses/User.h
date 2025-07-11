#pragma once
#include <iostream>
#include <string>
#include "Date.h"

class User
{
public:

	User() = default;
	User(const std::string& name, const std::string& password);
	virtual ~User() = default;

	const std::string& getName() const;
	const std::string& getPassword() const;
	const Date& getRegisterDate() const;
	const Date& getLastLogin() const;

	void setName(const std::string& name);
	void setPassword(const std::string& password);
	void setLastLogin();

	virtual User* clone() const = 0;

	friend std::ostream& operator<<(std::ostream& os, const User& user);
	friend std::istream& operator>>(std::istream& is, User& user);

	virtual void writeToBinary(std::ostream& os) const = 0;
	virtual void readFromBinary(std::istream& is) = 0;
	
	virtual void serialise(std::ostream& os) const = 0;
	virtual void deserialize(std::istream& is) = 0;

	virtual void print() const = 0;
	virtual std::string getType() const = 0;
	virtual unsigned getPrintLines() const = 0;

protected:

	std::string name;
	std::string password;
	Date registerDate;
	Date lastLogin;
};
