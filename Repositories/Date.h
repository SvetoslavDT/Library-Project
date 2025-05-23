#pragma once
#include <string>
#include <iostream>

class Date
{
public:

	Date(unsigned date);
	Date(unsigned day, unsigned month, unsigned year);

	const unsigned getDate() const;
	const unsigned getDay() const;
	const unsigned getDay(unsigned date) const;
	const unsigned getMonth() const;
	const unsigned getMonth(unsigned date) const;
	const unsigned getYear() const;
	const unsigned getYear(unsigned date) const;

	void setDate(unsigned day, unsigned month, unsigned year);
	void setDate(unsigned date);

private:

	bool checkDate(unsigned date) const;
	bool leapYear(unsigned year) const;

	unsigned date = 0;

	const static unsigned short DAY_MONTH_LENGTH;
	const static unsigned short YEAR_LENGTH;
};

std::ostream& operator<<(std::ostream& os, const Date& date);
std::istream& operator>>(std::istream& is, Date& date);
