#pragma once
#include "LibraryUnit.h"
#include <iostream>
#include <fstream>

class LibraryUnitRepository
{
public:

	LibraryUnitRepository();
	LibraryUnitRepository(const LibraryUnitRepository& other) = delete;
	LibraryUnitRepository& operator=(const LibraryUnitRepository& other) = delete;
	~LibraryUnitRepository();

	std::vector<LibraryUnit*>& getUnits();
	const std::vector<LibraryUnit*>& getUnits() const;

	size_t readUntilFindByUniqueNumber(unsigned num);

	void readAllBooks();
	void readAllPeriodicals();
	void readAllSeries();

	void readToEndAllFiles();
	void writeAllToFiles();

private:

	void readAllFromFile(std::fstream& stream, const char* fileName);

	void openStream(std::fstream& stream, const char* fileName);
	void closeAllStreams();

	const char booksFile[20]	   = "books.dat";
	const char periodicalsFile[20] = "periodical.dat";
	const char seriesFile[20]	   = "series.dat";

	std::vector<LibraryUnit*> units;

	std::fstream booksStream;
	std::fstream periodicalsStream;
	std::fstream seriesStream;
};
