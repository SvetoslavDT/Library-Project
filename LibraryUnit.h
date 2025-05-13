#pragma once
#include <string>
#include <vector>

typedef std::vector<std::string> stringArray;

class LibraryUnit
{
public:

private:

	std::string title;
	std::string publisher;
	std::string genre;
	std::string briefDescription;
	const static unsigned short ISBN_LENGTH;
	short releaseYear;
	std::vector<unsigned short> isbn; // not necessary
	unsigned uniceNumber;
	static unsigned currentUniceNumber;
	double rating;
};