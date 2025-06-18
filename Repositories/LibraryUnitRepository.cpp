#include "LibraryUnitRepository.h"
#include "Book.h"
#include "Periodical.h"
#include "Series.h"
#include <cstring>

LibraryUnitRepository::LibraryUnitRepository()
{
	units.reserve(512); // Allocate space for N library units

	booksStream.exceptions(std::ios::badbit);
	periodicalsStream.exceptions(std::ios::badbit);
	seriesStream.exceptions(std::ios::badbit);

	openStream(booksStream, booksFile);
	openStream(periodicalsStream, periodicalsFile);
	openStream(seriesStream, seriesFile);
}

LibraryUnitRepository::~LibraryUnitRepository()
{
	booksStream.exceptions(std::ios::goodbit);
	periodicalsStream.exceptions(std::ios::goodbit);
	seriesStream.exceptions(std::ios::goodbit);

	readToEndAllFiles();

	closeAllStreams();


	std::ofstream ofs1(booksFile, std::ios::binary | std::ios::trunc);
	ofs1.close();

	std::ofstream ofs2(periodicalsFile, std::ios::binary | std::ios::trunc);
	ofs2.close();

	std::ofstream ofs3(seriesFile, std::ios::binary | std::ios::trunc);
	ofs3.close();

	booksStream.open(booksFile, std::ios::binary | std::ios::in | std::ios::out);
	periodicalsStream.open(periodicalsFile, std::ios::binary | std::ios::in | std::ios::out);
	seriesStream.open(seriesFile, std::ios::binary | std::ios::in | std::ios::out);

	writeAllToFiles();

	closeAllStreams();


	for (auto ptr : units)
		delete ptr;

	units.clear(); // No need though
}

std::vector<LibraryUnit*>& LibraryUnitRepository::getUnits()
{
	return units;
}

const std::vector<LibraryUnit*>& LibraryUnitRepository::getUnits() const
{
	return units;
}

size_t LibraryUnitRepository::readUntilFindByUniqueNumber(unsigned num)
{
	while (booksStream.peek() != EOF)
	{
		Book* book = new Book();
		book->readFromBinary(booksStream);
		units.push_back(book);

		if (book->getUniqueNumber() == num)
			return units.size() - 1;
	}

	while (periodicalsStream.peek() != EOF)
	{
		Periodical* periodical = new Periodical();
		periodical->readFromBinary(periodicalsStream);
		units.push_back(periodical);

		if (periodical->getUniqueNumber() == num)
			return units.size() - 1;
	}

	while (seriesStream.peek() != EOF)
	{
		Series* series = new Series();
		series->readFromBinary(seriesStream);
		units.push_back(series);

		if (series->getUniqueNumber() == num)
			return units.size() - 1;
	}

	return 0;
}

void LibraryUnitRepository::readAllBooks()
{
	readAllFromFile(booksStream, booksFile);
}

void LibraryUnitRepository::readAllPeriodicals()
{
	readAllFromFile(periodicalsStream, periodicalsFile);
}

void LibraryUnitRepository::readAllSeries()
{
	readAllFromFile(seriesStream, seriesFile);
}

void LibraryUnitRepository::readToEndAllFiles()
{
	readAllBooks();
	readAllPeriodicals();
	readAllSeries();
}

void LibraryUnitRepository::writeAllToFiles()
{
	booksStream.seekp(0, std::ios::beg);
	periodicalsStream.seekp(0, std::ios::beg);
	seriesStream.seekp(0, std::ios::beg);

	for (LibraryUnit* u : units)
	{
		if (strcmp(u->getType().data(), "Book") == 0)
		{
			u->writeToBinary(booksStream);
		}
		else if (strcmp(u->getType().data(), "Periodical") == 0)
		{
			u->writeToBinary(periodicalsStream);
		}
		else if (strcmp(u->getType().data(), "Series") == 0)
		{
			u->writeToBinary(seriesStream);
		}
		else
			throw std::logic_error("Unregistered type"); // There won't be a case in which this line is called
	}
}

void LibraryUnitRepository::readAllFromFile(std::fstream& stream, const char* fileName)
{
	if (strcmp(fileName, booksFile) == 0)
	{
		while (stream.peek() != EOF)
		{
			Book* book = new Book();
			book->readFromBinary(stream);
			units.push_back(book);
		}
	}
	else if (strcmp(fileName, periodicalsFile) == 0)
	{
		while (stream.peek() != EOF)
		{
			Periodical* per = new Periodical();
			per->readFromBinary(stream);
			units.push_back(per);
		}
	}
	else if (strcmp(fileName, seriesFile) == 0)
	{
		while (stream.peek() != EOF)
		{
			Series* ser = new Series();
			ser->readFromBinary(stream);
			units.push_back(ser);
		}
	}
}

void LibraryUnitRepository::openStream(std::fstream& stream, const char* fileName)
{
	std::ofstream tmp(fileName, std::ios::binary | std::ios::app);
	
	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
	stream.seekg(0);
	stream.seekp(0);
}

void LibraryUnitRepository::closeAllStreams()
{
	if (booksStream.is_open())
		booksStream.close();
	if (periodicalsStream.is_open())
		periodicalsStream.close();
	if (seriesStream.is_open())
		seriesStream.close();
}