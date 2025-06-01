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

	const std::string getISBN() const; // ?? Pokaji na Tedo
	const std::string& getAuthor() const;
	const StringArray& getKeyWords() const;

	LibraryUnit* clone() const override;

	//Should the setters be private ( I feel like I shouldnt mendle in how a book will be handled )
	//I just have to give the possibility if needed
	void pushKeyWords();
	void setISBN(const std::string& str = generateNString(Book::ISBN_LENGTH));
	void setAuthor(const std::string& name);

	//operator>> polymorf. called from LibraryUnit
	friend std::istream& operator>>(std::istream& is, Book& obj);

	void writeToBinary(std::ostream& os) const override;
	void readFromBinary(std::istream& is) override;

	void print(std::ostream& os) const override;

protected:

	Optional<std::string> ISBN;
	std::string author;
	StringArray keyWords;
	
	const static unsigned short ISBN_LENGTH;
};
