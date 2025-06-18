#include "CommandChangeUser.h"

void CommandChangeUser::execute(System& sys, const std::vector<std::string>& tokens) const
{
	if (tokens.size() == 3)
	{
		if (sys.getLoggedUser()->getType() == "Administrator")
		{
			std::vector<User*>& users = sys.getUserRepository().getUsers();
			User* user = nullptr;

			for (User* u : users)
			{
				if (u->getName() == tokens[2])
				{
					user = u;
					break;
				}
			}

			if (!user)
				user = sys.getUserRepository().readUntilFindUser(tokens[2]);

			if (user)
			{
				std::string tmp;
				std::cout << "Please write new password: ";
				std::getline(std::cin, tmp);
				user->setPassword(tmp);
				std::cout << "Password changed successfully." << std::endl;
				return;
			}
			else
			{
				std::cout << "No found user with that name." << std::endl;
				return;
			}
		}
		else
		{
			std::cout << "Can not change password of " << tokens[2] << ", you don't have admin rights." << std::endl;
			return;
		}
	}
	else
	{
		if (sys.getLoggedUser())
		{
			std::string tmp;
			std::cout << "Please write new password: ";
			std::getline(std::cin, tmp);
			sys.getLoggedUser()->setPassword(tmp);
			std::cout << "Password changed successfully." << std::endl;
			return;
		}
		else
		{
			std::cout << "There is no logged user." << std::endl;
		}
	}
}