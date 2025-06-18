#include "CommandAddUnit.h"

void CommandAdd::execute(System& sys, const std::vector<std::string>& tokens) const
{
	if (tokens[0] == "books")
	{
		addBook(sys);
	}
	else if (tokens[0] == "series")
	{
		addSeries(sys);
	}
	else if (tokens[0] == "newsletters")
	{
		addNewsletters(sys);
	}
	else
	{
		std::cout << "Unrecognised unit to add." << std::endl;
	}
}

void CommandAdd::addBook(System& sys) const
{
	std::cout << "Enter each field on a new line. Type \"cancel\" at any prompt to abort.\n"
		"Fields (in order):\n"
		"1) Title (optional)\n"
		"2) Publisher (required)\n"
		"3) Genre (required)\n"
		"4) Description (required)\n"
		"5) Release year (required, integer)\n"
		"6) Rating (required, 1-5 integer)\n"
		"7) Author (optional)\n"
		"8) ISBN (optional)\n";

	std::string title, publisher, author, genre, description, isbn, tmp;
	unsigned short year = 0, rating = 0;

	do
	{
		// Title
		std::cout << "Title: ";
		std::getline(std::cin, title);
		if (title == "cancel")
		{
			std::cout << "Add canceled." << std::endl;
			return;
		}

		// Publisher
		std::cout << "Publisher: ";
		std::getline(std::cin, publisher);
		if (publisher == "cancel")
		{
			std::cout << "Add canceled." << std::endl;
			return;
		}

		// Genre
		std::cout << "Genre: ";
		std::getline(std::cin, genre);
		if (genre == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		// Description
		std::cout << "Description: ";
		std::getline(std::cin, description);
		if (description == "cancel")
		{
			std::cout << "Add cancelled" << std::endl;
			return;
		}

		// Release year
		std::cout << "Release year: ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		if (!std::stoi(tmp))
		{
			std::cout << "Year can not be negative number." << std::endl;
			continue;
		}
		year = std::stoi(tmp);

		// Rating
		std::cout << "Rating (1-5): ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}
		
		int rate = std::stoi(tmp);
		if (rate < 0 || rate > 5)
		{
			std::cout << "Rating must be in [0, 5]." << std::endl;
			continue;
		}
		rating = rate;

		// Author
		std::cout << "Author: ";
		std::getline(std::cin, author);
		if (author == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		// ISBN
		std::cout << "ISBN: ";
		std::getline(std::cin, isbn);
		if (isbn == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		
		Book* newBook = nullptr;
		try
		{
			newBook = new Book(title, publisher, genre, description, year, rating, author);
			if (!isbn.empty())
				newBook->setISBN(isbn);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			delete newBook;
			newBook = nullptr;
		}

		if (newBook)
		{
			Book* ptr = checkForIdenticalBook(sys, newBook);

			if (ptr)
				++(*ptr);
			else
				sys.getLibraryUnitRepository().getUnits().push_back(newBook);

			std::cout << "Book added successfully." << std::endl;
			return;
		}

	} while (true);
}

void CommandAdd::addSeries(System& sys) const
{
	std::cout << "Enter each field on a new line. Type \"cancel\" at any prompt to abort.\n"
		"Fields (in order):\n"
		"1) Title (optional)\n"
		"2) Publisher (required)\n"
		"3) Genre (required)\n"
		"4) Description (required)\n"
		"5) Release year (required, integer)\n"
		"6) Rating (required, 1-5 integer)\n"
		"7) Author (optional)\n"
		"8) Release month (required)\n"
		"9) ISBN (optional)\n"
		"10)ISSN (optional)\n"
		"11)Number of articles\n"
		"12)Multiple articles - every articles is 2 lines\n";

	std::string title, publisher, author, genre, description, isbn, issn, tmp, tmp1;
	unsigned short year = 0, month = 0, rating = 0;
	std::vector<Periodical::Article> articles;

	do
	{
		// Title
		std::cout << "Title: ";
		std::getline(std::cin, title);
		if (title == "cancel")
		{
			std::cout << "Add canceled." << std::endl;
			return;
		}

		// Publisher
		std::cout << "Publisher: ";
		std::getline(std::cin, publisher);
		if (publisher == "cancel")
		{
			std::cout << "Add canceled." << std::endl;
			return;
		}

		// Genre
		std::cout << "Genre: ";
		std::getline(std::cin, genre);
		if (genre == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		// Description
		std::cout << "Description: ";
		std::getline(std::cin, description);
		if (description == "cancel")
		{
			std::cout << "Add cancelled" << std::endl;
			return;
		}

		// Release year
		std::cout << "Release year: ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		if (!std::stoi(tmp))
		{
			std::cout << "Year can not be negative number." << std::endl;
			continue;
		}
		year = std::stoi(tmp);

		// Rating
		std::cout << "Rating (1-5): ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		int rate = std::stoi(tmp);
		if (rate < 0 || rate > 5)
		{
			std::cout << "Rating must be in [0, 5]." << std::endl;
			continue;
		}
		rating = rate;

		// Author
		std::cout << "Author: ";
		std::getline(std::cin, author);
		if (author == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		// Release month
		std::cout << "Month: ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		rate = std::stoi(tmp); // reusing int rate
		if (rate < 1 || rate > 12)
		{
			std::cout << "Month must be in [1, 12]." << std::endl;
			continue;
		}
		month = rate;

		// ISBN
		std::cout << "ISBN: ";
		std::getline(std::cin, isbn);
		if (isbn == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		// ISSN
		std::cout << "ISSN: ";
		std::getline(std::cin, issn);
		if (issn == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		// Number of articles
		std::cout << "Number of articles: ";
		std::getline(std::cin, tmp);
		if (issn == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		rate = std::stoi(tmp); // reusing int rate
		if (rate < 0)
		{
			std::cout << "Series should have at least one article." << std::endl;
			continue;
		}
		
		// Articles
		for (size_t i = 0; i < rate; i++)
		{
			std::cout << "Title: ";
			std::getline(std::cin, tmp);

			std::cout << "Author: ";
			std::getline(std::cin, tmp1);

			if (tmp == "cancel" || tmp1 == "cancel")
			{
				std::cout << "Add cancelled." << std::endl;
				return;
			}

			articles.push_back({ tmp, tmp1 });

			std::cout << std::endl;
		}

		Series* newSeries = nullptr;
		try
		{
			newSeries = new Series(title, publisher, genre, description, year, rating, author, month, articles);
			if(!isbn.empty())
				newSeries->setISBN(isbn);
			if (!issn.empty())
				newSeries->setISSN(issn);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			delete newSeries;
			newSeries = nullptr;
		}

		if (newSeries)
		{
			Series* ptr = checkForIdenticalSeries(sys, newSeries);

			if (ptr)
				++(*ptr);
			else
				sys.getLibraryUnitRepository().getUnits().push_back(newSeries);

			std::cout << "Series added successfully." << std::endl;
			return;
		}

	} while (true);
}

void CommandAdd::addNewsletters(System& sys) const
{
	std::cout << "Enter each field on a new line. Type \"cancel\" at any prompt to abort.\n"
		"Fields (in order):\n"
		"1) Title (optional)\n"
		"2) Publisher (required)\n"
		"3) Genre (required)\n"
		"4) Description (required)\n"
		"5) Release year (required, integer)\n"
		"6) Rating (required, 1–5 integer)\n"
		"7) Release month (required)\n"
		"8)ISSN (optional)\n"
		"9)Number of articles\n"
		"10)Multiple articles - every articles is 2 lines\n";

	std::string title, publisher, genre, description, issn, tmp, tmp1;
	unsigned short year = 0, month = 0, rating = 0;
	std::vector<Periodical::Article> articles;

	do
	{
		// Title
		std::cout << "Title: ";
		std::getline(std::cin, title);
		if (title == "cancel")
		{
			std::cout << "Add canceled." << std::endl;
			return;
		}

		// Publisher
		std::cout << "Publisher: ";
		std::getline(std::cin, publisher);
		if (publisher == "cancel")
		{
			std::cout << "Add canceled." << std::endl;
			return;
		}

		// Genre
		std::cout << "Genre: ";
		std::getline(std::cin, genre);
		if (genre == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		// Description
		std::cout << "Description: ";
		std::getline(std::cin, description);
		if (description == "cancel")
		{
			std::cout << "Add cancelled" << std::endl;
			return;
		}

		// Release year
		std::cout << "Release year: ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		if (!std::stoi(tmp))
		{
			std::cout << "Year can not be negative number." << std::endl;
			continue;
		}
		year = std::stoi(tmp);

		// Rating
		std::cout << "Rating (1–5): ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		int rate = std::stoi(tmp);
		if (rate < 0 || rate > 5)
		{
			std::cout << "Rating must be in [0, 5]." << std::endl;
			continue;
		}
		rating = rate;

		// Release month
		std::cout << "Month: ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		rate = std::stoi(tmp); // reusing int rate
		if (rate < 1 || rate > 12)
		{
			std::cout << "Month must be in [1, 12]." << std::endl;
			continue;
		}
		month = rate;

		// ISSN
		std::cout << "ISSN: ";
		std::getline(std::cin, issn);
		if (issn == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		// Number of articles
		std::cout << "Number of articles: ";
		std::getline(std::cin, tmp);
		if (issn == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			return;
		}

		rate = std::stoi(tmp); // reusing int rate
		if (rate < 0)
		{
			std::cout << "Series should have at least one article." << std::endl;
			continue;
		}

		// Articles
		for (size_t i = 0; i < rate; i++)
		{
			std::cout << "Title: ";
			std::getline(std::cin, tmp);

			std::cout << "Author: ";
			std::getline(std::cin, tmp1);

			if (tmp == "cancel" || tmp1 == "cancel")
			{
				std::cout << "Add cancelled." << std::endl;
				return;
			}

			articles.push_back({ tmp, tmp1 });

			std::cout << std::endl;
		}

		Periodical* newPeriodical = nullptr;
		try
		{
			newPeriodical = new Periodical(title, publisher, genre, description, year, rating, month, articles);
			if (!issn.empty())
				newPeriodical->setISSN(issn);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
			delete newPeriodical;
			newPeriodical = nullptr;
		}

		if (newPeriodical)
		{
			Periodical* ptr = checkForIdenticalNewsletter(sys, newPeriodical);

			if (ptr)
				++(*ptr);
			else
				sys.getLibraryUnitRepository().getUnits().push_back(newPeriodical);

			std::cout << "Series added successfully." << std::endl;
			return;
		}

	} while (true);
}

Book* CommandAdd::checkForIdenticalBook(System& sys, Book* book) const
{
	std::vector<LibraryUnit*> &units = sys.getLibraryUnitRepository().getUnits();

	for (size_t i = 0; i < units.size(); ++i)
	{
		if (Book* ptr = dynamic_cast<Book*>(units[i]))
		{
			if (ptr->getISBN().hasValue() && book->getISBN().hasValue() && ptr->getISBN().getValue() == book->getISBN().getValue())
			{
				return ptr;
			}
			else if (ptr->getAuthor() == book->getAuthor() && ptr->getTitle() == book->getTitle() && ptr->getReleaseYear() == book->getReleaseYear())
			{

				if (ptr->getISBN().hasValue() && !book->getISBN().hasValue())
				{
					book->setISBN(ptr->getISBN().getValue());
				}
				else if (!ptr->getISBN().hasValue() && book->getISBN().hasValue())
				{
					ptr->setISBN(book->getISBN().getValue());
				}
				else if ((ptr->getISBN().hasValue() && book->getISBN().hasValue()) && ptr->getISBN().getValue() != book->getISBN().getValue())
				{
					book->setISBN(ptr->getISBN().getValue());
				}

				return ptr;
			}
		}
	}

	return nullptr;
}

Series* CommandAdd::checkForIdenticalSeries(System& sys, Series* series) const
{
	std::vector<LibraryUnit*>& units = sys.getLibraryUnitRepository().getUnits();

	for (size_t i = 0; i < units.size(); ++i)
	{
		if (Series* ptr = dynamic_cast<Series*>(units[i]))
		{
			if (series->getISBN().hasValue() && series->getISSN().hasValue() && ptr->getISBN().hasValue() && ptr->getISSN().hasValue() &&
				series->getISBN().getValue() == ptr->getISBN().getValue() && series->getISSN().getValue() == ptr->getISSN().getValue())
			{
				return ptr;
			}

			if (checkArticles(series, ptr) && ptr->getAuthor() == series->getAuthor() && ptr->getTitle() == series->getTitle() && ptr->getReleaseYear() == series->getReleaseYear() &&
				ptr->getReleaseYear() == series->getReleaseYear() && ptr->getTitle() == series->getTitle())
			{
				
				if (ptr->getISBN().hasValue())
					series->setISBN(ptr->getISBN().getValue());
				else if (!ptr->getISBN().hasValue() && series->getISBN().hasValue())
					ptr->setISBN(series->getISBN().getValue());

				if (ptr->getISSN().hasValue())
					series->setISSN(ptr->getISSN().getValue());
				else if (!ptr->getISSN().hasValue() && series->getISSN().hasValue())
					ptr->setISSN(series->getISSN().getValue());

				return ptr;
			}
		}
	}

	return nullptr;
}

Periodical* CommandAdd::checkForIdenticalNewsletter(System& sys, Periodical* periodical) const
{
	std::vector<LibraryUnit*>& units = sys.getLibraryUnitRepository().getUnits();

	for (size_t i = 0; i < units.size(); i++)
	{
		if (Periodical* ptr = dynamic_cast<Periodical*>(units[i]))
		{
			if (periodical->getISSN().hasValue() && ptr->getISSN().hasValue() && periodical->getISSN().getValue() == ptr->getISSN().getValue())
			{
				return ptr;
			}
			else if (checkArticles(periodical, ptr) && ptr->getReleaseYear() == periodical->getReleaseYear() && ptr->getTitle() == periodical->getTitle())
			{
				if (periodical->getISSN().hasValue() && !ptr->getISSN().hasValue())
				{
					ptr->setISSN(periodical->getISSN().getValue());
				}
				else if (!periodical->getISSN().hasValue() && ptr->getISSN().hasValue())
				{
					periodical->setISSN(ptr->getISSN().getValue());
				}
				else if (periodical->getISSN().hasValue() && ptr->getISSN().hasValue() && periodical->getISSN().getValue() != ptr->getISSN().getValue())
				{
					periodical->setISSN(ptr->getISSN().getValue());
				}

				return ptr;
			}
		}
	}

	return nullptr;
}

bool CommandAdd::checkArticles(const Periodical* series, const Periodical* ptr) const
{
	bool sameArticles = series->getArticles().size() == ptr->getArticles().size();

	for (size_t i = 0; sameArticles && i < ptr->getArticles().size(); i++)
	{
		if (ptr->getArticles()[i] != series->getArticles()[i])
			sameArticles = false;
	}

	return sameArticles;
}