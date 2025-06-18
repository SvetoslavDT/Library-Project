#include "CommandInfo.h"

void CommandInfo::execute(System& sys, const std::vector<std::string>& tokens) const
{
	sys.getLibraryUnitRepository().readToEndAllFiles();
	
	std::vector<LibraryUnit*>& units = sys.getLibraryUnitRepository().getUnits();

	for (LibraryUnit* u : units)
	{
		if (Series* ptr = dynamic_cast<Series*>(u))
		{
			if ((ptr->getISBN().hasValue() && ptr->getISBN().getValue() == tokens[2]) ||
				(ptr->getISSN().hasValue() && ptr->getISSN().getValue() == tokens[2]))
			{
				std::cout << std::endl;
				ptr->print();
				return;
			}
		}
		else if (Book* ptr = dynamic_cast<Book*>(u))
		{
			if (ptr->getISBN().hasValue() && ptr->getISBN().getValue() == tokens[2])
			{
				std::cout << std::endl;
				ptr->print();
				return;
			}
		}
		else if (Periodical* ptr = dynamic_cast<Periodical*>(u))
		{
			if (ptr->getISSN().hasValue() && ptr->getISSN().getValue() == tokens[2])
			{
				std::cout << std::endl;
				ptr->print();
				return;
			}
		}
		else // Should't be called ( won't have a reason )
		{
			std::cout << "There is an unidentified unit in the system." << std::endl;
			return;
		}
	}

	std::cout << "No library unit mathes the ISBN/ISSN." << std::endl;
}