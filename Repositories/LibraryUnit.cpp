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

void LibraryUnit::copyFrom(const LibraryUnit& other)
{
	setTitle(other.title);
	setPublisher(other.publisher);
	setGenre(other.genre);
	setBriefDescription(other.description);
	setRating(other.rating);
}

LibraryUnit::LibraryUnit(std::string title, std::string publisher, std::string genre,
	std::string description, unsigned short releaseYear, unsigned short rating)
	: releaseYear(releaseYear)
{
	setTitle(title);
	setPublisher(publisher);
	setGenre(genre);
	setBriefDescription(description);
	setRating(rating);
}

LibraryUnit::LibraryUnit(const LibraryUnit& other) : releaseYear(other.releaseYear)
{
	copyFrom(other);
}

LibraryUnit& LibraryUnit::operator=(const LibraryUnit& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}
