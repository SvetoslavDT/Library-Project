#pragma once
#include "Command.h"

struct CommandExit : public Command
{
	void execute(System& sys, const std::vector<std::string>& tokens) const override;
};