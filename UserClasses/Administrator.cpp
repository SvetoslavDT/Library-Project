#include "Administrator.h"
#include "Functions.h"
#include <cctype>

Administrator::Administrator(const std::string& name, const std::string& password, const std::string email)
	: User(name, password), email(email)
{
	if (!validEmail(email))
		throw std::invalid_argument("Invalid email");
}

const std::string& Administrator::getEmail() const
{
	return email;
}

void Administrator::setEmail(const std::string& email)
{
	if(!validEmail(email))
		throw std::invalid_argument("Invalid email");
	
	this->email = email;
}

User* Administrator::clone() const
{
	return new Administrator(*this);
}

bool Administrator::validEmail(const std::string& str) const
{
    if (str.empty())
        return false;

    bool seenAt = false;
    bool seenDotAfterAt = false;

    size_t segmentStart = 0;
    size_t atPos = std::string::npos;

    for (size_t i = 0; i < str.length(); ++i)
    {
        char c = str[i];

        if (!(std::isalnum((unsigned char)c) || c == '.' || c == '-' || c == '_' || c == '@'))
            return false;

        if (c == '@')
        {
            if (seenAt || i == 0 || i + 1 == str.length())
                return false;

            seenAt = true;
            atPos = i;

            if (i == segmentStart)
                return false;
            
            segmentStart = i + 1;

            continue;
        }

        if (c == '.')
        {
            if (i == 0 || i + 1 == str.length() || str[i - 1] == '.')
                return false;

            if (seenAt && i > atPos + 0)
                seenDotAfterAt = true;

            segmentStart = i + 1;
        }
    }

    if (!seenAt || !seenDotAfterAt || segmentStart >= str.length())
        return false;

    return true;
}

void Administrator::writeToBinary(std::ostream& os) const
{
    User::writeToBinary(os);

    FunctionsForBinary::writeString(os, email);
}

void Administrator::readFromBinary(std::istream& is)
{
    User::readFromBinary(is);

    std::string tmpEmail = FunctionsForBinary::readString(is);
    email = std::move(tmpEmail);
}

void Administrator::serialise(std::ostream& os) const
{
    User::serialise(os);

    os << email << '\n';
}

void Administrator::deserialize(std::istream& is)
{
    User::deserialize(is);

    is >> email;
}

void Administrator::print() const
{
    User::print();

    std::cout << "Email - " << email << '\n';
}

std::string Administrator::getType() const
{
    return "Administrator";
}

unsigned Administrator::getPrintLines() const
{
    return User::getPrintLines() + 1;
}
