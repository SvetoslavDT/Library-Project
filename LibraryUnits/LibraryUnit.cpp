#include "LibraryUnit.h"
#include "Functions.h"
#include "Date.h"
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

const unsigned short LibraryUnit::getCopies() const
{
	return copies;
}

unsigned short& LibraryUnit::getCopies()
{
	return copies;
}

const unsigned short LibraryUnit::getTaken() const
{
	return taken;
}

unsigned short& LibraryUnit::getTaken()
{
	return taken;
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
	if (Date{}.getYear() < year)
		throw std::invalid_argument("Year is not yet reached.");
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

LibraryUnit& LibraryUnit::operator++()
{
	++copies;
	return *this;
}

LibraryUnit& LibraryUnit::operator--()
{
	--copies;
	return *this;
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

	os.write((const char*)&copies, sizeof(copies));
	os.write((const char*)&taken, sizeof(taken));
}

void LibraryUnit::readFromBinary(std::istream& is)
{
	std::string tmpTitle = FunctionsForBinary::readString(is);
	std::string tmpPublisher = FunctionsForBinary::readString(is);
	std::string tmpGenre = FunctionsForBinary::readString(is);
	std::string tmpDescription = FunctionsForBinary::readString(is);

	unsigned short tmpReleaseYear, tmpRating, tmpCopies, tmpTaken;
	unsigned tmpUniqueNumber;

	is.read((char*)&tmpReleaseYear, sizeof(tmpReleaseYear));
	is.read((char*)&tmpRating, sizeof(tmpRating));
	is.read((char*)&tmpUniqueNumber, sizeof(tmpUniqueNumber));
	is.read((char*)&tmpCopies, sizeof(tmpCopies));
	is.read((char*)&tmpTaken, sizeof(tmpTaken));

	title = std::move(tmpTitle);
	publisher = std::move(tmpPublisher);
	genre = std::move(tmpGenre);
	description = std::move(tmpDescription);

	releaseYear = tmpReleaseYear;
	rating = tmpRating;
	uniqueNumber = tmpUniqueNumber;
	copies = tmpCopies;
	taken = tmpTaken;
}

void LibraryUnit::serialise(std::ostream& os) const
{
	os << title << '\n' << publisher << '\n' << genre << '\n' << description << '\n'
		<< releaseYear << '\n' << rating << '\n' << uniqueNumber << '\n'
		<< copies << '\n' << taken << '\n';
}

void LibraryUnit::deserialize(std::istream& is)
{
	std::string title, publisher, genre, description;
	unsigned short release;
	unsigned short rating;
	unsigned uniqueNum;
	unsigned short copies;
	unsigned short taken;

	if (!std::getline(is, title)) throw std::exception("Stream failed");
	if (!std::getline(is, publisher)) throw std::exception("Stream failed");
	if (!std::getline(is, genre)) throw std::exception("Stream failed");
	if (!std::getline(is, description)) throw std::exception("Stream failed");
	if (!(is >> release)) throw std::exception("Stream failed");
	if (!(is >> rating)) throw std::exception("Stream failed");
	if (!(is >> uniqueNum)) throw std::exception("Stream failed");
	if(!(is >> copies)) throw std::exception("Stream failed");
	if(!(is >> taken)) throw std::exception("Stream failed");

	is.ignore(1, '\n');

	setTitle(title);
	setPublisher(publisher);
	setRating(rating);
	setBriefDescription(description);
	setReleaseYear(release);
	setRating(rating);
	this->uniqueNumber = uniqueNum;
	this->copies = copies;
	this->taken = taken;
}

void LibraryUnit::print() const
{
	std::cout << "Title - " << title << '\n';
	std::cout << "Publisher - " << publisher << '\n';
	std::cout << "Genre - " << genre << '\n';
	std::cout << "Description - " << description << '\n';
	std::cout << "Release year - " << releaseYear << '\n';
	std::cout << "Rating - " << rating << '\n';
	std::cout << "Unique number - " << uniqueNumber << '\n'; 
	// std::cout << "Copies count - " << copies << '\n';
	// std::cout << "Taken units - " << taken << '\n';
}

LibraryUnit::LibraryUnit(const std::string& title, const std::string& publisher, const std::string& genre,
	const std::string& description, unsigned short releaseYear, unsigned short rating)
	: title(title), genre(genre), description(description)
{
	setPublisher(publisher);
	setRating(rating);
	setUniqueNumber();
	setReleaseYear(releaseYear);
}

std::ostream& operator<<(std::ostream& os, const LibraryUnit& obj)
{
	obj.serialise(os);

	return os;
}

std::istream& operator>>(std::istream& is, LibraryUnit& obj)
{
	obj.deserialize(is);

	return is;
}
