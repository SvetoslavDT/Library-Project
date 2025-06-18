#include "CommandLogin.h"

void CommandLogin::execute(System& sys, const std::vector<std::string>& tokens) const
{
	if (sys.getLoggedUser())
	{
		std::cout << "User already logged in the system." << std::endl;
		return;
	}

	if (sys.getBadEntry())
	{
		std::cout << "Too many incorrect logins, system will shut down." << std::endl;
		sys.setRunSystem(false);
		return;
	}

	std::vector<User*>& users = sys.getUserRepository().getUsers();
	std::string username, password;

	std::cout << "Username: ";
	std::getline(std::cin, username);

	std::cout << "Password: ";
	std::getline(std::cin, password);

	for (size_t i = 0; i < users.size(); ++i)
	{
		if (users[i]->getName() == username)
		{
			if(users[i]->getPassword() == password)
			{
				users[i]->setLastLogin();
				std::cout << "Welcome " << users[i]->getName() << std::endl;
				sys.setLoggedUser(users[i]);
			}
			else
			{
				std::cout << "Password is wrong." << std::endl;
				sys.setBadEntry(true);
			}

			return;
		}
	}

	User* user = sys.getUserRepository().readUntilFindUser(username);

	if (user)
	{
		if (user->getPassword() == password)
		{
			user->setLastLogin();
			std::cout << "Welcome " << user->getName() << std::endl;
			sys.setLoggedUser(user);
		}
		else
		{
			std::cout << "Password is wrong." << std::endl;
			sys.setBadEntry(true);
		}
		
		return;
	}

	std::cout << "Wrong username/password." << std::endl;
	sys.setBadEntry(true);
}