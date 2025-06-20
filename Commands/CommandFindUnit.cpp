#include "CommandFindUnit.h"
#include <cstdlib>

void CommandFindUnit::execute(System& sys, const std::vector<std::string>& tokens) const
{
	std::string optionString = tokens[3];
	size_t nextCommandIndex = 0;
	for (size_t i = 4; i < tokens.size() && tokens.size() > 4; i++)
	{
		if (tokens[i] == "sort" || tokens[i] == "top")
		{
			nextCommandIndex = i;
			break;
		}
		optionString += " " + tokens[i];
	}

	std::vector<LibraryUnit*> result;

	if (tokens[0] == "books")
	{
		sys.getLibraryUnitRepository().readAllBooks();
		fillByKey(sys, tokens[2], result, "Book", optionString);
	}
	else if (tokens[0] == "series")
	{
		sys.getLibraryUnitRepository().readAllSeries();
		fillByKey(sys, tokens[2], result, "Series", optionString);
	}
	else if (tokens[0] == "newsletters")
	{
		sys.getLibraryUnitRepository().readAllPeriodicals();
		fillByKey(sys, tokens[2], result, "Periodical", optionString);
	}
	else if (tokens[0] == "list")
	{
		sys.getLibraryUnitRepository().readToEndAllFiles();
		fillByKey(sys, tokens[2], result, "", optionString);
	}
	else
	{
		std::cout << "Unidentified command." << std::endl;
		return;
	}


	if (result.empty())
	{
		std::cout << "No results." << std::endl;
		return;
	}

	if (nextCommandIndex)
	{
		bool sorted = false;
		size_t tokensSize = tokens.size();

		if (tokens[nextCommandIndex] == "sort")
		{
			++nextCommandIndex;

			if (nextCommandIndex + 1 <= tokensSize && tokens[nextCommandIndex] == "year")
			{
				if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "desc")
				{
					++nextCommandIndex;
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getReleaseYear() > rhs->getReleaseYear(); });
				}
				else if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "asc")
				{
					++nextCommandIndex;
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getReleaseYear() < rhs->getReleaseYear();});
				}
				else
				{
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getReleaseYear() < rhs->getReleaseYear();});
				}
			}
			else if (nextCommandIndex + 1 <= tokensSize && tokens[nextCommandIndex] == "rate")
			{
				if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "desc")
				{
					++nextCommandIndex;
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getRating() > rhs->getRating(); });
				}
				else if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "asc")
				{
					++nextCommandIndex;
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getRating() < rhs->getRating();});
				}
				else
				{
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getRating() < rhs->getRating();});
				}
			}
			else if (nextCommandIndex + 1 <= tokensSize && tokens[nextCommandIndex] == "genre")
			{
				if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "desc")
				{
					++nextCommandIndex;
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getGenre() > rhs->getGenre(); });
				}
				else if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "asc")
				{
					++nextCommandIndex;
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getGenre() < rhs->getGenre();});
				}
				else
				{
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getGenre() < rhs->getGenre();});
				}
			}
			else if (nextCommandIndex + 1 <= tokensSize && tokens[nextCommandIndex] == "publisher")
			{
				if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "desc")
				{
					++nextCommandIndex;
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getPublisher() > rhs->getPublisher(); });
				}
				else if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "asc")
				{
					++nextCommandIndex;
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getPublisher() < rhs->getPublisher();});
				}
				else
				{
					selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
						{ return lhs->getPublisher() < rhs->getPublisher();});
				}
			}
			else
			{
				std::cout << "Incorrect sort command - key missing." << std::endl;
				return;
			}
			++nextCommandIndex;
			sorted = true;
		}
		else
		{
			std::cout << "Unrecognised command" << std::endl;
			return;
		}

		if (sorted && nextCommandIndex + 1 <= tokensSize && tokens[nextCommandIndex] == "top")
		{
			++nextCommandIndex;

			if (nextCommandIndex + 1 <= tokensSize)
			{
				if (!checkIfTokenIsNumber(tokens[nextCommandIndex]))
				{
					std::cout << "Incorrect top syntax: '" << tokens[nextCommandIndex] << "' is not a number\n";
					return;
				}
				else
				{
					int topN = std::stoi(tokens[nextCommandIndex]);
					if (nextCommandIndex + 2 <= tokensSize)
					{
						std::cout << "Incorrect top syntax - unexpected token " << tokens[nextCommandIndex + 1]
							<< std::endl;
						return;
					}
					else
					{
						if (topN <= 0)
						{
							std::cout << "Invalid top number" << std::endl;
							return;
						}

						if (topN > result.size())
							topN = result.size();
						else if(topN < result.size())
							result.resize(topN);
					}
				}
			}
			else
			{
				std::cout << "Incorrect top format, no number written." << std::endl;
			}
		}
		else if(nextCommandIndex + 1 <= tokens.size())
		{
			std::cout << "Wrong syntaxys." << std::endl;
			return;
		}
	}

	if (result.empty())
		std::cout << "No units found." << std::endl;
	else
	{
		std::cout << std::endl;

		size_t sum = 0;
		bool goOn = false;
		goOn = printAllSingleLibraryUnit(result, "Book", sum);
		if (goOn)
			return;
		printAllSingleLibraryUnit(result, "Periodical", sum);
		if (goOn)
			return;

		printAllSingleLibraryUnit(result, "Series", sum);
	}
}

