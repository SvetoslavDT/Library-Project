#include "Series.h"

Series::Series() : LibraryUnit(), Book(), Periodical() {}

Series::Series(const std::string& title, const std::string& publisher, const std::string& genre,
	const std::string& description, unsigned short releaseYear, unsigned short rating,
	const std::string& author, const std::string& isbn, unsigned short month,
	const std::vector<Article>& articles, const std::string& issn)
	: LibraryUnit(title, publisher, genre, description, releaseYear, rating),
	  Book(title, publisher, genre, description, releaseYear, rating, author),
	  Periodical(title, publisher, genre, description, releaseYear, rating, month, articles, issn) {}

Series::Series(const Series& other) : LibraryUnit(other), Book(other), Periodical(other) {}

Series& Series::operator=(const Series& other)
{
	if (this != &other)
	{
		LibraryUnit::operator=(other);
		Book::operator=(other);
		Periodical::operator=(other);
	}
	return *this;
}

LibraryUnit* Series::clone() const
{
	return new Series(*this);
}

void Series::writeToBinary(std::ostream& os) const
{
	Book::writeToBinary(os);
	Periodical::writeToBinary(os);
}

void Series::readFromBinary(std::istream& is)
{
	Book::readFromBinary(is);
	Periodical::readFromBinary(is);
}

std::ostream& operator<<(std::ostream& os, const Series& obj)
{
	os << (const Book&)obj;
	os << (const Periodical&)obj;
}

std::istream& operator>>(std::istream& is, const Series& obj)
{
	is >> (Book&)obj;
	is >> (Periodical&)obj;
}
