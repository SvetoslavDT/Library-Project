#pragma once
#include "LibraryUnit.h"
#include "Optional.h"
#include "Functions.h"

class Book : public virtual LibraryUnit
{
public:

	Book() = default;
	Book(const std::string& title, const std::string& publisher, const std::string& genre, const std::string& description,
		unsigned short releaseYear, unsigned short rating, const std::string& author, const std::string& isbn = "");
	Book(const Book& other);
	Book& operator=(const Book& other);

	const Optional<std::string>& getISBN() const;
	const std::string& getAuthor() const;
	const StringArray& getKeyWords() const;

	LibraryUnit* clone() const override;

	void pushKeyWords();
	void setISBN(const std::string& str = generateNString(Book::ISBN_LENGTH));
	void setAuthor(const std::string& name);

	void writeToBinary(std::ostream& os) const override;
	void readFromBinary(std::istream& is) override;

	virtual void serialise(std::ostream& os) const override;
	virtual void deserialize(std::istream& is) override;

	void print() const override;
	std::string getType() const override;
	unsigned getPrintLines() const override;

protected:

	Optional<std::string> ISBN;
	std::string author;
	StringArray keyWords;
	
	const static unsigned short ISBN_LENGTH;
};
