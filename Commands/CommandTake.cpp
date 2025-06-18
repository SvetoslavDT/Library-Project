#include "CommandTake.h"

void CommandTake::execute(System& sys, const std::vector<std::string>& tokens) const
{
	if (atoi(tokens[1].data()) < 0)
	{
		std::cout << "ID numbers of library units are only positive." << std::endl;
		return;
	}

	std::vector<LibraryUnit*>& units = sys.getLibraryUnitRepository().getUnits();

	LibraryUnit* toTake = nullptr;

	for (size_t i = 0; i < units.size(); ++i)
	{
		if (std::to_string(units[i]->getUniqueNumber()) == tokens[1])
			toTake = units[i];
	}

	if (!toTake)
	{
		size_t pos = sys.getLibraryUnitRepository().readUntilFindByUniqueNumber(atoi(tokens[1].data()));

		if (pos)
		{
			toTake = units[pos];
		}
		else
		{
			std::cout << "No library unit with given number found." << std::endl;
			return;
		}
	}

	if (toTake)
	{
		if (toTake->getCopies() + 1 > toTake->getTaken())
		{
			Reader* ptr = dynamic_cast<Reader*>(sys.getLoggedUser()); // Already insured it is correct
			
			Date date;
			date += 1;
			ptr->addLibraryUnit(toTake, Date{}, date);
			toTake->getTaken()++;
		}
		else
		{
			std::cout << "There are no spare copies of this unit, that can be given at the moment." << std::endl;
			return;
		}
	}

	std::cout << "Library unit added to user's list." << std::endl;
}