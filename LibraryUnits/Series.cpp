#include "Series.h"

Series::Series(const std::string& title, const std::string& publisher, const std::string& genre,
	const std::string& description, unsigned short releaseYear, unsigned short rating,
	const std::string& author, unsigned short month, const std::vector<Article>& articles,
	const std::string& isbn, const std::string& issn)
	: LibraryUnit(title, publisher, genre, description, releaseYear, rating),
	  Book(title, publisher, genre, description, releaseYear, rating, author, isbn),
	  Periodical(title, publisher, genre, description, releaseYear, rating, month, articles, issn) {}

LibraryUnit* Series::clone() const
{
	return new Series(*this);
}

void Series::writeToBinary(std::ostream& os) const
{
	LibraryUnit::writeToBinary(os);

	ISBN.writeToBinary(os);
	FunctionsForBinary::writeString(os, author);
	FunctionsForBinary::writeStringArray(os, keyWords);

	os.write(reinterpret_cast<const char*>(&month), sizeof(month));
	ISSN.writeToBinary(os);

	size_t count = articles.size();
	os.write(reinterpret_cast<const char*>(&count), sizeof(count));
	for (auto& art : articles)
		art.writeToBinary(os);
}

void Series::readFromBinary(std::istream& is)
{
	Series tmp; 

	tmp.LibraryUnit::readFromBinary(is);

	tmp.ISBN.readFromFile(is);
	tmp.author = FunctionsForBinary::readString(is);
	tmp.keyWords = FunctionsForBinary::readStringArray(is);

	unsigned short m;
	is.read((char*)&m, sizeof(m));
	tmp.month = m;

	tmp.ISSN.readFromFile(is);

	size_t count;
	is.read((char*)&count, sizeof(count));

	tmp.articles.clear();
	tmp.articles.reserve(count);
	for (size_t i = 0; i < count; ++i)
	{
		Article art;
		art.readFromBinary(is);
		tmp.articles.push_back(std::move(art));
	}

	*this = std::move(tmp);
}

void Series::serialise(std::ostream& os) const
{
	Book::serialise(os);

	os << month << '\n' << ISSN << '\n';
	os << articles.size() << '\n';
	for (size_t i = 0; i < articles.size(); i++)
	{
		os << articles[i];
		os << '\n';
	}
}

void Series::deserialize(std::istream& is)
{
	Book::deserialize(is);

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
		if (!(is >> newArticles[i])) throw std::exception("Stream failed");
	}

	setMonth(month);
	setISSN(issn.getValue());
	setArticles(newArticles);
}

void Series::print() const
{
	Book::print();

	std::cout << "Month - " << month << '\n';
	if (ISSN.hasValue())
	{
		for (size_t i = 0; i < ISSN.getValue().length(); i++)
		{
			if (i == 4)
				std::cout << '-';
			std::cout << ISSN.getValue()[i];
		}
		std::cout << '\n';
	}

	std::cout << '\n';

	for (size_t i = 0; i < articles.size(); i++)
	{
		std::cout << articles[i];
		if (i != articles.size() - 1)
			std::cout << '\n';
	}
}

std::string Series::getType() const
{
	return "Series";
}

unsigned Series::getPrintLines() const
{
	return Periodical::getPrintLines() + 2;
}
