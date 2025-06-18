#include "CommandAll.h"

void CommandAll::execute(System& sys, const std::vector<std::string>& tokens) const
{
	if (tokens[0] == "books")
	{
		sys.getLibraryUnitRepository().readAllBooks();
		size_t sum = 0;
		printAllSingleLibraryUnit(sys.getLibraryUnitRepository().getUnits(), "Book", sum);
		return;
	}
	else if (tokens[0] == "newsletters")
	{
		sys.getLibraryUnitRepository().readAllPeriodicals();
		size_t sum = 0;
		printAllSingleLibraryUnit(sys.getLibraryUnitRepository().getUnits(), "Periodical", sum);
		return;
	}
	else if (tokens[0] == "series")
	{
		sys.getLibraryUnitRepository().readAllSeries();
		size_t sum = 0;
		printAllSingleLibraryUnit(sys.getLibraryUnitRepository().getUnits(), "Series", sum);
		return;
	}
	else if (tokens[0] == "list")
	{
		sys.getLibraryUnitRepository().readAllBooks();
		sys.getLibraryUnitRepository().readAllPeriodicals();
		sys.getLibraryUnitRepository().readAllSeries();
		size_t sum = 0;
		bool stop = false;
		stop = printAllSingleLibraryUnit(sys.getLibraryUnitRepository().getUnits(), "Book", sum);
		if (stop)
			return;
		stop = printAllSingleLibraryUnit(sys.getLibraryUnitRepository().getUnits(), "Periodical", sum);
		if (stop)
			return;
		stop = printAllSingleLibraryUnit(sys.getLibraryUnitRepository().getUnits(), "Series", sum);
		return;
	}
	else
	{
		std::cout << "Invalid command." << std::endl;
		return;
	}

	std::cout << "No units found." << std::endl;
}