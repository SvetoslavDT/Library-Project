#include "Book.h"
#include "Functions.h"
#include <stdexcept>
#include <cctype>

const unsigned short Book::ISBN_LENGTH = 13;

Book::Book(const std::string& title, const std::string& publisher, const std::string& genre,
	const std::string& description, unsigned short releaseYear, unsigned short rating,
	const std::string& author, const std::string& isbn)
	: LibraryUnit(title, publisher, genre, description, releaseYear, rating), author(author) 
{
	if (!isbn.empty())
		setISBN(isbn);

	pushKeyWords();
}

Book::Book(const Book& other) : LibraryUnit(other), author(other.author)
{
	if (other.ISBN.hasValue())
	{
		ISBN.setValue(other.ISBN.getValue());
	}
	pushKeyWords();
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		LibraryUnit::operator=(other);
		author = other.author;
		pushKeyWords();
		if(other.ISBN.hasValue())
			ISBN.setValue(other.ISBN.getValue());
	}
	return *this;
}

const Optional<std::string>& Book::getISBN() const
{
	return ISBN;
}

const std::string& Book::getAuthor() const
{
	return author;
}

const StringArray& Book::getKeyWords() const
{
	return keyWords;
}

LibraryUnit* Book::clone() const
{
	return new Book(*this);
}

void Book::pushKeyWords()
{
	keyWords.push_back(title);
	keyWords.push_back(author);
	keyWords.push_back(std::to_string(getReleaseYear()));
}

void Book::setISBN(const std::string& str)
{
	if (str.length() != Book::ISBN_LENGTH)
		throw std::invalid_argument("Given string is not in ISBN format");
	
	for (size_t i = 0; i < str.length(); i++)
	{
		if(!isdigit(str[i]))
			throw std::invalid_argument("Given string is not in ISBN format");
	}
	
	ISBN.setValue(str);
}

void Book::setAuthor(const std::string& name)
{
	author = name;
}

void Book::writeToBinary(std::ostream& os) const
{
	LibraryUnit::writeToBinary(os);

	ISBN.writeToBinary(os);

	FunctionsForBinary::writeString(os, author);
	
	FunctionsForBinary::writeStringArray(os, keyWords);
}

void Book::readFromBinary(std::istream& is)
{
	Book tmp;

	tmp.LibraryUnit::readFromBinary(is);
	tmp.ISBN.readFromFile(is);
	tmp.author = FunctionsForBinary::readString(is);
	tmp.keyWords = FunctionsForBinary::readStringArray(is);

	*this = std::move(tmp);
}

void Book::serialise(std::ostream& os) const
{
	LibraryUnit::serialise(os);

	os << author << '\n' << ISBN << '\n';
}

void Book::deserialize(std::istream& is)
{
	LibraryUnit::deserialize(is);

	Optional<std::string> isbn;

	if(!(is >> isbn)) throw std::exception("Stream failed");

	is.ignore(64, '\n');

	std::string author;
	if(std::getline(is, author)) throw std::exception("Stream failed");

	setISBN(isbn.getValue());
	setAuthor(author);
	getKeyWords();
}

void Book::print() const
{
	LibraryUnit::print();

	std::cout << "Author - " << author << '\n';
	if (ISBN.hasValue())
	{		
		std::cout << "ISBN - ";

		for (size_t i = 0; i < ISBN.getValue().length(); ++i)
		{
			if (i == 3 || i == 5 || i == 10 || i == 12) // after these numbers an ISBN number contains '-'
				std::cout << '-';
			std::cout << ISBN.getValue()[i];
		}
		std::cout << '\n';
	}
}

std::string Book::getType() const
{
	return "Book";
}

unsigned Book::getPrintLines() const
{
	return 11;
}
