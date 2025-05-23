#pragma once
#include "LibraryUnit.h"
#include "Optional.h"

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

	private:

		std::string title;
		std::string author;
		StringArray keyWords;
	};

	Periodical() = default;
	Periodical(const std::string& title, const std::string& publisher, const std::string& genre, const std::string& description,
		unsigned short releaseYear, unsigned short rating, unsigned short month, const std::vector<Article>& articles,
		const std::string& issn = "");
	Periodical(const Periodical& other);
	Periodical& operator=(const Periodical& other);
	~Periodical() = default;

	const unsigned short getMonth() const;
	const std::vector<Article>& getArticles() const;
	const std::string getISSN() const;

	void setMonth(unsigned short newMonth);
	void setArticles(const std::vector<Article>& newArticles);
	void setISSN(const std::string& issn = generateNString(Periodical::ISSN_LENGTH));

	LibraryUnit* clone() const override;

private:

	unsigned short month;
	Optional<std::string> ISSN;
	std::vector<Article> articles;

	const static unsigned short ISSN_LENGTH;
};
