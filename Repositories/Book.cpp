#include "Book.h"
#include <stdexcept>

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
	if (other.ISBN)
		ISBN.setValue(other.ISBN.getValue());
	pushKeyWords();
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		Book::operator=(other);
		author = other.author;
		pushKeyWords();
		// Not changing the ISBN, so it stays unique
	}
	return *this;
}

const std::string& Book::getISBN() const
{
	return ISBN.getValue();
}

const std::string& Book::getAuthor() const
{
	return author;
}

const StringArray& Book::getKeyWords() const
{
	return keyWords;
}

std::string Book::generateISBN()
{
	return generateNString(Book::ISBN_LENGTH);
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
	if (str.length() != 13)
		throw std::invalid_argument("Given string is not in ISBN format");

	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isDigit(str[i]))
			throw std::invalid_argument("Given string is not in ISBN format");
	}

	ISBN.setValue(str);
}

void Book::setAuthor(const std::string& name)
{
	author = name;
}

bool Book::isDigit(const char& ch) const
{
	return ch >= '0' && ch <= '9';
}
