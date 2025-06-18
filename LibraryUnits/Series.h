#pragma once
#include "Book.h"
#include "Periodical.h"

class Series : public Book, public Periodical
{
public:

	Series() = default;
	Series(const std::string& title, const std::string& publisher, const std::string& genre,
		const std::string& description, unsigned short releaseYear, unsigned short rating,
		const std::string& author, unsigned short month, const std::vector<Article>& articles,
		const std::string& isbn = "", const std::string& issn = "");

	LibraryUnit* clone() const override;

	void writeToBinary(std::ostream& os) const override;
	void readFromBinary(std::istream& is) override;

	virtual void serialise(std::ostream& os) const override;
	virtual void deserialize(std::istream& is) override;

	void print() const override;
	std::string getType() const override;
	unsigned getPrintLines() const override;
};
