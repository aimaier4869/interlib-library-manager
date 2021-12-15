#include "../include/Book.h"


Book::Book() {

};

Book::Book(string bookName, string bookAuthor, string bookISBN, string bookType) {
	name = bookName;
	author = bookAuthor;
	ISBN = bookISBN;
	type = bookType;
};
