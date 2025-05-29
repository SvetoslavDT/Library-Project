#include "Reader.h"

Reader::LibraryUnitTaken::LibraryUnitTaken(const LibraryUnit* unit, const Date& borrowDate, const Date& returnDate)
	: borrowDate(borrowDate), returnDate(returnDate)
{
	if (returnDate < borrowDate)
		throw std::logic_error("Can not return a unit before borrowing it");

	unit = unit->clone();
}

Reader::LibraryUnitTaken::LibraryUnitTaken(const LibraryUnitTaken& other)
	: borrowDate(borrowDate), returnDate(returnDate)
{
	unit = other.unit->clone();
}

Reader::LibraryUnitTaken& Reader::LibraryUnitTaken::operator=(const LibraryUnitTaken& other)
{
	if (this != &other)
	{
		unit = other.unit->clone();
		borrowDate = other.borrowDate;
		returnDate = other.returnDate;
	}
	return *this;
}

Reader::LibraryUnitTaken::~LibraryUnitTaken()
{
	delete unit;
}

const LibraryUnit* Reader::LibraryUnitTaken::getUnit() const
{
	return unit;
}

const Date& Reader::LibraryUnitTaken::getBorrowDate() const
{
	return borrowDate;
}

const Date& Reader::LibraryUnitTaken::getReturnDate() const
{
	return returnDate;
}

void Reader::LibraryUnitTaken::seReturnDate(const Date& date)
{
	if (date < borrowDate)
		throw std::logic_error("Can not return a unit before borrowing it");
	returnDate = date;
}

void Reader::LibraryUnitTaken::writeToBinary(std::ostream& os) const
{
	unit->writeToBinary(os);
	borrowDate.writeDateToBinary(os);
	returnDate.writeDateToBinary(os);
}

void Reader::LibraryUnitTaken::readFromBinary(std::istream& is)
{
	unit->readFromBinary(is);
	borrowDate.readDateFromBinary(is);
	borrowDate.readDateFromBinary(is);
}

Reader::Reader(const std::string& name, const std::string& password, const std::vector<LibraryUnitTaken>& arr)
	: User(name, password), takenUnits(arr) {}

Reader::Reader(const std::string& name, const std::string& password)
	: User(name, password) {}

const std::vector<Reader::LibraryUnitTaken> Reader::getTakenUnits() const
{
	return takenUnits;
}

void Reader::setTakenLibraryUnits(const std::vector<LibraryUnitTaken>& arr)
{
	takenUnits = arr;
}

void Reader::addLibraryUnit(const LibraryUnit* unit, const Date& borrowDate, const Date& returnDate)
{
	takenUnits.push_back({ unit, borrowDate, returnDate });
}

User* Reader::clone() const
{
	return new Reader(*this);
}

void Reader::writeToBinary(std::ostream& os) const
{
	User::writeToBinary(os);

	size_t size = takenUnits.size();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
		takenUnits[i].writeToBinary(os);
}

void Reader::readFromBinary(std::istream& is)
{
	User::readFromBinary(is);

	size_t size;
	is.read((char*)&size, sizeof(size));
	takenUnits.clear();
	takenUnits.resize(size);
	for (size_t i = 0; i < size; i++)
		takenUnits[i].readFromBinary(is);
}

std::ostream& operator<<(std::ostream& os, const Reader::LibraryUnitTaken& obj)
{
	return os << *obj.unit << '\n' << obj.borrowDate << '\n' << obj.returnDate << '\n';
}

std::ostream& operator<<(std::ostream& os, const Reader& obj)
{
	os << (const User&)obj;

	for (size_t i = 0; i < obj.takenUnits.size(); i++)
		os << obj.takenUnits[i];

	return os;
}
