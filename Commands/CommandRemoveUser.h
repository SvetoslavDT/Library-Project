#pragma once
#include "Command.h"

struct CommandRemoveUser : public Command
{
	void execute(System& sys, const std::vector<std::string>& tokens) const override;

private:

	void removeBooksFromReader(std::vector<LibraryUnit*>& units, std::vector<Reader::LibraryUnitTaken>& takenUnits) const;
};