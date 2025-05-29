#include "LibraryUnit.h"
#include "Functions.h"
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

void LibraryUnit::writeToBinary(std::ostream& os) const
{
	FunctionsForBinary::writeString(os, title);
	FunctionsForBinary::writeString(os, publisher);
	FunctionsForBinary::writeString(os, genre);
	FunctionsForBinary::writeString(os, description);

	os.write((const char*)&releaseYear, sizeof(releaseYear));
	os.write((const char*)&rating, sizeof(rating));
	os.write((const char*)&uniqueNumber, sizeof(uniqueNumber));
}

void LibraryUnit::readFromBinary(std::istream& is)
{
	title = FunctionsForBinary::readString(is);
	publisher = FunctionsForBinary::readString(is);
	genre = FunctionsForBinary::readString(is);
	description = FunctionsForBinary::readString(is);

	is.read((char*)&releaseYear, sizeof(releaseYear));
	is.read((char*)&rating, sizeof(rating));
	is.read((char*)&uniqueNumber, sizeof(uniqueNumber));
}

LibraryUnit::LibraryUnit(const std::string& title, const std::string& publisher, const std::string& genre,
	const std::string& description, unsigned short releaseYear, unsigned short rating)
	: title(title), genre(genre), description(description), releaseYear(releaseYear)
{
	setPublisher(publisher);
	setRating(rating);
	setUniqueNumber();
}

std::ostream& operator<<(std::ostream& os, const LibraryUnit& obj)
{
	os << obj.title << '\n' << obj.publisher << '\n' << obj.genre << '\n' << obj.description
		<< obj.releaseYear << '\n' << obj.rating << '\n' << obj.uniqueNumber << '\n';

	return os;
}

std::istream& operator>>(std::istream& is, LibraryUnit& obj)
{
	std::string title, publisher, genre, description;
	unsigned short release;
	unsigned short rating;
	unsigned uniqueNum;

	if (!std::getline(is, title)) throw std::exception("Stream failed");
	if (!std::getline(is, publisher)) throw std::exception("Stream failed");
	if (!std::getline(is, genre)) throw std::exception("Stream failed");
	if (!std::getline(is, description)) throw std::exception("Stream failed");
	if (!(is >> release)) throw std::exception("Stream failed");
	if (!(is >> rating)) throw std::exception("Stream failed");
	if (!(is >> uniqueNum)) throw std::exception("Stream failed");

	is.ignore(1, '\n');

	obj.title = title;
	obj.publisher = publisher;
	obj.rating = rating;
	obj.description = description;
	obj.releaseYear = release;
	obj.rating = rating;
	obj.uniqueNumber = uniqueNum;

	return is;
}
