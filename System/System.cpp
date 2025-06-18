#include "System.h"
#include "Command.h"
#include "CommandFactory.h"
#include <cstring>

System& System::getSystem()
{
	static System theSystem;
	return theSystem;
}

void System::setLoggedUser(User* user)
{
	if (!user)
		typeOfUser = TypeOfUser::DEFAULT;
	else if (strcmp(user->getType().data(), "Reader") == 0)
		typeOfUser = TypeOfUser::READER;
	else if (strcmp(user->getType().data(), "Administrator") == 0)
		typeOfUser = TypeOfUser::ADMIN;
	else
		throw std::logic_error("Unregistered type of user!");

	loggedUser = user;
}

void System::setRunSystem(bool boolean)
{
	runSystem = boolean;
}

void System::setBadEntry(bool boolean)
{
	badEntry = boolean;
}

void System::setTypeOfUser(TypeOfUser type)
{
	typeOfUser = type;
}

void System::setAdminsCount(size_t count)
{
	userRepo.getAdminsCount() = count;
}

void System::exitSystem()
{
	runSystem = false;
}

System::System()
{
	userRepo.readToEndAllFiles();
	adminsCount = userRepo.getAdminsCount();

	if (!adminsCount)
	{
		Administrator* newAdmin = new Administrator("admin", "i<3c++", "user@abv.bg");
		userRepo.getUsers().push_back(newAdmin);
		loggedUser = newAdmin;
		typeOfUser = TypeOfUser::ADMIN;
		adminsCount++;
	}
}

void System::run()
{
	while (runSystem)
	{
		try
		{
			std::string input;
			std::getline(std::cin, input);

			if (input.empty())
				continue;

			std::vector<std::string> tokens = tokenizeString(input);

			Command* cmd = CommandFactory::getFactory().create(*this, tokens);

			if(cmd)
			{
				cmd->execute(*this, tokens);
				delete cmd;
			}
		}
		catch (const std::ios_base::failure& ex)
		{
			std::ofstream log("stream_errors.txt", std::ios::app);
			if(log)
				log << "[" << Date{} << "] Stream error: "<< ex.what() << std::endl;

		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		catch (...) // Should't come to this
		{
			std::cout << "Unknow exception occured." << std::endl;
		}
		std::cout << std::endl;
	}
}

UserRepository& System::getUserRepository()
{
	return userRepo;
}

LibraryUnitRepository& System::getLibraryUnitRepository()
{
	return libRepo;
}

const bool System::getRunSystem() const
{
	return runSystem;
}

const bool System::getBadEntry() const
{
	return badEntry;
}

const User* System::getLoggedUser() const
{
	return loggedUser;
}

User* System::getLoggedUser()
{
	return loggedUser;
}

const System::TypeOfUser System::getTypeOfUser() const
{
	return typeOfUser;
}

const size_t System::getAdminsCount() const
{
	return userRepo.getAdminsCount();
}

size_t& System::getAdminsCount()
{
	return adminsCount;
}
