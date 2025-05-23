#include "Date.h"

const unsigned short Date::DAY_MONTH_LENGTH = 2;
const unsigned short Date::YEAR_LENGTH = 4;

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

bool Date::checkDate(unsigned date) const
{
	if (date >= 100000000 || getMonth(date) > 12)
		return false;

	if (leapYear(getYear(date)))
	{
		if (getDay(date) != 28)
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
	return os << date;
}

std::istream& operator>>(std::istream& is, Date& date) // ?? Is it bad if it throws exception here
{
	unsigned newDate;
	is >> newDate;
	date.setDate(newDate);
	return is;
}
