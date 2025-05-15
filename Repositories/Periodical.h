#pragma once
#include "LibraryUnit.h"

class Periodical : LibraryUnit
{
public:

	class Article
	{
	public:
		
		const std::string getTitle() const;
		const std::string getAuthor() const;
		const stringArray getKeyWords() const;

		void setTitle(const std::string& newTitle);
		void setAuthor(const std::string& newAuthor);
		void setKeyWords(const stringArray& other);

	private:

		std::string title;
		std::string author;
		stringArray keyWords;
	};

private:

	uint8_t month;
	std::vector<Article> articles;
};