void CommandFindUnit::fillByKey(System& sys, const std::string& key, std::vector<LibraryUnit*>& result,
	const std::string& typeFilter,	const std::string& optionString) const
{
	std::vector<LibraryUnit*>& units = sys.getLibraryUnitRepository().getUnits();

	if (key == "title")
	{
		for (size_t i = 0; i < units.size(); ++i)
		{
			if ((units[i]->getType() == typeFilter || typeFilter.empty()) && units[i]->getTitle() == optionString)
				result.push_back(units[i]);
		}
	}
	else if (key == "author")
	{
		for (size_t i = 0; i < units.size(); ++i)
		{
			if (!typeFilter.empty() && units[i]->getType() != typeFilter)
				continue;

			if (Periodical* ptr = dynamic_cast<Periodical*>(units[i]))
			{
				for (size_t j = 0; j < ptr->getArticles().size(); j++)
				{
					if(ptr->getArticles()[j].getAuthor() == optionString)
					{
						result.push_back(units[i]);
						break;
					}
				}
			}
			else if(Book* ptr = dynamic_cast<Book*>(units[i])) // works if Series too in this else if
			{
				if (ptr->getAuthor() == optionString)
					result.push_back(units[i]);
			}
		}
	}
	else if (key == "tag")
	{
		for (size_t i = 0; i < units.size(); ++i)
		{
			if ((units[i]->getType() == typeFilter || typeFilter.empty()) &&
				units[i]->getUniqueNumber() == atol(optionString.data()))
			{
				result.push_back(units[i]);
			}
		}
	}
	else
		std::cout << "Unidentified <option>." << std::endl;
}

/*void CommandFindUnit::sort(size_t& nextCommandIndex, const std::vector<std::string>& tokens,
	std::vector<LibraryUnit*>& result, bool& sorted)
{
	size_t tokensSize = tokens.size();

	if (nextCommandIndex + 1 <= tokensSize && tokens[nextCommandIndex] == "year")
	{
		if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "desc")
		{
			++nextCommandIndex;
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getReleaseYear() > rhs->getReleaseYear(); });
		}
		else if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "asc")
		{
			++nextCommandIndex;
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getReleaseYear() < rhs->getReleaseYear();});
		}
		else
		{
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getReleaseYear() < rhs->getReleaseYear();});
		}
	}
	else if (nextCommandIndex + 1 <= tokensSize && tokens[nextCommandIndex] == "rate")
	{
		if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "desc")
		{
			++nextCommandIndex;
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getRating() > rhs->getRating(); });
		}
		else if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "asc")
		{
			++nextCommandIndex;
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getRating() < rhs->getRating();});
		}
		else
		{
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getRating() < rhs->getRating();});
		}
	}
	else if (nextCommandIndex + 1 <= tokensSize && tokens[nextCommandIndex] == "genre")
	{
		if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "desc")
		{
			++nextCommandIndex;
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getGenre() > rhs->getGenre(); });
		}
		else if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "asc")
		{
			++nextCommandIndex;
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getGenre() < rhs->getGenre();});
		}
		else
		{
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getGenre() < rhs->getGenre();});
		}
	}
	else if (nextCommandIndex + 1 <= tokensSize && tokens[nextCommandIndex] == "publisher")
	{
		if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "desc")
		{
			++nextCommandIndex;
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getPublisher() > rhs->getPublisher(); });
		}
		else if (nextCommandIndex + 2 <= tokensSize && tokens[nextCommandIndex + 1] == "asc")
		{
			++nextCommandIndex;
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getPublisher() < rhs->getPublisher();});
		}
		else
		{
			selectionSortWithPredicate(result, [](const LibraryUnit* lhs, const LibraryUnit* rhs)
				{ return lhs->getPublisher() < rhs->getPublisher();});
		}
	}
	else
	{
		std::cout << "Incorrect sort command - key missing." << std::endl;
		return;
	}
	++nextCommandIndex;
	sorted = true;
}
*/
