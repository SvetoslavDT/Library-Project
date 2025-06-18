#include "Date.h"
#include <ctime>
#pragma warning(disable : 4996);

const unsigned short Date::DAY_MONTH_LENGTH = 100;
const unsigned short Date::YEAR_LENGTH = 10000;

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

Date& Date::operator-=(unsigned months)
{
	unsigned m = getMonth(), y = getYear(), d = getDay();

	int total = y * 12 + m - months - 1;
	y = total / 12;
	m = (total % 12) + 1;

	unsigned maxD = daysInMonth(m, y);
	unsigned newD = std::min(d, maxD);
	setDate(newD, m, y);
	return *this;
}

Date& Date::operator+=(unsigned months)
{
	unsigned d = getDay(), m = getMonth(), y = getYear();

	unsigned total = y * 12 + (m - 1) + months;
	y = total / 12;
	m = (total % 12) + 1;

	unsigned maxD = daysInMonth(m, y);
	unsigned newD = (d <= maxD ? d : maxD);

	setDate(newD, m, y);
	return *this;
}

bool Date::checkDate(unsigned date) const
{
	unsigned d = getDay(date);
	unsigned m = getMonth(date);
	unsigned y = getYear(date);

	if (m < 1 || m > 12)
		return false;

	static constexpr int daysInMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	int dim = daysInMonth[m];
	if (m == 2 && leapYear(y))
		dim = 29;

	return (d >= 1 && d <= (unsigned)dim);
}

bool Date::leapYear(unsigned year) const
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

unsigned Date::daysInMonth(unsigned month, unsigned year) const
{
	static const unsigned days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2)
	{
		return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
	}
	return days[month];
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	return os << date.getDay() << '.' << date.getMonth() << '.' << date.getYear();
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
