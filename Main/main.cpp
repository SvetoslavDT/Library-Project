#include <iostream>
#include "System.h"

int main()
{
	System::getSystem().run();



	/*
	LibraryUnit* book = new Book("Ti", "Toi", "Tq", "To", 2004, 4, "Az");
std::cout << std::endl;
Reader reader("spens", "123");
Date returnDate, getDate;
Date b;  // current
Date t = b; t += 1;
reader.addLibraryUnit(book, b, t);
std::cout << std::endl;

auto c = book->clone();
c->print();
delete c;

Reader::LibraryUnitTaken x(book, b, t);
Reader::LibraryUnitTaken y = x;

delete book;
*/

	/*
		User** users = new User * [2];
	users[0] = new Reader("Svetoslav", "madmax");
	users[1] = new Administrator("Svetoslavv", "mmmm", "ebasi@dali.com");

	for (size_t i = 0; i < 2; ++i)
	{
		std::cout << *users[i] << std::endl;
	}
	*/

	/*
	Date date;
	std::cout << date.getDay() << '\n' << date.getMonth() << '\n' << date.getYear() << std::endl;

	Reader r("Svetoslav", "madmax");
	std::cout << r << std::endl;

	Administrator adm("Svetoslavv", "mmmm", "ebasi@dali.com");
	std::cout << adm << std::endl;
	*/

	//Optional<std::string> opt("Shinigami");
	//std::cout << opt.getValue() << std::endl;

	/*
	Book book("Shrek", "DC", "Horror", "Good book", 1970, 4, "Boba Fett");
	std::cout << book << std::endl;

	book.setISBN();
	std::cout << std::endl << book;
	*/

	/*
	std::vector<Periodical::Article> v;
	v.push_back({"Pishka", "Pishliov" });
	v.push_back({"A da", "A ne" });
	Periodical per("Shrek", "DC", "Horror", "Good book", 1970, 4, 9, v);

	std::cout << per << std::endl;
	per.setISSN();

	std::cout << per;
	*/

	/*
	LibraryUnit** arr = new LibraryUnit*[3];
	arr[0] = new Book("Shrek", "DC", "Horror", "Good book", 1970, 4, "Boba Fett");
	arr[1] = new Periodical("Shrek", "DC", "Horror", "Good book", 1970, 4, 9, { {"Pishka", "Pishliov"}, {"A da", "A ne"} });
	arr[2] = new Series("Shrek", "DC", "Horror", "Good book", 1970, 4, "Az", 9, {{"Pishka", "Pishliov"}, {"A da", "A ne"}});

	for (size_t i = 0; i < 3; i++)
	{
		std::cout << *arr[i] << std::endl;
		std::cout << "----------------------------------" << std::endl;
	}
	*/

/*	Optional<int> opt;
	opt.setValue(69);
	Optional<int> opt2(69);
	std::cout << opt.getValue() << std::endl << opt2.getValue() << std::endl;
	bool yep = opt == opt2;
	std::cout << yep;

	Optional<std::string> str;
	str.setValue("MAMKA MU");
	std::cout << str.getValue();
		*/

	/*
	Book b("Pinokio", "Baba", "strah", "Description", 2004, 3, "Johny Depp");
	b.setISBN(Book::generateISBN());
	std::cout << b.getISBN();
	*/
}
