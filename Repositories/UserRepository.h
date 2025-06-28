#pragma once
#include <fstream>
#include "User.h"
#include "Reader.h"
#include "Administrator.h"

class UserRepository
{
public:

	UserRepository();
	UserRepository(const UserRepository& other) = delete;
	UserRepository& operator=(const UserRepository& other) = delete;
	~UserRepository();

	const std::vector<User*>& getUsers() const;
	std::vector<User*>& getUsers();
	const size_t getAdminsCount() const;
	size_t& getAdminsCount();

	void writeAllToFiles();
	void readToEndAllFiles();
	void readAllReaders();

	User* readUntilFindUser(const std::string& name);

private:

	void closeAllStreams();
	size_t readAllFromFile(std::fstream& stream, const char* fileName);
	void openStream(std::fstream& stream, const char* fileName);

	size_t adminsCount = 0;

	const char readersFile[20] = "readers.dat";
	const char administratorsFile[20] = "administrators.dat";

	std::fstream readersStream;
	std::fstream administratorsStream;

	std::vector<User*> users;
};
