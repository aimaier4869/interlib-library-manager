#ifndef BOOK_H
#define BOOK_H 

#include <string>
using namespace std;

class Book {
	public:
		string name;
		string author;
		string ISBN; // ISBN作为key，一旦输入不可修改且不可重复录入 
		string type;
		Book();
		Book(string bookName, string bookAuthor, string bookISBN, string bookType);
};

#endif
