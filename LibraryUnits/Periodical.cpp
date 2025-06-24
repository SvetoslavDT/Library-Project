#include "Periodical.h"
#include "LibraryUnit.h"
#include "Functions.h"
#include <stdexcept>
#include <cctype>

const unsigned short Periodical::ISSN_LENGTH = 8;

Periodical::Article::Article(const std::string& title, const std::string& author) : title(title), author(author) {}

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
	std::string tmpTitle = FunctionsForBinary::readString(is);
	std::string tmpAuthor = FunctionsForBinary::readString(is);
	StringArray tmpKeyWords = FunctionsForBinary::readStringArray(is);

	title = std::move(tmpTitle);
	author = std::move(tmpAuthor);
	keyWords = std::move(tmpKeyWords);
}

void Periodical::Article::print() const
{
	std::cout << "Title - " << title << '\n';
	std::cout << "Author - " << author << '\n';
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

const unsigned short Periodical::getMonth() const
{
	return month;
}

const std::vector<Periodical::Article>& Periodical::getArticles() const
{
	return articles;
}

std::vector<Periodical::Article>& Periodical::getArticles()
{
	return articles;
}

const Optional<std::string>& Periodical::getISSN() const
{
	return ISSN;
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

void Periodical::addArticle(const Article& newArticle)
{
	articles.push_back(newArticle);
}

LibraryUnit* Periodical::clone() const
{
	return new Periodical(*this);
}

std::ostream& operator<<(std::ostream& os, const Periodical::Article& obj)
{
	os << obj.title << '\n' << obj.author << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Periodical::Article& obj)
{
	std::string title;
	std::string author;

	if (!(std::getline(is, title))) throw std::exception("Stream failed");
	if (!(std::getline(is, author))) throw std::exception("Stream failed");

	obj.setTitle(title);
	obj.setAuthor(author);
	obj.setKeyWords();

	return is;
}

bool operator==(const Periodical::Article& lhs, const Periodical::Article& rhs)
{
	return lhs.getAuthor() == rhs.getAuthor() && lhs.getTitle() == rhs.getTitle();
}

bool operator!=(const Periodical::Article& lhs, const Periodical::Article& rhs)
{
	return !(lhs == rhs);
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

	unsigned short tmpMonth;
	is.read((char*)&tmpMonth, sizeof(tmpMonth));

	Optional<std::string> tmpIssn;
	tmpIssn.readFromFile(is);

	size_t count;
	is.read((char*)(&count), sizeof(count));

	std::vector<Article> tmpArticles;
	tmpArticles.reserve(count);
	for (size_t i = 0; i < count; ++i)
	{
		Article art;
		art.readFromBinary(is);
		tmpArticles.push_back(std::move(art));
	}

	month = tmpMonth;
	ISSN = tmpIssn;
	articles.swap(tmpArticles);
}

void Periodical::serialise(std::ostream& os) const
{
	LibraryUnit::serialise(os);

	os << month << '\n' << ISSN << '\n';

	os << articles.size() << '\n';
	for (size_t i = 0; i < articles.size(); i++)
	{
		os << articles[i];
		os << '\n';
	}
}

void Periodical::deserialize(std::istream& is)
{
	LibraryUnit::deserialize(is);

	unsigned short month;
	Optional<std::string> issn;

	if (!(is >> month)) throw std::exception("Stream failed");
	if (!(is >> issn)) throw std::exception("Stream failed");

	size_t articlesCount;
	std::string temp;
	is >> articlesCount;

	std::vector<Article> newArticles(articlesCount);

	for (size_t i = 0; i < articlesCount; ++i)
	{
		if(!(is >> newArticles[i])) throw std::exception("Stream failed");
	}

	setMonth(month);
	setISSN(issn.getValue());
	setArticles(newArticles);
}

void Periodical::print() const
{
	LibraryUnit::print();

	std::cout << "Month - " << month << '\n';
	if (ISSN.hasValue())
	{
		for (size_t i = 0; i < ISSN.getValue().length(); i++)
		{
			if (i == 4) // after this number an ISSN number contains '-'
				std::cout << '-';
			std::cout << ISSN.getValue()[i];
		}
		std::cout << '\n';
	}

	std::cout << '\n';

	for (size_t i = 0; i < articles.size(); i++)
	{
		articles[i].print();
		std::cout << '\n';
	}
}

std::string Periodical::getType() const
{
	return "Periodical";
}

unsigned Periodical::getPrintLines() const
{
	return 11 + articles.size() * 3;
}
