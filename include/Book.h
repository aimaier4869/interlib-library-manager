#ifndef BOOK_H
#define BOOK_H 

#include <string>
using namespace std;

class Book {
	public:
		string name;
		string author;
		string ISBN; // ISBN��Ϊkey��һ�����벻���޸��Ҳ����ظ�¼�� 
		string type;
		Book();
		Book(string bookName, string bookAuthor, string bookISBN, string bookType);
};

#endif
