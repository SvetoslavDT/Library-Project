#include "Series.h"

Series::Series(const std::string& title, const std::string& publisher, const std::string& genre,
	const std::string& description, unsigned short releaseYear, unsigned short rating,
	const std::string& author, unsigned short month, const std::vector<Article>& articles,
	const std::string& isbn = "", const std::string& issn = "")
	: LibraryUnit(title, publisher, genre, description, releaseYear, rating),
	  Book(title, publisher, genre, description, releaseYear, rating, author, isbn),
	  Periodical(title, publisher, genre, description, releaseYear, rating, month, articles, issn) {}

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

	return os;
}

std::istream& operator>>(std::istream& is, const Series& obj)
{
	is >> (Book&)obj;
	is >> (Periodical&)obj;

	return is;
}
