#pragma once
#include "User.h"

class Administrator : public User
{
public:

	Administrator() = default;
	Administrator(const std::string& name, const std::string& password, const std::string email);

	const std::string& getEmail() const;

	void setEmail(const std::string& email);

	User* clone() const override;

	void writeToBinary(std::ostream& os) const override;
	void readFromBinary(std::istream& is) override;

	void serialise(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	void print() const override;
	std::string getType() const override;
	unsigned getPrintLines() const override;

private:

	bool validEmail(const std::string& str) const;

	std::string email;
};
