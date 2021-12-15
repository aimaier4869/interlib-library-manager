#include <fstream>
#include "../include/Book.h"
#include "../include/Library.h"

#include <iostream>
using namespace std;


Library::Library() {
	// ��ǰҳ����Ϊ 0
	currentPageIndex = 0;
	currentPageCount = 0;
	updatePageMode = 0;

	// ���ļ��ж�ȡ����
	readDataFromFile();

	// ��ǰҳ��Ҫչʾ��ͼ���б�
	updateCurrentPage(1);
//			cout << searchBook(Book("", "", "", "T"));
//			cout << currentPageBooksArr[0]->name;
};
// ��ȡ�ļ��е����ݲ����µ������У������û�ɾ���û�ʱ��Ҫ���»�ȡ���ݣ����Է�װ����������
void Library::readDataFromFile() {
	// ��ʼ���ļ��ж�ȡ
	fstream fs;
	// �Ȼ�ȡ��Ϣ
	fs.open("database\\LibraryInfo.txt", ios::in);
	fs >> totalCount;
	// �ر��ļ�
	fs.close();
	// ��ʼ��ȡÿһ�������Ϣ
	booksArr = new Book[totalCount];
	fs.open("database\\Library.txt", ios::in);
	for(int i = 0; i < totalCount; i++) {
		string name, author, ISBN, type;
		fs >> name >> author >> ISBN >> type;
		booksArr[i] = Book(name, author, ISBN, type);
	}
	// �ر��ļ�
	fs.close();
}
// ͨ���������ң������ҵ���������û�ҵ�����0;
int Library::searchBook(Book book) {

	if(book.name == "" && book.author == "" && book.ISBN == "" && book.type == "") {
		// ʲô��û���룬�л�Ϊ�ܱ�����Ⱦ��ҳ
		updatePageMode = 0;
		return updateCurrentPage(1);
	}

	int len = 0;
	// ��ʼ����
	for(int i = 0; i < totalCount; i++) {
		bool checkBookName = false;
		bool checkAuthor = false;
		bool checkISBN = false;
		bool checkType = false;

		if(book.name == "") { // ����ǿ��Ǿͺ��Ը���
			checkBookName = true;
		} else if(book.name != booksArr[i].name) {
			continue;
		}

		if(book.author == "") { // ����ǿ��Ǿͺ��Ը���
			checkAuthor = true;
		} else if(book.author != booksArr[i].author) {
			continue;
		}

		if(book.ISBN == "") { // ����ǿ��Ǿͺ��Ը���
			checkISBN = true;
		} else if(book.ISBN != booksArr[i].ISBN) {
			continue;
		}

		if(book.type == "") {
			checkType = true;
		} else {
			int bookTypeLength = book.type.length();
			string thisBookType = booksArr[i].type.substr(0, bookTypeLength);
			if(book.type != thisBookType) {
				continue;
			}
		}
		// ����������֤���ڵ�������
		len++;
		Book ** temp = tempBooksArr;
		tempBooksArr = new Book*[len]; // �½�����Ϊlen������
		for(int j = 0; j < len - 1; j++) {
			tempBooksArr[j] = temp[j];
		}
		tempBooksArr[len - 1] = &booksArr[i];
	}

	// ����������ˣ���ҳҪ����ʱ����չʾ
	updatePageMode = 1;
	tempBooksArrLen = len;
	updateCurrentPage(1);
	return len;
};
// ͨ��ISBN�õ�ͼ�����ƣ���Ҫ���ڽ��ļ�¼
string Library::getBookNameByISBN(string ISBN) {
	for(int i = 0; i < totalCount; i++) {
		if(ISBN == booksArr[i].ISBN) {
			return booksArr[i].name;
		}
	}
	return "";
}
// ��ҳչʾ��������ת֮��ҳ���е���������
// pageIndexҪ��ת���ڼ�ҳ��countÿҳչʾ���������ݣ�Ĭ��10��
// �����ⲿ�ж��Ƿ���Ե����һҳ����֤�������pageIndex�ǲ�С��0���Ҳ�������ҳ��
// ���pageIndex���˵��´��뱨���Ҳ���
// ������getTotalPageCount�����õ���ҳ��
int Library::updateCurrentPage(int pageIndex, int count) {

	// Ҫ��ת��ҳ�����������
	int len = count;

	// �ܱ�����Ⱦ
	if(!updatePageMode) {
		// ���ﴦ�����һҳ�������ݲ���count��ʱ�����
		if(totalCount - (pageIndex - 1) * count < count) {
			len = totalCount - (pageIndex - 1) * count;
		}
		// ��ʼ�޸ĸ���ҳ������
		currentPageBooksArr = new Book*[len]; // �½�����Ϊlen������
		for(int i = 0; i < len; i++) {
			// debug:������ܻ���������������Ҳ��֪�����������ǵù��������ǲ�������
			//				cout <<  ((pageIndex - 1) * count + i);
			currentPageBooksArr[i] = &booksArr[(pageIndex - 1) * count + i];
		}
	} else {
		// ��ʱ������Ⱦ
		if(tempBooksArrLen - (pageIndex - 1) * count < count) {
			len = tempBooksArrLen - (pageIndex - 1) * count;
		}
		// ��ʼ�޸ĸ���ҳ������
		currentPageBooksArr = new Book*[len]; // �½�����Ϊlen������
		for(int i = 0; i < len; i++) {
			// debug:������ܻ���������������Ҳ��֪�����������ǵù��������ǲ�������
			//				cout <<  ((pageIndex - 1) * count + i);
			currentPageBooksArr[i] = tempBooksArr[(pageIndex - 1) * count + i];
		}
	}
	currentPageIndex = pageIndex;
	currentPageCount = len;
	return len;
}
// ��ȡÿҳչʾcount�����ݵĻ������Էֶ���ҳ
int Library::getTotalPageCount(int count) {
	if(!updatePageMode) {
		if(totalCount % count == 0) {
			return totalCount / count;
		} else {
			return totalCount / count + 1;
		}
	} else {
		if(tempBooksArrLen % count == 0) {
			return tempBooksArrLen / count;
		} else {
			return tempBooksArrLen / count + 1;
		}
	}
};
//		 ɾ��ͼ�飬����currentPageBooksArr�е�index
void Library::removeBook(int index) {
	// ɾ���û������ҪɾŶ�����ָܻ���
	fstream fs;
	fs.open("database\\Library.txt", ios::out);
	for(int i = 0; i < totalCount; i++) {
		if(booksArr[i].ISBN == currentPageBooksArr[index]->ISBN) {
			continue;
		}
		fs << booksArr[i].name << " " << booksArr[i].author << " " << booksArr[i].ISBN << " " <<booksArr[i].type << " " << "\n";
	};
	// �ر��ļ�
	fs.close();
	// ������Ϣ
	fs.open("database\\LibraryInfo.txt", ios::out);
	fs << --totalCount;
	// �ر��ļ�
	fs.close();

	// ��ô�죿���¶�ȡ�� ��
	// ���ļ��ж�ȡ����
	readDataFromFile();

	// ���µ�ǰҳ��Ҫչʾ������
	updateCurrentPage(1);
};
// ����ͼ�飬�����ɹ����ص�ǰҳͼ������ ,ʧ���˷���-1
int Library::addBook(Book book) {
	if(searchBook(Book("", "", book.ISBN, ""))) {
		return -1;
	}
	// ���ͼ�飬��ӵ���ǰ��
	fstream fs;
	fs.open("database\\Library.txt", ios::out);
	fs << book.name << " " << book.author << " " << book.ISBN << " " << book.type << "\n";
	for(int i = 0; i < totalCount; i++) {
		string name, author, ISBN, type;
		fs << booksArr[i].name << " " << booksArr[i].author << " " << booksArr[i].ISBN << " " << booksArr[i].type << "\n";
	}
	// �ر��ļ�
	fs.close();
	// ������Ϣ
	fs.open("database\\LibraryInfo.txt", ios::out);
	fs << ++totalCount;
	// �ر��ļ�
	fs.close();

	// ��ô�죿���¶�ȡ�� ��
	// ���ļ��ж�ȡ����
	readDataFromFile();

	// ���µ�ǰҳ��Ҫչʾ������
	return updateCurrentPage(1);
}
// �޸�ͼ�飬�����ɹ����ص�ǰҳͼ������ ,ʧ���˷���-1
int Library::modifyBook(Book book) {
	if(!searchBook(Book("", "", book.ISBN, ""))) {
		return -1;
	}
	// ���ͼ�飬��ӵ���ǰ��
	fstream fs;
	fs.open("database\\Library.txt", ios::out);
	for(int i = 0; i < totalCount; i++) {
		if(booksArr[i].ISBN == book.ISBN) {
			fs << book.name << " " << book.author << " " << book.ISBN << " " << book.type << "\n";
		} else {
			fs << booksArr[i].name << " " << booksArr[i].author << " " << booksArr[i].ISBN << " " << booksArr[i].type << "\n";
		}
	}
	// �ر��ļ�
	fs.close();

	// ��ô�죿���¶�ȡ�� ��
	// ���ļ��ж�ȡ����
	readDataFromFile();

	// ���µ�ǰҳ��Ҫչʾ������
	return updateCurrentPage(1);
}

