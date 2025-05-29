#include "User.h"
#include "Functions.h"

User::User(const std::string& name, const std::string& password)
	: name(name), password(password), registerDate(Date()), lastLogin(registerDate)
{
	if (name.empty() || password.empty())
		throw std::invalid_argument("Name OR/AND password is empty");
}

const std::string& User::getName() const
{
	return name;
}

const std::string& User::getPassword() const
{
	return password;
}

const Date& User::getRegisterDate() const
{
	return registerDate;
}

const Date& User::getLastLogin() const
{
	return lastLogin;
}

void User::setName(const std::string& name)
{
	if (name.empty())
		throw std::invalid_argument("Empty username");

	this->name = name;
}

void User::setPassword(const std::string& password)
{
	if(password.empty())
		throw std::invalid_argument("Empty password");

	this->password = password;
}

void User::setLastLogin()
{
	lastLogin.setCurrentDate();
}

void User::writeToBinary(std::ostream& os) const
{
	FunctionsForBinary::writeString(os, name);
	FunctionsForBinary::writeString(os, password);
	registerDate.writeDateToBinary(os);
	lastLogin.writeDateToBinary(os);
}

void User::readFromBinary(std::istream& is)
{
	name = FunctionsForBinary::readString(is);
	password = FunctionsForBinary::readString(is);
	registerDate.readDateFromBinary(is);
	lastLogin.readDateFromBinary(is);
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << user.name          << '\n'
		<< user.password     << '\n'
		<< user.registerDate << '\n'
		<< user.lastLogin    << '\n';

	return os;
}

std::istream& operator>>(std::istream& is, User& user) // ?? strong exception safe li e
{
	std::string name, password;
	Date reg;
	Date last;

	if (!std::getline(is, name)) return is;
	if (!std::getline(is, password)) return is;
	if (!(is >> reg)) return is;
	if (!(is >> last)) return is;

	is.ignore(1, '\n');

	user.name = name;
	user.password = password;
	user.registerDate = reg;
	user.lastLogin = last;

	return is;
}
