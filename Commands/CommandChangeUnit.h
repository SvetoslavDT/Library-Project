#pragma once
#include "Command.h"

struct CommandChangeUnit : public Command
{
	void execute(System& sys, const std::vector<std::string>& tokens) const override;

private:

	void changeIfBook(Book* ptr, std::string& tmp) const;
	void changeIfPeriodical(Periodical* ptr, std::string& tmp) const;
	void changeIfSeries(LibraryUnit* ptr, std::string& tmp) const;
};