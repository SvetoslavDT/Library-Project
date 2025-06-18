#include "CommandFactory.h"
#include "CommandAddUnit.h"
#include "CommandAddUser.h"
#include "CommandAll.h"
#include "CommandChangeUnit.h"
#include "CommandChangeUser.h"
#include "CommandFindUnit.h"
#include "CommandInfo.h"
#include "CommandLogin.h"
#include "CommandLogout.h"
#include "CommandRemoveUnit.h"
#include "CommandRemoveUser.h"
#include "CommandReturn.h"
#include "CommandTake.h"
#include "CommandHelp.h"
#include "CommandExit.h"
#include "CommandFindUser.h"

Command* CommandFactory::create(System& sys, const std::vector<std::string>& tokens) const
{
    bool isLogged = sys.getLoggedUser() != nullptr;
    bool isAdmin = sys.getTypeOfUser() == System::TypeOfUser::ADMIN;
    size_t tokensSize = tokens.size();

    if (tokensSize == 1)
    {
        if (tokens[0] == "login")
        {
            return new CommandLogin;
        }
        else if (tokens[0] == "logout")
        {
            if (isLogged)
            {
                return new CommandLogout;
            }
            else
                std::cout << "Logged user is needed to use this command." << std::endl;
        }
        else if (tokens[0] == "help")
        {
            return new CommandHelp;
        }
        else if (tokens[0] == "exit")
        {
            return new CommandExit;
        }
        else
            std::cout << "Unrecognised command used." << std::endl;
    }
    else if (tokensSize == 2)
    {
        if (tokens[1] == "all")
        {
            return new CommandAll;
        }
        else if(tokens[1] == "add")
        {
            if(isAdmin)
            {
                return new CommandAdd;
            }
            else
                std::cout << "You need to be admin to use this command." << std::endl;
        }
        else if (tokens[0] == "take")
        {
            if (isLogged && !isAdmin)
            {
                return new CommandTake;
            }
            else
                std::cout << "Logged reader is needed to use this command." << std::endl;
        }
        else if (tokens[0] == "return")
        {
            if (isLogged && isAdmin)
            {
                return new CommandReturn;
            }
            else
                std::cout << "Logged reader is needed to use this command." << std::endl;
        }
        else if (tokens[0] == "user" && tokens[1] == "change")
        {
            if (isLogged)
                return new CommandChangeUser;
            else
                std::cout << "Logged user is needed to use this command." << std::endl;
        }
        else
            std::cout << "Unrecognised command used." << std::endl;
    }
    else if (tokensSize == 3)
    {
        if (tokens[0] == "list" && tokens[1] == "info")
        {
            if (isLogged)
            {
                return new CommandInfo;
            }
            else
                std::cout << "Logged user is needed to use this command." << std::endl;
        }
        else if (tokens[0] == "list" && tokens[1] == "remove")
        {
            if (isAdmin)
            {
                return new CommandRemoveUnit;
            }
            else
                std::cout << "You need to be admin to use this command." << std::endl;
        }
        else if (tokens[0] == "list" && tokens[1] == "change")
        {
            if (isAdmin)
            {
                return new CommandChangeUnit;
            }
            else
                std::cout << "You need to be admin to use this command." << std::endl;
        }
        else if (tokens[0] == "user" && tokens[1] == "remove")
        {
            if (isAdmin)
            {
                return new CommandRemoveUser;
            }
            else
                std::cout << "You need to be admin to use this command." << std::endl;
        }
        else if (tokens[0] == "user" && tokens[1] == "change")
        {
            if (isAdmin)
                return new CommandChangeUser;
            else
                std::cout << "You need to be admin to use this command." << std::endl;
        }
        else
            std::cout << "Unrecognised command used." << std::endl;
    }
    else if (tokensSize >= 4)
    {
        if (tokensSize == 4 && tokens[0] == "user" && tokens[1] == "find")
        {
            if (isAdmin)
                return new CommandFindUser;
            else
                std::cout << "You need to be admin to use this command." << std::endl;
        }
        else if (tokens[1] == "find")
        {
            if (isLogged)
            {
                return new CommandFindUnit;
            }
            else
                std::cout << "Logged user is needed to use this command." << std::endl;
        }
        else if (tokens[0] == "user" && tokens[1] == "add")
        {
            if (isAdmin)
            {
                return new CommandAddUser;
            }
            else
                std::cout << "You need to be admin to use this command." << std::endl;
        }
    }

    return nullptr;
}