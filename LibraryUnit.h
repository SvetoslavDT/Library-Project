#pragma once
#include <string>
#include <vector>
//<cstdlib>

using StringArray = std::vector<std::string>;

class LibraryUnit
{
public:

	const std::string getTitle() const;
	const std::string getPublisher() const;
	const std::string getGenre() const;
	const std::string getBriefDescription() const;
	const short getReleaseYear() const;
	const unsigned getUniceNumber() const;
	const double getRating() const;

	void setTitle(const std::string& str);
	void setPublisher(const std::string& str);
	void setGenre(const std::string& str);
	void setBriefDescription(const std::string& str);
	void setReleaseYear(short year);
	void setRating(double rating);

	unsigned generateRandomNumber();

protected: // so there cant be LibraryUnit object

	LibraryUnit();
	LibraryUnit(std::string title, std::string publisher, std::string genre, std::string description,
		short releaseYear, double rating);
	~LibraryUnit();

	LibraryUnit(const LibraryUnit& other);
	LibraryUnit& operator=(const LibraryUnit& other);

protected:

	std::string title;
	std::string publisher;
	std::string genre; // Did't make it enum, beacuse 26 genres seems a bit too much
	std::string briefDescription;
	short releaseYear;
	const unsigned uniceNumber; // ?? should it be const
	double rating;
};
