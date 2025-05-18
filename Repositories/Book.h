#pragma once
#include "LibraryUnit.h"
#include "Optional.h"

using StringArray = std::vector<std::string>;

class Book : LibraryUnit
{
public:

	Book() = delete;
	Book(const std::string& title, const std::string& publisher, const std::string& genre, const std::string& description,
		unsigned short releaseYear, unsigned short rating, const std::string& author, const std::string& isbn = "");
	Book(const Book& other);
	Book& operator=(const Book& other);
	~Book() = default;

	const std::string& getISBN() const;
	const std::string& getAuthor() const;
	const StringArray& getKeyWords() const;

	static std::string generateISBN();

	LibraryUnit* clone() const override;

	//Should the setters be private ( I feel like I shouldnt mendle in how a book will be handled )
	//I just have to give the possibility if needed
	void pushKeyWords();
	void setISBN(const std::string& str);
	void setAuthor(const std::string& name);

protected:

	Optional<std::string> ISBN; // should it has '-' betweeen numbers
	std::string author;
	StringArray keyWords; // treated as const

	const static unsigned short ISBN_LENGTH;

private:

	bool isDigit(const char& ch) const;
};
