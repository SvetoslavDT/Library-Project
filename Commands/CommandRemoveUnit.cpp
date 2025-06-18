#include "CommandRemoveUnit.h"

void CommandRemoveUnit::execute(System& sys, const std::vector<std::string>& tokens) const
{
	if (atol(tokens[2].data()) <= 0)
	{
		std::cout << "Invalid id number." << std::endl;
		return;
	}

	std::vector<LibraryUnit*>& units = sys.getLibraryUnitRepository().getUnits();
	bool done = false;

	for (size_t i = 0; i < units.size(); i++)
	{
		if (std::to_string(units[i]->getUniqueNumber()) == tokens[2])
		{
			removeFromUsers(sys, atol(tokens[2].data()));

			if (i != units.size() - 1)
				std::swap(units[i], units[units.size() - 1]);

			delete units[units.size() - 1];
			units.pop_back();

			done = true;
			break;
		}
	}

	if (!done && sys.getLibraryUnitRepository().readUntilFindByUniqueNumber(atol(tokens[2].data())))
	{
		removeFromUsers(sys, atol(tokens[2].data()));

		delete units[units.size() - 1];
		units.pop_back();

		done = true;
	}

	if (done)
	{
		std::cout << "Unit removed successfully." << std::endl;
	}
	else
		std::cout << "No unit matches the number." << std::endl;
}

void CommandRemoveUnit::removeUnit(std::vector<LibraryUnit*>& units, LibraryUnit* toDelete, size_t i) const
{
	if (i != units.size() - 1)
		std::swap(units[i], units[units.size() - 1]);

	delete units[units.size() - 1];
	units.pop_back();
}

void CommandRemoveUnit::removeFromUsers(System& sys, unsigned num) const
{
	sys.getUserRepository().readAllReaders();
	auto& users = sys.getUserRepository().getUsers();

	for (User* u : users)
	{
		if (Reader* reader = dynamic_cast<Reader*>(u))
		{
			auto& units = reader->getTakenUnits();

			for (int i = units.size() - 1; i >= 0; --i)
			{
				if (units[i].getUnit()->getUniqueNumber() == num)
				{
					units.erase(units.begin() + i);
				}
			}
		}
	}
}