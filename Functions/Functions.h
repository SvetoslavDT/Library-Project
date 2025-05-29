#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace FunctionsForBinary
{
	using StringArray = std::vector<std::string>;

	void writeStringArray(std::ostream& os, const StringArray& arr);

	StringArray readStringArray(std::istream& is);

	void writeString(std::ostream& os, const std::string& str);

	std::string readString(std::istream& is);
}

char fromDigitToChar(unsigned short digit);

std::string generateNString(size_t n);
