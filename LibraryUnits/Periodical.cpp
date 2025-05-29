#include "Periodical.h"
#include "LibraryUnit.h"
#include "Functions.h"
#include <stdexcept>
#include <cctype>

Periodical::Article::Article(const std::string& title, const std::string& author) : title(title), author(title) {}

const std::string Periodical::Article::getTitle() const
{
	return title;
}

const std::string Periodical::Article::getAuthor() const
{
	return author;
}

const StringArray Periodical::Article::getKeyWords() const
{
	return keyWords;
}

void Periodical::Article::setTitle(const std::string& newTitle)
{
	title = newTitle;
}

void Periodical::Article::setAuthor(const std::string& newAuthor)
{
	author = newAuthor;
}

void Periodical::Article::setKeyWords()
{
	keyWords.push_back(title);
	keyWords.push_back(author);
}

void Periodical::Article::writeToBinary(std::ostream& os) const
{
	FunctionsForBinary::writeString(os, title);
	FunctionsForBinary::writeString(os, author);
	FunctionsForBinary::writeStringArray(os, keyWords);
}

void Periodical::Article::readFromBinary(std::istream& is)
{
	title = FunctionsForBinary::readString(is);
	author = FunctionsForBinary::readString(is);
	keyWords = FunctionsForBinary::readStringArray(is);
}

Periodical::Periodical(const std::string& title, const std::string& publisher, const std::string& genre,
	const std::string& description, unsigned short releaseYear, unsigned short rating, unsigned short month,
	const std::vector<Article>& articles, const std::string& issn)
	: LibraryUnit(title, publisher, genre, description, releaseYear, rating), articles(articles)
{
	if(!issn.empty())
		setISSN(issn);
	setMonth(month);
}

Periodical::Periodical(const Periodical& other) : LibraryUnit(other), articles(other.articles)
{
	if (other.ISSN)
		ISSN.setValue(other.getISSN());
	setMonth(other.month);
}

Periodical& Periodical::operator=(const Periodical& other)
{
	if (this != &other)
	{
		LibraryUnit::operator=(other);
		setMonth(other.month);
	}
	return *this;
}

const unsigned short Periodical::getMonth() const
{
	return month;
}

const std::vector<Periodical::Article>& Periodical::getArticles() const
{
	return articles;
}

const std::string Periodical::getISSN() const // ?? Tova dobre li e
{
	try
	{
		return ISSN.getValue();
	}
	catch (const std::exception&)
	{
		return "";
	}
}

void Periodical::setMonth(unsigned short newMonth)
{
	if (newMonth < 0 || newMonth > 12)
		throw std::invalid_argument("Invalid month");
	month = newMonth;
}

void Periodical::setArticles(const std::vector<Article>& newArticles)
{
	articles = newArticles;
}

void Periodical::setISSN(const std::string& issn)
{
	if(issn.length() != Periodical::ISSN_LENGTH)
		throw std::invalid_argument("Given string is not in ISSN format");

	for (size_t i = 0; i < issn.length(); i++)
	{
		if (!isdigit(issn[i]))
			throw std::invalid_argument("Given string is not in ISSN format");
	}

	ISSN.setValue(issn);
}

LibraryUnit* Periodical::clone() const
{
	return new Periodical(*this);
}

std::ostream& operator<<(std::ostream& os, const Periodical::Article& obj)
{
	os << obj.title << '\n' << obj.author << '\n';
	os << obj.keyWords.size() << '\n';
	for (const std::string& kw : obj.keyWords)
		os << kw << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Periodical::Article& obj)
{
	is >> obj.title >> obj.author;

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

std::ostream& operator<<(std::ostream& os, const Periodical& obj)
{
	os << (const LibraryUnit&)obj;

	os << obj.month << '\n' << obj.ISSN << '\n';

	os << obj.articles.size() << '\n';
	for (size_t i = 0; i < obj.articles.size(); i++)
	{
		os << obj.articles[i]; // the op<< writes '\n\ after each iteration of the sycle
	}

	return os;
}

std::istream& operator>>(std::istream& is, Periodical& obj)
{
	is >> (LibraryUnit&)obj;

	is >> obj.month >> obj.ISSN;

	size_t articlesCount;
	std::string temp;
	is >> articlesCount;
	is.ignore();
	obj.articles.clear();
	for (size_t i = 0; i < articlesCount; ++i)
	{
		is >> obj.articles[i];
	}

	return is;
}

void Periodical::writeToBinary(std::ostream& os) const
{
	LibraryUnit::writeToBinary(os);

	os.write((const char*)&month, sizeof(month));
	ISSN.writeToBinary(os);

	size_t size = articles.size();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		articles[i].writeToBinary(os);
	}
}

void Periodical::readFromBinary(std::istream& is)
{
	LibraryUnit::readFromBinary(is);

	is.read((char*)&month, sizeof(month));
	ISSN.readFromFile(is);

	size_t size;
	is.read((char*)&size, sizeof(size));
	articles.clear();
	articles.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		articles[i].readFromBinary(is);
	}
}
