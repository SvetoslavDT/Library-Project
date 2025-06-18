#include "Command.h"

unsigned short Command::MAX_PRINTABLE_LINES = 50;

bool Command::printAllSingleLibraryUnit(std::vector<LibraryUnit*>& units, const std::string& str, size_t& sum) const
{
	if (units.size() > 1)
		std::cout << std::endl;

	for (size_t i = 0; i < units.size(); i++)
	{
		if (units[i]->getType() != str)
			continue;

		if (sum + units[i]->getPrintLines() < Command::MAX_PRINTABLE_LINES)
		{
			sum += units[i]->getPrintLines();
			units[i]->print();
			if(i != units.size() - 1)
				std::cout << std::endl;
		}
		else
		{
			std::string answer;
			do
			{
				std::cout << "Would you like to see more results : yes / no" << std::endl;
				std::getline(std::cin, answer);
				if (answer == "yes")
				{
					std::cout << std::endl;
					units[i]->print();
					if (i != units.size() - 1)
						std::cout << std::endl;
					sum = units[i]->getPrintLines();
					break;
				}
				else if (answer == "no")
				{
					return true;
				}
				else
					std::cout << "Please type 'yes' or 'no'." << std::endl;
			} while (true);
		}
	}

	return false;
}

void Command::printUsers(const std::vector<User*>& users) const
{
	for (size_t i = 0, sum = 0; i < users.size(); ++i)
	{
		if (sum + users[i]->getPrintLines() < Command::MAX_PRINTABLE_LINES)
		{
			sum += users[i]->getPrintLines();
			users[i]->print();
		}
		else
		{
			std::string answer;
			do
			{
				std::cout << "Would you like to see more results : yes / no" << std::endl;
				std::getline(std::cin, answer);
				if (answer == "yes")
				{
					users[i]->print();
					sum = users[i]->getPrintLines();
					break;
				}
				else if (answer == "no")
					return;
				else
					std::cout << "Please type 'yes' or 'no'." << std::endl;
			} while (true);
		}
	}
}

void Command::setMaxPrintableLines(unsigned short newMaxPrintableLines)
{
	MAX_PRINTABLE_LINES = newMaxPrintableLines;
}

bool Command::checkIfTokenIsNumber(const std::string token) const
{
	if (token.empty())
		return false;

	for (const char& c : token)
	{
		if (!std::isdigit(static_cast<unsigned char>(c)))
			return false;
	}

	return true;
}