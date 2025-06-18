#include "CommandChangeUnit.h"

void CommandChangeUnit::execute(System& sys, const std::vector<std::string>& tokens) const
{
	unsigned id = atol(tokens[2].data());

	if (id <= 0)
	{
		std::cout << "Invalid id number." << std::endl;
		return;
	}

	std::vector<LibraryUnit*>& units = sys.getLibraryUnitRepository().getUnits();
	LibraryUnit* toChange = nullptr;

	for (size_t i = 0; i < units.size(); ++i)
	{
		if (units[i]->getUniqueNumber() == id)
		{
			toChange = units[i];
			break;
		}
	}

	if (!toChange)
	{
		size_t index = sys.getLibraryUnitRepository().readUntilFindByUniqueNumber(id);

		if (index)
			toChange = units[index];
	}

	if (!toChange)
	{
		std::cout << "No unit matches given id." << std::endl;
		return;
	}

	std::string tmp;

	// Title
	std::cout << "Title [" << toChange->getTitle() << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if (!tmp.empty())
		toChange->setTitle(tmp);

	// Publisher
	std::cout << "Publisher [" << toChange->getPublisher() << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if (!tmp.empty())
		toChange->setPublisher(tmp);

	// Genre
	std::cout << "Genre [" << toChange->getGenre() << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if (!tmp.empty())
		toChange->setGenre(tmp);

	// Description
	std::cout << "Description [" << toChange->getBriefDescription() << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if (!tmp.empty())
		toChange->setBriefDescription(tmp);

	// Release year
	std::cout << "Release year [" << toChange->getReleaseYear() << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if (!tmp.empty())
	{
		try
		{
			unsigned year = std::stoul(tmp);
			toChange->setReleaseYear(year);
		}
		catch (...)
		{
			std::cout << "Invalid year, change aborted." << std::endl;
			return;
		}
	}

	// Rating
	std::cout << "Rating [" << toChange->getRating() << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if (!tmp.empty())
	{
		try
		{
			toChange->setRating(std::stoul(tmp));
		}
		catch (...)
		{
			std::cout << "Invalid rating, change aborted." << std::endl;
			return;
		}
	}

	// Specific fields

	if (Book* ptr = dynamic_cast<Book*>(toChange))
	{
		changeIfBook(ptr, tmp);
	}
	else if (Periodical* ptr = dynamic_cast<Periodical*>(toChange))
	{
		changeIfPeriodical(ptr, tmp);
	}
	else if (toChange->getType() == "Series")
	{
		changeIfSeries(toChange, tmp);
	}
}

void CommandChangeUnit::changeIfBook(Book* ptr, std::string& tmp) const
{
	// Author
	std::cout << "Author [" << ptr->getAuthor() << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if (!tmp.empty())
		ptr->setAuthor(tmp);

	// ISBN
	std::cout << "ISBN [" << (ptr->getISBN().hasValue() ? ptr->getISBN().getValue() : "") << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if(!tmp.empty())
	{
		try
		{
			ptr->setISBN(tmp);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			return;
		}
	}
}

void CommandChangeUnit::changeIfPeriodical(Periodical* ptr, std::string& tmp) const
{
	// Month
	std::cout << "Month [" << ptr->getMonth() << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if (!tmp.empty())
	{
		try
		{
			ptr->setMonth(std::stoul(tmp));
		}
		catch (...)
		{
			std::cout << "Invalid month, change aborted." << std::endl;
			return;
		}
	}

	// ISSN
	std::cout << "ISSN [" << (ptr->getISSN().hasValue() ? ptr->getISSN().getValue() : "") << "]: ";
	std::getline(std::cin, tmp);
	if (tmp == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if(!tmp.empty())
	{
		try
		{
			ptr->setISSN(tmp);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			return;
		}
	}

	// Articles
	auto& articles = ptr->getArticles();
	std::cout << "Articles:" << std::endl;
	for (size_t i = 0; i < articles.size(); ++i)
	{
		std::cout << "[" << i << "] " << articles[i].getTitle() << " by " << articles[i].getAuthor() << std::endl;
	}

	std::cout << "Enter article index to edit (or blank to skip): ";
	std::string sel;
	std::getline(std::cin, sel);
	if (sel == "cancel")
	{
		std::cout << "Change cancelled." << std::endl;
		return;
	}
	if (!sel.empty())
	{
		size_t articleIndex;
		try
		{
			articleIndex = std::stoul(sel);
			if (articleIndex >= articles.size())
				throw std::invalid_argument("");
		}
		catch (...)
		{
			std::cout << "Invalid index, aborting article editing." << std::endl;
			return;
		}

		auto& art = articles[articleIndex];

		std::cout << "Article title [" << art.getTitle() << "]: ";
		std::getline(std::cin, sel);
		if (sel == "cancel")
		{
			std::cout << "Change cancelled." << std::endl;
			return;
		}
		if (!sel.empty())
			art.setTitle(sel);

		std::cout << "Article author [" << art.getAuthor() << "]: ";
		std::getline(std::cin, sel);
		if (sel == "cancel")
		{
			std::cout << "Change cancelled." << std::endl;
			return;
		}
		if (!sel.empty())
			art.setAuthor(sel);

		art.setKeyWords();

		std::cout << "Article updated." << std::endl;
	}
}

void CommandChangeUnit::changeIfSeries(LibraryUnit* ptr, std::string& tmp) const
{
	changeIfBook(dynamic_cast<Book*>(ptr), tmp);
	changeIfPeriodical(dynamic_cast<Periodical*>(ptr), tmp);
}