#pragma once
#include "UserRepository.h"
#include "LibraryUnitRepository.h"

class System
{
public:

	enum class TypeOfUser : unsigned char
	{
		READER, ADMIN, DEFAULT
	};

	static System& getSystem();

	void run();

	UserRepository& getUserRepository();
	LibraryUnitRepository& getLibraryUnitRepository();
	const bool getRunSystem() const;
	const bool getBadEntry() const;
	const User* getLoggedUser() const;
	User* getLoggedUser();
	const TypeOfUser getTypeOfUser() const;
	const size_t getAdminsCount() const;
	size_t& getAdminsCount();

	void setLoggedUser(User* user);
	void setRunSystem(bool boolean);
	void setBadEntry(bool boolean);
	void setTypeOfUser(TypeOfUser type);
	void setAdminsCount(size_t count);

	void exitSystem();

private:

	System();
	~System() = default;
	System(const System& other) = delete;
	System& operator=(const System& other) = delete;

private:

	LibraryUnitRepository libRepo;
	UserRepository userRepo;

	User* loggedUser = nullptr;
	size_t adminsCount = 0;
	TypeOfUser typeOfUser = TypeOfUser::DEFAULT;

	bool runSystem = true;
	bool badEntry = false;

};
