#pragma once
#include "User.h"

// op>> needed??

class Administrator : public User
{
public:

	Administrator() = default;
	Administrator(const std::string& name, const std::string& password, const std::string email);

	const std::string& getEmail() const;

	void setEmail(const std::string& email);

	User* clone() const override;

	//operator>> polymorf. called from User
	//friend std::istream& operator>>(std::istream& is, Administrator& obj);

	void writeToBinary(std::ostream& os) const override;
	void readFromBinary(std::istream& is) override;

	void print(std::ostream& os) const override;

private:

	bool validEmail(const std::string& str) const;

	std::string email;
};
