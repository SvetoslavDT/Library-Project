#pragma once
#include <iostream>
#include <string>
#include <vector>

using StringArray = std::vector<std::string>;

class LibraryUnit
{
public:

	LibraryUnit() = default;
	LibraryUnit(const std::string& title, const std::string& publisher, const std::string& genre,
		const std::string& description, unsigned short releaseYear, unsigned short rating);
	virtual ~LibraryUnit() = default;

	const std::string& getTitle() const;
	const std::string& getPublisher() const;
	const std::string& getGenre() const;
	const std::string& getBriefDescription() const;
	const unsigned short getReleaseYear() const;
	const unsigned short getRating() const;
	const unsigned getUniqueNumber() const;
	
	const unsigned short getCopies() const;
	unsigned short& getCopies();
	const unsigned short getTaken() const;
	unsigned short& getTaken();

	void setTitle(const std::string& str);
	void setPublisher(const std::string& str);
	void setGenre(const std::string& str);
	void setBriefDescription(const std::string& str);
	void setReleaseYear(unsigned short year);
	void setRating(unsigned short rating);
	void setUniqueNumber();

	virtual LibraryUnit* clone() const = 0;

	friend std::ostream& operator<<(std::ostream& os, const LibraryUnit& obj);
	friend std::istream& operator>>(std::istream& is, LibraryUnit& obj);

	LibraryUnit& operator++(); // Used for incrementing copies
	LibraryUnit& operator--(); // Used for decrementing copies
	// No post increment/decrement operators because class is abstract

	virtual void writeToBinary(std::ostream& os) const = 0;
	virtual void readFromBinary(std::istream& is) = 0;

	virtual void serialise(std::ostream& os) const = 0;
	virtual void deserialize(std::istream& is) = 0;

	virtual void print() const = 0;
	virtual std::string getType() const = 0;
	virtual unsigned getPrintLines() const = 0;

protected:

	std::string title;
	std::string publisher;
	std::string genre; // Did't make it enum, beacuse 26 genres seems a bit too much
	std::string description;
	unsigned short releaseYear;
	unsigned short rating;
	unsigned uniqueNumber;

	unsigned short copies = 1;
	unsigned short taken = 0;
};
