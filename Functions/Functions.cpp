#include "Functions.h"

using StringArray = std::vector<std::string>;


void FunctionsForBinary::writeStringArray(std::ostream& os, const StringArray& arr)
{
	size_t count = arr.size();
	os.write((const char*)&count, sizeof(count));
	for (const auto& kw : arr)
		writeString(os, kw);
}

StringArray FunctionsForBinary::readStringArray(std::istream& is)
{
	size_t count;
	is.read((char*)&count, sizeof(count));
	StringArray arr;
	arr.reserve(count);
	for (size_t i = 0; i < count; ++i)
		arr.push_back(readString(is));
	return arr;
}

void FunctionsForBinary::writeString(std::ostream& os, const std::string& str)
{
	size_t len = str.size();
	os.write((const char*)&len, sizeof(len));
	os.write(str.data(), len);
}

std::string FunctionsForBinary::readString(std::istream& is)
{
	size_t len;
	is.read((char*)&len, sizeof(len));

	std::string str(len, '\0');
	is.read(&str[0], len);
	return str;
}

char fromDigitToChar(unsigned short digit)
{
	return char('0' + digit);
}

std::string generateNString(size_t n)
{
	unsigned short i;
	std::string result(n, 'X'); // Allocating space at the beginning

	for (size_t j = 0; j < n; j++)
	{
		i = rand() % 10;
		result[j] = fromDigitToChar(i);
	}

	return result;
}

std::vector<std::string> tokenizeString(const std::string& str)
{
	std::vector<std::string> result;
	std::string word;

	for (char ch : str)
	{
		if (std::isspace(static_cast<unsigned char>(ch)))
		{
			if (!word.empty())
			{
				result.push_back(word);
				word.clear();
			}
		}
		else
		{
			word += ch;
		}
	}

	if (!word.empty())
	{
		result.push_back(word);
	}

	return result;
}
