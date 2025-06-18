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

		void print() const;

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
	std::vector<Article>& getArticles();
	const Optional<std::string>& getISSN() const;

	void setMonth(unsigned short newMonth);
	void setArticles(const std::vector<Article>& newArticles);
	void setISSN(const std::string& issn = generateNString(Periodical::ISSN_LENGTH));
	void addArticle(const Article& newArticle);

	LibraryUnit* clone() const override;

	void writeToBinary(std::ostream& os) const override;
	void readFromBinary(std::istream& is) override;

	virtual void serialise(std::ostream& os) const override;
	virtual void deserialize(std::istream& is) override;

	void print() const override;
	std::string getType() const override;
	unsigned getPrintLines() const override;

protected:

	unsigned short month;
	Optional<std::string> ISSN;
	std::vector<Article> articles;

	const static unsigned short ISSN_LENGTH;
};

bool operator==(const Periodical::Article& lhs, const Periodical::Article& rhs);
bool operator!=(const Periodical::Article& lhs, const Periodical::Article& rhs);
