#pragma once
#include <string>
#include <vector>

class LibraryUnit
{
public:

	LibraryUnit() = delete;
	LibraryUnit(std::string title, std::string publisher, std::string genre, std::string description,
		unsigned short releaseYear, unsigned short rating);
	virtual ~LibraryUnit() = default;

	LibraryUnit(const LibraryUnit& other);
	LibraryUnit& operator=(const LibraryUnit& other);

	virtual LibraryUnit* clone() const = 0;

	const std::string& getTitle() const;
	const std::string& getPublisher() const;
	const std::string& getGenre() const;
	const std::string& getBriefDescription() const;
	const unsigned short getReleaseYear() const;
	const unsigned short getRating() const;
	const unsigned getUniqueNumber() const;

	void setTitle(const std::string& str);
	void setPublisher(const std::string& str);
	void setGenre(const std::string& str);
	void setBriefDescription(const std::string& str);
	void setReleaseYear(unsigned short year);
	void setRating(unsigned short rating);

protected:

	std::string title;
	std::string publisher;
	std::string genre; // Did't make it enum, beacuse 26 genres seems a bit too much
	std::string description;
	unsigned short releaseYear;
	unsigned short rating;
	unsigned uniqueNumber;

private:

	void copyFrom(const LibraryUnit& other);
};
