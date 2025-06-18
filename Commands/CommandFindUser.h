#pragma once
#include "Command.h"

struct CommandFindUser : public Command
{
	void execute(System& sys, const std::vector<std::string>& tokens) const override;

private:

	bool findUsers(System& sys, const std::vector<std::string>& tokens, std::vector<User*>& result) const;
};