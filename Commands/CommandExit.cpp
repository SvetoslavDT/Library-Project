#include "CommandExit.h"

void CommandExit::execute(System& sys, const std::vector<std::string>& tokens) const
{
	sys.exitSystem();
}
