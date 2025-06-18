#pragma once
#include "Command.h"
#include "System.h"

class CommandFactory
{
public:

	static CommandFactory& getFactory()
	{
		static CommandFactory theFactory;
		return theFactory;
	}

	Command* create(System& sys, const std::vector<std::string>& tokens) const;

private:

	CommandFactory() = default;
	~CommandFactory() = default;
	CommandFactory(const CommandFactory& other) = delete;
	CommandFactory& operator=(const CommandFactory& other) = delete;
};