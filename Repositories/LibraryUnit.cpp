#include "LibraryUnit.h"

const std::string LibraryUnit::getTitle() const
{
	return title;
}

const std::string LibraryUnit::getPublisher() const
{
	return publisher;
}

const std::string LibraryUnit::getGenre() const
{
	return genre;
}

const std::string LibraryUnit::getBriefDescription() const
{
	return briefDescription;
}

const unsigned short LibraryUnit::getReleaseYear() const
{
	return releaseYear;
}

const unsigned LibraryUnit::getUniceNumber() const
{
	return uniceNumber;
}

const double LibraryUnit::getRating() const
{
	return rating;
}

void LibraryUnit::setTitle(const std::string& str)
{

}

void LibraryUnit::setPublisher(const std::string& str)
{
}

void LibraryUnit::setGenre(const std::string& str)
{
}

void LibraryUnit::setBriefDescription(const std::string& str)
{
}

void LibraryUnit::setReleaseYear(unsigned short year)
{
	releaseYear = year;
}

void LibraryUnit::setRating(double rating)
{
	this->rating = rating;
}

unsigned LibraryUnit::generateRandomNumber() // ?? is this correct?
{
	return rand();
}

LibraryUnit::LibraryUnit()
{
}

LibraryUnit::LibraryUnit(std::string title, std::string publisher, std::string genre, std::string description, short releaseYear, double rating)
{
}

LibraryUnit::~LibraryUnit()
{
}

LibraryUnit::LibraryUnit(const LibraryUnit& other)
{
}

LibraryUnit& LibraryUnit::operator=(const LibraryUnit& other)
{
	// TODO: insert return statement here
}
