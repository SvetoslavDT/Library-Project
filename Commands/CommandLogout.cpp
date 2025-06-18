#include "CommandLogout.h"

void CommandLogout::execute(System& sys, const std::vector<std::string>& tokens) const
{
	sys.setLoggedUser(nullptr);
	std::cout << "Logout successful." << std::endl;
}