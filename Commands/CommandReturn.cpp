#include "CommandReturn.h"

void CommandReturn::execute(System& sys, const std::vector<std::string>& tokens) const
{
	if (!sys.getLoggedUser() || sys.getTypeOfUser() != System::TypeOfUser::READER)
	{
		std::cout << "Logged reader needed for this command." << std::endl;
		return;
	}
	unsigned id = atoi(tokens[1].data());
	if (id < 0)
	{
		std::cout << "ID numbers of library units are only positive." << std::endl;
		return;
	}

	Reader* user = dynamic_cast<Reader*>(sys.getLoggedUser());

	for (size_t i = 0; i < user->getTakenUnits().size(); ++i)
	{
		if (user->getTakenUnits()[i].getUnit()->getUniqueNumber() == id)
		{
			user->getTakenUnits().erase(user->getTakenUnits().begin() + i);

			returnCopy(sys, id);

			std::cout << "Library unit returned successfully" << std::endl;
			return;
		}
		else
		{
			std::cout << "Reader has not this library unit in their loan list." << std::endl;
			return;
		}
	}

	std::cout << "No unit with this id num found." << std::endl;
}

void CommandReturn::returnCopy(System& sys, unsigned id) const
{
	std::vector<LibraryUnit*>& units = sys.getLibraryUnitRepository().getUnits();

	for (size_t i = 0; i < units.size(); ++i)
	{
		if (units[i]->getUniqueNumber() == id)
		{
			units[i]->getTaken()--;
			return;
		}
	}

	size_t index = sys.getLibraryUnitRepository().readUntilFindByUniqueNumber(id);
	units[index]->getTaken()--;
}