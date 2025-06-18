#pragma once
#include "Command.h"

struct CommandRemoveUnit : public Command
{
	void execute(System& sys, const std::vector<std::string>& tokens) const override;

private:

	void removeUnit(std::vector<LibraryUnit*>& units, LibraryUnit* toDelete, size_t i) const;
	void removeFromUsers(System& sys, unsigned num) const;
};