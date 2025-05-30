#include "Date.h"
#include <ctime>
#pragma warning(disable : 4996);

const unsigned short Date::DAY_MONTH_LENGTH = 2;
const unsigned short Date::YEAR_LENGTH = 4;

Date::Date()
{
	setCurrentDate();
}

Date::Date(unsigned date)
{
	if(!checkDate(date))
		throw std::invalid_argument("Invalid arguments");

	this->date = date;
}

Date::Date(unsigned day, unsigned month, unsigned year)
{
	setDate(day, month, year);
}

const unsigned Date::getDate() const
{
	return date;
}

const unsigned Date::getDay() const
{
	return getDay(date);
}

const unsigned Date::getDay(unsigned date) const
{
	return date / 1000000;
}

const unsigned Date::getMonth() const
{
	return getMonth(date);
}

const unsigned Date::getMonth(unsigned date) const
{
	return (date / 10000) % 100;
}

const unsigned Date::getYear() const
{
	return getYear(date);
}

const unsigned Date::getYear(unsigned date) const
{
	return date % 10000;
}

void Date::setDate(unsigned day, unsigned month, unsigned year)
{
	unsigned date = day;
	date *= Date::DAY_MONTH_LENGTH;
	date += month;
	date *= Date::YEAR_LENGTH;
	date += year;
	
	if (!checkDate(date))
		throw std::invalid_argument("Invalid arguments");

	this->date = date;
}

void Date::setDate(unsigned date)
{
	if(!checkDate(date))
		throw std::invalid_argument("Invalid arguments");

	this->date = date;
}

void Date::setCurrentDate()
{
	std::time_t t = std::time(nullptr);
	std::tm* tm = std::localtime(&t);

	unsigned day = static_cast<unsigned>(tm->tm_mday);
	unsigned month = static_cast<unsigned>(tm->tm_mon) + 1;
	unsigned year = static_cast<unsigned>(tm->tm_year) + 1900;

	setDate(day, month, year);
}

void Date::writeDateToBinary(std::ostream& os) const
{
	os.write((const char*)&date, sizeof(date));
}

void Date::readDateFromBinary(std::istream& is)
{
	is.read((char*)&date, sizeof(date));
}

Date& Date::operator-=(unsigned month)
{
	const unsigned DECEMBER = 12;

	if (this->getMonth() > month)
	{
		setDate(this->getDay(), this->getMonth() - month, this->getYear());
	}
	else
	{
		setDate(this->getDay(), DECEMBER - (month - this->getMonth()), this->getYear() - 1);
	}

		return *this;
}

Date& Date::operator+=(unsigned month)
{
	const unsigned DECEMBER = 12;

	if (this->getMonth() + month <= DECEMBER)
	{
		setDate(this->getDay(), this->getMonth() + month, this->getYear());
	}
	else
	{
		setDate(this->getDay(), (this->getMonth() + month) - DECEMBER, this->getYear() + 1);
	}
	
		return *this;
}

bool Date::checkDate(unsigned date) const
{
	if (date >= 100000000 || getMonth(date) > 12)
		return false;

	if (leapYear(getYear(date)))
	{
		if (getDay(date) > 28)
			return false;
	}

	return true;
}

bool Date::leapYear(unsigned year) const
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	return os << date.getDate();
}

std::istream& operator>>(std::istream& is, Date& date)
{
	unsigned newDate;
	is >> newDate;
	date.setDate(newDate);
	return is;
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return lhs.getDate() == rhs.getDate();
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.getYear() < rhs.getYear())
		return true;
	else if (lhs.getYear() == rhs.getYear())
	{
		if (lhs.getMonth() < rhs.getMonth())
			return true;
		else if (lhs.getMonth() == rhs.getMonth())
		{
			if (lhs.getDay() < rhs.getDay())
				return true;
			return false;
		}
		else
			return false;
	}
	return false;
}

bool operator>(const Date& lhs, const Date& rhs)
{
	return !(lhs <= rhs);
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	return (lhs == rhs) || (lhs < rhs);
}

bool operator>=(const Date& lhs, const Date& rhs)
{
	return !(lhs < rhs);
}

Date operator-(const Date& rhs, const Date& lhs)
{
	Date temp(lhs);
	temp -= rhs.getMonth();

	return temp;
}

Date operator+(const Date& rhs, const Date& lhs)
{
	Date temp(lhs);
	temp += rhs.getMonth();

	return temp;
}
