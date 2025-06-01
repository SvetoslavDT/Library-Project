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

const std::string Book::getISBN() const // ?? Tova dobre li e
{
	try
	{
		return ISBN.getValue();
	}
	catch (const std::exception&)
	{
		return "";
	}
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
	keyWords.push_back(std::to_string(uniqueNumber));
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

std::istream& operator>>(std::istream& is, Book& obj)
{
	is >> (LibraryUnit&)obj;

	is >> obj.ISBN;
	std::getline(is, obj.author);

	size_t keyWordsCount;
	std::string tmp;
	is >> keyWordsCount;
	is.ignore();
	obj.keyWords.clear();
	for (size_t i = 0; i < keyWordsCount; ++i) 
	{
		std::getline(is, tmp);
		obj.keyWords.push_back(tmp);
	}

	return is;
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
	LibraryUnit::readFromBinary(is);

	ISBN.readFromFile(is);

	author = FunctionsForBinary::readString(is);

	keyWords = FunctionsForBinary::readStringArray(is);
}

void Book::print(std::ostream& os) const
{
	LibraryUnit::print(os);

	os << author << '\n' << ISBN;
}
