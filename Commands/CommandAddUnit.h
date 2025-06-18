#pragma once
#include "Command.h"

struct CommandAdd : public Command
{
	void execute(System& sys, const std::vector<std::string>& tokens) const override;

private:

	void addBook(System& sys) const;
	void addSeries(System& sys) const;
	void addNewsletters(System& sys) const;

	//checkers and ISBN/ISSN recorders
	Book* checkForIdenticalBook(System& sys, Book* book) const;
	Series* checkForIdenticalSeries(System& sys, Series* series) const;
	Periodical* checkForIdenticalNewsletter(System& sys, Periodical* periodical) const;

	bool checkArticles(const Periodical* series, const Periodical* ptr) const;

	/*
	void addBaseData(bool& shouldSycle, bool& shouldReturn, std::string& title, std::string& publisher,
		std::string& genre, std::string& description, std::string& tmp, unsigned short& year, unsigned short& rating) const
	{
		bool shouldSycle = false;
		bool shouldReturn = false;

		// Title
		std::cout << "Title: ";
		std::getline(std::cin, title);
		if (title == "cancel")
		{
			std::cout << "Add canceled." << std::endl;
			shouldReturn = true;
		}

		// Publisher
		std::cout << "Publisher: ";
		std::getline(std::cin, publisher);
		if (publisher == "cancel")
		{
			std::cout << "Add canceled." << std::endl;
			shouldReturn = true;
		}

		// Genre
		std::cout << "Genre: ";
		std::getline(std::cin, genre);
		if (genre == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			shouldReturn = true;
		}

		// Description
		std::cout << "Description: ";
		std::getline(std::cin, description);
		if (description == "cancel")
		{
			std::cout << "Add cancelled" << std::endl;
			shouldReturn = true;
		}

		// Release year
		std::cout << "Release year: ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel") {
			std::cout << "Add cancelled.\n";
			shouldReturn = true;
		}

		if (!std::stoi(tmp))
		{
			std::cout << "Year can not be negative number." << std::endl;
			shouldSycle = true;
		}
		year = std::stoi(tmp);

		// Rating
		std::cout << "Rating (1–5): ";
		std::getline(std::cin, tmp);
		if (tmp == "cancel")
		{
			std::cout << "Add cancelled." << std::endl;
			shouldReturn = true;
		}

		int rate = std::stoi(tmp);
		if (rate < 0 || rate > 5)
		{
			std::cout << "Rating must be in [0, 5]." << std::endl;
			shouldSycle = true;
		}
		rating = rate;
	}
	*/
};
