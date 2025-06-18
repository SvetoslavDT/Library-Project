#pragma once
#include "System.h"

struct Command
{
	virtual ~Command() = default;
	virtual void execute(System& sys, const std::vector<std::string>& tokens) const = 0;
	
protected:

	bool printAllSingleLibraryUnit(std::vector<LibraryUnit*>& units, const std::string& str, size_t& sum) const;
	void printUsers(const std::vector<User*>& users) const;

	static void setMaxPrintableLines(unsigned short newMaxPrintableLines);

	bool checkIfTokenIsNumber(const std::string token) const;

	static unsigned short MAX_PRINTABLE_LINES;
};
