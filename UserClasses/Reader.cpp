#include "Reader.h"
#include "Functions.h"

Reader::LibraryUnitTaken::LibraryUnitTaken(const LibraryUnit* unit, const Date& borrowDate, const Date& returnDate)
	: unit(nullptr), borrowDate(borrowDate), returnDate(returnDate)
{
	if (returnDate < borrowDate)
		throw std::logic_error("Can not return a unit before borrowing it");

	this->unit = unit->clone();
}

Reader::LibraryUnitTaken::LibraryUnitTaken(const LibraryUnitTaken& other)
	: borrowDate(other.borrowDate), returnDate(other.returnDate)
{
	unit = other.unit->clone();
}

Reader::LibraryUnitTaken& Reader::LibraryUnitTaken::operator=(const LibraryUnitTaken& other)
{
	if (this != &other)
	{
		borrowDate = other.borrowDate;
		returnDate = other.returnDate;
		delete unit;
		unit = other.unit->clone();
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
	std::string type = unit->getType();
	FunctionsForBinary::writeString(os, type);

	unit->writeToBinary(os);

	borrowDate.writeDateToBinary(os);
	returnDate.writeDateToBinary(os);
}

void Reader::LibraryUnitTaken::readFromBinary(std::istream& is)
{
	size_t len;
	is.read(reinterpret_cast<char*>(&len), sizeof(len));
	std::string type(len, '\0');
	is.read(&type[0], len);

	LibraryUnit* tmpUnit = nullptr;
	if (type == "Book")
		tmpUnit = new Book();
	else if (type == "Periodical")
		tmpUnit = new Periodical();
	else if (type == "Series")
		tmpUnit = new Series();
	else
		throw std::runtime_error("Unknown LibraryUnit type.");

	tmpUnit->readFromBinary(is);

	Date tmpBorrow, tmpReturn;
	tmpBorrow.readDateFromBinary(is);
	tmpReturn.readDateFromBinary(is);

	delete unit;
	unit = tmpUnit;
	borrowDate = tmpBorrow;
	returnDate = tmpReturn;
}

void Reader::LibraryUnitTaken::print() const
{
	unit->print();
	
	std::cout << "Borrow date - " << borrowDate << '\n';
	std::cout << "Return date - " << returnDate << '\n';
}

Reader::Reader(const std::string& name, const std::string& password, const std::vector<LibraryUnitTaken>& arr)
	: User(name, password), takenUnits(arr) {}

Reader::Reader(const std::string& name, const std::string& password)
	: User(name, password) {}

const std::vector<Reader::LibraryUnitTaken>& Reader::getTakenUnits() const
{
	return takenUnits;
}

std::vector<Reader::LibraryUnitTaken>& Reader::getTakenUnits()
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

	size_t count;
	is.read((char*)&count, sizeof(count));

	std::vector<LibraryUnitTaken> tmp;
	tmp.reserve(count);

	for (size_t i = 0; i < count; ++i)
	{
		LibraryUnitTaken lut;
		lut.readFromBinary(is);
		tmp.push_back(lut);
	}

	takenUnits.swap(tmp);
}

void Reader::serialise(std::ostream& os) const
{
	User::serialise(os);

	os << takenUnits.size() << '\n';
	for (size_t i = 0; i < takenUnits.size(); i++)
		os << takenUnits[i] << '\n';
}

void Reader::deserialize(std::istream& is)
{
	User::deserialize(is);

	size_t size;
	if(!(is >> size)) throw std::exception("Stream failed");
	std::vector<LibraryUnitTaken> unitsTaken(size);
	for (size_t i = 0; i < size; i++)
	{
		if(!(is >> unitsTaken[i])) throw std::exception("Stream failed");
	}

	setTakenLibraryUnits(unitsTaken);
}

std::ostream& operator<<(std::ostream& os, const Reader::LibraryUnitTaken& obj)
{
	return os << obj.unit->getType() << *obj.unit << '\n' << obj.borrowDate
		<< '\n' << obj.returnDate << '\n';
}

std::istream& operator>>(std::istream& is, Reader::LibraryUnitTaken& obj)
{
	std::string type;
	if (!std::getline(is, type))
		throw std::runtime_error("Stream failed reading type");

	LibraryUnit* pointer = nullptr;

	if (type == "Book")
	{
		Book* newBook = new Book();
		if (!(is >> *newBook))
		{
			delete newBook;
			throw std::runtime_error("Stream failed reading Book");
		}
		pointer = newBook;
	}
	else if (type == "Periodical")
	{
		Periodical* newPer = new Periodical();
		if (!(is >> *newPer))
		{
			delete newPer;
			throw std::runtime_error("Stream failed reading Periodical");
		}
		pointer = newPer;
	}
	else if (type == "Series")
	{
		Series* series = new Series();
		if (!(is >> *series))
		{
			delete series;
			throw std::runtime_error("Stream failed reading Series");
		}
		pointer = series;
	}
	else
	{
		throw std::invalid_argument("Unknown LibraryUnit type: " + type);
	}

	Date borDate, retDate;
	if (!(is >> borDate >> retDate))
	{
		delete pointer;
		throw std::runtime_error("Stream failed reading dates");
	}

	if (borDate > retDate)
	{
		delete pointer;
		throw std::logic_error("Cannot return a book before taking it.");
	}

	delete obj.unit;
	obj.unit = pointer;
	obj.borrowDate = borDate;
	obj.returnDate = retDate;
	return is;
}

void Reader::print() const
{
	User::print();

	std::cout << '\n';

	for (size_t i = 0; i < takenUnits.size(); i++)
		takenUnits[i].print();
}

std::string Reader::getType() const
{
	return "Reader";
}

unsigned Reader::getPrintLines() const
{
	return User::getPrintLines() + 12;
}
