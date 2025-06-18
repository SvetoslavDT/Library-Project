#pragma once
#include "User.h"
#include "Series.h"

class Reader : public User
{
public:

	struct LibraryUnitTaken
	{
	public:
		
		LibraryUnitTaken() = default;
		LibraryUnitTaken(const LibraryUnit* unit, const Date& borrowDate, const Date& returnDate);
		LibraryUnitTaken(const LibraryUnitTaken& other);
		LibraryUnitTaken& operator=(const LibraryUnitTaken& other);
		~LibraryUnitTaken();

		const LibraryUnit* getUnit() const;
		const Date& getBorrowDate() const;
		const Date& getReturnDate() const;

		void seReturnDate(const Date& date);

		friend std::ostream& operator<<(std::ostream& os, const LibraryUnitTaken& obj);
		friend std::istream& operator>>(std::istream& is, LibraryUnitTaken& obj);

		void writeToBinary(std::ostream& os) const;
		void readFromBinary(std::istream& is);

		void print() const;

	private:

		LibraryUnit* unit = nullptr;
		Date borrowDate;
		Date returnDate;
	};

	Reader() = default;
	Reader(const std::string& name, const std::string& password);
	Reader(const std::string& name, const std::string& password, const std::vector<LibraryUnitTaken>& arr);

	const std::vector<LibraryUnitTaken>& getTakenUnits() const;
	std::vector<LibraryUnitTaken>& getTakenUnits();

	void setTakenLibraryUnits(const std::vector<LibraryUnitTaken>& arr);

	void addLibraryUnit(const LibraryUnit* unit, const Date& borrowDate, const Date& returnDate);

	User* clone() const override;

	void writeToBinary(std::ostream& os) const override;
	void readFromBinary(std::istream& is) override;

	void serialise(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	void print() const override;
	std::string getType() const override;
	unsigned getPrintLines() const override;

private:

	std::vector<LibraryUnitTaken> takenUnits;
};
