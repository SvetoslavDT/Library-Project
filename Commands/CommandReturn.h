#pragma once
#include "Command.h"

struct CommandReturn : public Command
{
	void execute(System& sys, const std::vector<std::string>& tokens) const override;

private:

	void returnCopy(System& sys, unsigned id) const;
};