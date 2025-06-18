#include "CommandAddUser.h"

void CommandAddUser::execute(System& sys, const std::vector<std::string>& tokens) const
{
	std::vector<User*>& users = sys.getUserRepository().getUsers();

	bool administrator = false;
	if (tokens.size() == 6 && tokens[4] == "admin")
		administrator = true;

	for (size_t i = 0; i < users.size(); ++i)
	{
		if (users[i]->getName() == tokens[2])
		{
			std::cout << "Name already taken." << std::endl;
			return;
		}
		if (administrator)
		{
			if (Administrator* ptr = dynamic_cast<Administrator*>(users[i]))
			{
				if (ptr->getEmail() == tokens[5])
				{
					std::cout << "Email already is used." << std::endl;
					return;
				}
			}
		}
	}

	User* newUser = nullptr;

	try
	{
		if (administrator)
		{
			newUser = new Administrator(tokens[2], tokens[3], tokens[5]);
			sys.getAdminsCount()++;
		}
		else
			newUser = new Reader(tokens[2], tokens[3]);

		users.push_back(newUser);
		std::cout << "User added successfully." << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return;
	}
}
