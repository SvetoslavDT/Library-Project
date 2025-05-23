#include "Periodical.h"
#include "LibraryUnit.h"
#include <stdexcept>

Periodical::Article::Article(const std::string& title, const std::string& author) : title(title), author(title) ,{}

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
		if (!isDigit(issn[i]))
			throw std::invalid_argument("Given string is not in ISSN format");
	}

	ISSN.setValue(issn);
}

LibraryUnit* Periodical::clone() const
{
	return new Periodical(*this);
}
