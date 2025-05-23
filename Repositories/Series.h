#pragma once
#include "Book.h"
#include "Periodical.h"

class Series : public Book, public Periodical
{
public:

	Series();
	Series(const std::string& title, const std::string& publisher, const std::string& genre,
		const std::string& description, unsigned short releaseYear, unsigned short rating,
		const std::string& author, const std::string& isbn = "", unsigned short month,
		const std::vector<Article>& articles, const std::string& issn = "");
	Series(const Series& other);
	Series& operator=(const Series& other);
	~Series() = default;

	LibraryUnit* clone() const override;

};
