#pragma once
#include "Command.h"

struct CommandFindUnit : public Command
{
	void execute(System& sys, const std::vector<std::string>& tokens) const override;

private:

	void fillByKey(System& sys, const std::string& key, std::vector<LibraryUnit*>& result,
		const std::string& typeFilter, const std::string& optionString) const;

    template<typename Compare>
    void selectionSortWithPredicate(std::vector<LibraryUnit*>& units, const Compare& cmp) const
    {
        size_t n = units.size();

        for (size_t i = 0; i + 1 < n; ++i)
        {
            size_t best = i;

            for (size_t j = i + 1; j < n; ++j)
            {
                if (cmp(units[j], units[best])) // true means the first is "smaller" in context
                    best = j;
            }

            if (best != i)
                std::swap(units[i], units[best]);
        }
    }


	// void sort(size_t& nextCommandIndex, const std::vector<std::string>& tokens, std::vector<LibraryUnit*>& result, bool& sorted);
};