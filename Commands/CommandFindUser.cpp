#include "CommandFindUser.h"

void CommandFindUser::execute(System& sys, const std::vector<std::string>& tokens) const
{
	sys.getUserRepository().readToEndAllFiles();

	std::vector<User*> result;
	result.reserve(8);

	if (findUsers(sys, tokens, result))
	{
		printUsers(result);
		return;
	}
	
	std::cout << "No users found." << std::endl;
}

bool CommandFindUser::findUsers(System& sys, const std::vector<std::string>& tokens, std::vector<User*>& result) const
{
	std::vector<User*>& users = sys.getUserRepository().getUsers();

	if (tokens[2] == "name")
	{
		for (size_t i = 0; i < users.size(); ++i)
		{
			if (users[i]->getName() == tokens[3])
				result.push_back(users[i]);
		}
	}
	else if (tokens[2] == "ID")
	{
		if (!checkIfTokenIsNumber(tokens[3]))
		{
			std::cout << "No number found after 'ID'" << std::endl;
			return false;
		}

		unsigned num = std::stoi(tokens[3]);

		for (size_t i = 0; i < users.size(); ++i)
		{
			if (Reader* ptr = dynamic_cast<Reader*>(users[i]))
			{
				for (const auto& unit : ptr->getTakenUnits())
				{
					if (unit.getUnit()->getUniqueNumber() == num)
						result.push_back(users[i]);
				}
			}
		}
	}
	else if (tokens[2] == "state")
	{
		const Date today;
		const Date oneMonthAgo = today - 1;
		const Date threeMonthsAgo = today - 3;

		if (tokens[3] == "overdue")
		{
			for (size_t i = 0; i < users.size(); ++i)
			{
				if (Reader* ptr = dynamic_cast<Reader*>(users[i]))
				{
					for (const auto& unit : ptr->getTakenUnits())
					{
						if (unit.getReturnDate() < today)
						{
							result.push_back(users[i]);
							break;
						}
					}
				}
			}
		}
		else if (tokens[3] == "reader")
		{
			size_t count = 0;

			for (size_t i = 0; i < users.size(); ++i)
			{
				if (Reader* ptr = dynamic_cast<Reader*>(users[i]))
				{
					count = 0;
					for (const auto& unit : ptr->getTakenUnits())
					{
						if (unit.getBorrowDate() >= oneMonthAgo)
							++count;

						if (count > 5)
						{
							result.push_back(users[i]);
							break;
						}
					}
				}
			}
		}
		else if (tokens[3] == "inactive")
		{
			for (size_t i = 0; i < users.size(); ++i)
			{
				if (Reader* ptr = dynamic_cast<Reader*>(users[i]))
				{
					for (const auto& unit : ptr->getTakenUnits())
					{
						if (unit.getBorrowDate() < threeMonthsAgo)
						{
							result.push_back(users[i]);
							break;
						}
					}
				}
			}
		}
		else
		{
			std::cout << "Unrecognised command." << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Unrecognised command." << std::endl;
		return false;
	}

	if (result.empty())
		std::cout << "No results found." << std::endl;

	return true;
}
