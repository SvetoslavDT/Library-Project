#include "CommandHelp.h"

void CommandHelp::execute(System& sys, const std::vector<std::string>& tokens) const
{
    std::cout
        << "Available commands:\n"
        << "  login                       - enter username and password\n"
        << "  logout                      - log out of current session\n"
        << "  books all                   - list all books\n"
        << "  newsletters all             - list all periodicals\n"
        << "  series all                  - list all series\n"
        << "  list all                    - list all items\n"
        << "  list info <isbn|issn>       - show detailed info by ISBN/ISSN ( wtihout dashes)\n"
        << "  books find <opt> <value>       [sort <key> [asc|desc]] [top <n>]\n"
        << "  series find <opt> <value>      [sort <key> [asc|desc]] [top <n>]\n"
        << "  newsletters find <opt> <value> [sort <key> [asc|desc]] [top <n>]\n"
        << "  list find <opt> <value>        [sort <key> [asc|desc]] [top <n>]  - search all types\n"
        << "      <opt> = title | author | tag\n"
        << "      <key> = year | rate | genre | publisher\n"
        << "  books add                   - interactively add a book (admin only)\n"
        << "  series add                  - interactively add a series (admin only)\n"
        << "  newsletters add             - interactively add a periodical (admin only)\n"
        << "  list remove <id>            - remove an item (admin only)\n"
        << "  list change <id>            - edit an item (admin only)\n"
        << "  user add <name> <pw> [admin]- create new user (admin only)\n"
        << "  user remove <name>          - delete a user (admin only)\n"
        << "  user change [<name>]        - change password\n"
        << "  user find <opt> <value>     - search users by name, ID or state ( if state is chosen then after it write <opt2>)\n"
        << "  <opt2> = overdue (users with expired date of return) | reader(with more than 5 taken units for a month) | inactive (no taken units for the past 3 months)\n"
        << "  take <ID>                   - borrow an item\n"
        << "  return <ID>                 - return a borrowed item\n"
        << "  help                        - show this help\n"
        << "  exit                        - quit application\n";
}
