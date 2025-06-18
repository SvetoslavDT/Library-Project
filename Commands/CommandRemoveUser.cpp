#include "CommandRemoveUser.h"

void CommandRemoveUser::execute(System& sys, const std::vector<std::string>& tokens) const
{
	std::vector<User*>& users = sys.getUserRepository().getUsers();
	User* user = nullptr;

	size_t i = 0;
	for (; i < users.size(); ++i)
	{
		if (users[i]->getName() == tokens[2])
		{
			user = users[i];
			break;
		}
	}

	if (!user)
	{
		user = sys.getUserRepository().readUntilFindUser(tokens[2]);
	}

	if (user)
	{
		if (sys.getAdminsCount() <= 1 && user->getType() == "Administrator")
		{
			std::cout << "Can't remove the last admin. Removing denied." << std::endl;
			return;
		}

		if (Reader* ptr = dynamic_cast<Reader*>(user))
		{
			if (ptr->getTakenUnits().size() != 0)
			{
				std::string tmp;
				do
				{
					std::cout << "Reader has some taken units. Do wish to remove them from the library [yes/no]?" << std::endl;
					std::getline(std::cin, tmp);
					if (tmp == "yes")
					{
						removeBooksFromReader(sys.getLibraryUnitRepository().getUnits(), ptr->getTakenUnits());
						break;
					}
					else if (tmp == "no")
					{
						std::cout << "User was not removed due to possession of library units." << std::endl;
						return;
					}
				} while (true);
			}	
		}

		if (i != users.size() - 1)
		{
			std::swap(users[i], users[users.size() - 1]);
		}

		if (users[users.size() - 1] == sys.getLoggedUser())
			sys.setLoggedUser(nullptr);

		delete users[users.size() - 1];
		users.pop_back();

		std::cout << "User removed successfully." << std::endl;
	}
	else
	{
		std::cout << "No user found with this name." << std::endl;
	}
}

void CommandRemoveUser::removeBooksFromReader(std::vector<LibraryUnit*>& units, std::vector<Reader::LibraryUnitTaken>& takenUnits) const
{
	for (LibraryUnit* u : units)
	{
		unsigned targetId = u->getUniqueNumber();

		for (int j = takenUnits.size() - 1; j >= 0; --j)
		{
			if (takenUnits[j].getUnit()->getUniqueNumber() == targetId)
			{
				takenUnits.erase(takenUnits.begin() + j);
			}
		}
	}
}