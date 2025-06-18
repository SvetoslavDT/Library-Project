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
	std::string tmpName = FunctionsForBinary::readString(is);
	std::string tmpPass = FunctionsForBinary::readString(is);
	Date tmpRegDate;
	Date tmpLastLog;
	tmpRegDate.readDateFromBinary(is);
	tmpLastLog.readDateFromBinary(is);

	name = std::move(tmpName);
	password = std::move(tmpPass);
	registerDate = tmpRegDate;
	lastLogin = tmpLastLog;
}

void User::serialise(std::ostream& os) const
{
	os << name << '\n' << password << '\n' << registerDate << '\n' << lastLogin << '\n';
}

void User::deserialize(std::istream& is)
{
	std::string name, password;
	Date reg;
	Date last;

	if (!std::getline(is, name)) throw std::exception("Stream failed");
	if (!std::getline(is, password)) throw std::exception("Stream failed");
	if (!(is >> reg)) throw std::exception("Stream failed");
	if (!(is >> last)) throw std::exception("Stream failed");

	is.ignore(1024, '\n');

	if (last < reg)
		throw std::logic_error("Registration date can not be after last the last login.");

	setName(name);
	setPassword(password);
	this->registerDate = reg;
	this->lastLogin = last;
}

void User::print() const
{
	std::cout << "Name - " << name << '\n';
	std::cout << "Register date - " << registerDate << '\n';
	std::cout << "Last login - " << lastLogin << '\n';
}

unsigned User::getPrintLines() const
{
	return 4;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	user.serialise(os);

	return os;
}

std::istream& operator>>(std::istream& is, User& user)
{
	user.deserialize(is);

	return is;
}
