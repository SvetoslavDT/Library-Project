#include "UserRepository.h"
#include <cstring>

UserRepository::UserRepository()
{
	users.reserve(16); // Allocate space for N users

	readersStream.exceptions(std::ios::badbit);
	administratorsStream.exceptions(std::ios::badbit);

	openStream(readersStream, readersFile);
	openStream(administratorsStream, administratorsFile);

	adminsCount = readAllFromFile(administratorsStream, administratorsFile);
}

UserRepository::~UserRepository()
{
	readersStream.exceptions(std::ios::goodbit);
	administratorsStream.exceptions(std::ios::goodbit);

	readToEndAllFiles();

	closeAllStreams();

	std::ofstream ofs(readersFile, std::ios::binary | std::ios::trunc);
	ofs.close();

	std::ofstream ofs1(administratorsFile, std::ios::binary | std::ios::trunc);
	ofs1.close();

	readersStream.open(readersFile, std::ios::binary | std::ios::in | std::ios::out);
	administratorsStream.open(administratorsFile, std::ios::binary | std::ios::in | std::ios::out);

	writeAllToFiles();

	closeAllStreams();

	for (auto ptr : users)
		delete ptr;
}

const std::vector<User*>& UserRepository::getUsers() const
{
	return users;
}

std::vector<User*>& UserRepository::getUsers()
{
	return users;
}

const size_t UserRepository::getAdminsCount() const
{
	return adminsCount;
}

size_t& UserRepository::getAdminsCount()
{
	return adminsCount;
}

void UserRepository::writeAllToFiles()
{
	readersStream.seekp(0, std::ios::beg);
	administratorsStream.seekp(0, std::ios::beg);

	for (User* u : users)
	{
		if (strcmp(u->getType().data(), "Reader") == 0)
		{
			u->writeToBinary(readersStream);
		}
		else if (strcmp(u->getType().data(), "Administrator") == 0)
		{
			u->writeToBinary(administratorsStream);
		}
		else
			throw std::logic_error("Unregistered type"); // There won't be a case in which this line is called
	}
}

void UserRepository::readToEndAllFiles()
{
	readAllFromFile(readersStream, readersFile);
}

void UserRepository::readAllReaders()
{
	readAllFromFile(readersStream, readersFile);
}

User* UserRepository::readUntilFindUser(const std::string& name)
{
	while (readersStream.peek() != EOF)
	{
		Reader* reader = new Reader();
		reader->readFromBinary(readersStream);
		users.push_back(reader);

		if (reader->getName() == name)
			return reader;
	}

	return nullptr;
}

void UserRepository::closeAllStreams()
{
	if (readersStream.is_open())
		readersStream.close();
	if (administratorsStream.is_open())
		administratorsStream.close();
}

size_t UserRepository::readAllFromFile(std::fstream& stream, const char* fileName)
{
	if (strcmp(fileName, readersFile) == 0)
	{
		while (stream.peek() != EOF)
		{
			Reader* reader = new Reader();
			reader->readFromBinary(stream);
			users.push_back(reader);
		}
	}
	else if (strcmp(fileName, administratorsFile) == 0)
	{
		size_t count = 0;
		while (stream.peek() != EOF)
		{
			++count;
			Administrator* adm = new Administrator();
			adm->readFromBinary(stream);
			users.push_back(adm);
		}

		return count;
	}
	else
		return 0;

	return 0;
}

void UserRepository::openStream(std::fstream& stream, const char* fileName)
{
	std::ofstream tmp(fileName, std::ios::binary | std::ios::app);

	stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
}