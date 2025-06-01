#pragma once
#include "LibraryUnit.h"
#include "Optional.h"
#include "Functions.h"

using StringArray = std::vector<std::string>;

class Periodical : public virtual LibraryUnit
{
public:

	class Article
	{
	public:

		Article() = default;
		Article(const std::string& title, const std::string& author);

		const std::string getTitle() const;
		const std::string getAuthor() const;
		const StringArray getKeyWords() const;

		void setTitle(const std::string& newTitle);
		void setAuthor(const std::string& newAuthor);
		void setKeyWords();

		friend std::ostream& operator<<(std::ostream& os, const Article& obj);
		friend std::istream& operator>>(std::istream& is, Article& obj);

		void writeToBinary(std::ostream& os) const;
		void readFromBinary(std::istream& is);

	private:

		std::string title;
		std::string author;
		StringArray keyWords;
	};

	Periodical() = default;
	Periodical(const std::string& title, const std::string& publisher, const std::string& genre, const std::string& description,
		unsigned short releaseYear, unsigned short rating, unsigned short month, const std::vector<Article>& articles,
		const std::string& issn = "");

	const unsigned short getMonth() const;
	const std::vector<Article>& getArticles() const;
	const std::string getISSN() const;

	void setMonth(unsigned short newMonth);
	void setArticles(const std::vector<Article>& newArticles);
	void setISSN(const std::string& issn = generateNString(Periodical::ISSN_LENGTH));

	LibraryUnit* clone() const override;

	//operator>> polymorf. called from LibraryUnit
	friend std::istream& operator>>(std::istream& is, Periodical& obj);

	void writeToBinary(std::ostream& os) const override;
	void readFromBinary(std::istream& is) override;

	void print(std::ostream& os) const override;

	const static unsigned short ISSN_LENGTH;

protected:

	unsigned short month;
	Optional<std::string> ISSN;
	std::vector<Article> articles;
};
