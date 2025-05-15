#pragma once
#include "Repositories/LibraryUnit.h"

class Book : LibraryUnit
{
public:

private:

	std::string author;
	StringArray keyWords; // treated as const
};
