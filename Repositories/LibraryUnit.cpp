#include "LibraryUnit.h"
#include <exception>
#include <stdexcept>

const std::string& LibraryUnit::getTitle() const
{
	return title;
}

const std::string& LibraryUnit::getPublisher() const
{
	return publisher;
}

const std::string& LibraryUnit::getGenre() const
{
	return genre;
}

const std::string& LibraryUnit::getBriefDescription() const
{
	return description;
}

const unsigned short LibraryUnit::getReleaseYear() const
{
	return releaseYear;
}

const unsigned LibraryUnit::getUniqueNumber() const
{
	return uniqueNumber;
}

const unsigned short LibraryUnit::getRating() const
{
	return rating;
}

void LibraryUnit::setTitle(const std::string& str)
{
	if (!str.empty())
		title = str;
	else
		throw std::invalid_argument("String can not be empty");
}

void LibraryUnit::setPublisher(const std::string& str)
{
	if (!str.empty())
		publisher = str;
	else
		throw std::invalid_argument("String can not be empty");
}

void LibraryUnit::setGenre(const std::string& str)
{
	if (!str.empty())
		genre = str;
	else
		throw std::invalid_argument("String can not be empty");
}

void LibraryUnit::setBriefDescription(const std::string& str)
{
	if (!str.empty())
		description = str;
	else
		throw std::invalid_argument("String can not be empty");
}

void LibraryUnit::setReleaseYear(unsigned short year)
{
	releaseYear = year;
}

void LibraryUnit::setRating(unsigned short rating) // 5 star rating system
{
	if (rating > 5)
		throw std::invalid_argument("Book are rated from 0 to 5 stars");
	this->rating = rating;
}

void LibraryUnit::setUniqueNumber()
{
	uniqueNumber = rand() * rand(); // To be sure its unique
}

void LibraryUnit::copyFrom(const LibraryUnit& other)
{
	setTitle(other.title);
	setPublisher(other.publisher);
	setGenre(other.genre);
	setBriefDescription(other.description);
	setRating(other.rating);
	setUniqueNumber();
	setReleaseYear(other.releaseYear);
}

LibraryUnit::LibraryUnit(const std::string& title, const std::string& publisher, const std::string& genre,
	const std::string& description, unsigned short releaseYear, unsigned short rating)
	: title(title), genre(genre), description(description), releaseYear(releaseYear)
{
	setPublisher(publisher);
	setRating(rating);
	setUniqueNumber();
}

LibraryUnit::LibraryUnit(const LibraryUnit& other) : title(other.title), genre(other.genre),
	description(other.description), releaseYear(other.releaseYear)
{
	setPublisher(other.publisher);
	setRating(other.rating);
	setUniqueNumber();
}

LibraryUnit& LibraryUnit::operator=(const LibraryUnit& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

std::string generateNString(size_t n)
{
	unsigned short i;
	std::string result(n, 'X'); // Allocating space at the beginning

	for (size_t j = 0; j < n; j++)
	{
		i = rand() % 10;
		result[j] = fromDigitToChar(i);
	}

	return result;
}

char fromDigitToChar(unsigned short digit)
{
	return char('0' + digit);
}

bool LibraryUnit::isDigit(const char& ch) const
{
	return ch >= '0' && ch <= '9';
}
