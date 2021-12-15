#include <fstream>
#include "../include/Book.h"
#include "../include/Library.h"

#include <iostream>
using namespace std;


Library::Library() {
	// 当前页设置为 0
	currentPageIndex = 0;
	currentPageCount = 0;
	updatePageMode = 0;

	// 从文件中读取数据
	readDataFromFile();

	// 当前页需要展示的图书列表
	updateCurrentPage(1);
//			cout << searchBook(Book("", "", "", "T"));
//			cout << currentPageBooksArr[0]->name;
};
// 读取文件中的数据并更新到属性中，新增用户删除用户时需要重新获取数据，所以封装到函数中了
void Library::readDataFromFile() {
	// 开始从文件中读取
	fstream fs;
	// 先获取信息
	fs.open("database\\LibraryInfo.txt", ios::in);
	fs >> totalCount;
	// 关闭文件
	fs.close();
	// 开始读取每一本书的信息
	booksArr = new Book[totalCount];
	fs.open("database\\Library.txt", ios::in);
	for(int i = 0; i < totalCount; i++) {
		string name, author, ISBN, type;
		fs >> name >> author >> ISBN >> type;
		booksArr[i] = Book(name, author, ISBN, type);
	}
	// 关闭文件
	fs.close();
}
// 通过条件查找，返回找到的数量，没找到就是0;
int Library::searchBook(Book book) {

	if(book.name == "" && book.author == "" && book.ISBN == "" && book.type == "") {
		// 什么都没输入，切换为总表中渲染分页
		updatePageMode = 0;
		return updateCurrentPage(1);
	}

	int len = 0;
	// 开始查找
	for(int i = 0; i < totalCount; i++) {
		bool checkBookName = false;
		bool checkAuthor = false;
		bool checkISBN = false;
		bool checkType = false;

		if(book.name == "") { // 如果是空那就忽略该项
			checkBookName = true;
		} else if(book.name != booksArr[i].name) {
			continue;
		}

		if(book.author == "") { // 如果是空那就忽略该项
			checkAuthor = true;
		} else if(book.author != booksArr[i].author) {
			continue;
		}

		if(book.ISBN == "") { // 如果是空那就忽略该项
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
		// 经过重重验证终于到这里了
		len++;
		Book ** temp = tempBooksArr;
		tempBooksArr = new Book*[len]; // 新建长度为len的数组
		for(int j = 0; j < len - 1; j++) {
			tempBooksArr[j] = temp[j];
		}
		tempBooksArr[len - 1] = &booksArr[i];
	}

	// 有搜索结果了，分页要用临时数组展示
	updatePageMode = 1;
	tempBooksArrLen = len;
	updateCurrentPage(1);
	return len;
};
// 通过ISBN拿到图书名称，主要用于借阅记录
string Library::getBookNameByISBN(string ISBN) {
	for(int i = 0; i < totalCount; i++) {
		if(ISBN == booksArr[i].ISBN) {
			return booksArr[i].name;
		}
	}
	return "";
}
// 分页展示，返回跳转之后页面中的数据数量
// pageIndex要跳转到第几页，count每页展示多少条数据，默认10条
// 请在外部判断是否可以点击下一页，保证你输入的pageIndex是不小于0并且不超过总页数
// 如果pageIndex错了导致代码报错我不管
// 可以用getTotalPageCount函数拿到总页数
int Library::updateCurrentPage(int pageIndex, int count) {

	// 要跳转的页面的数据数量
	int len = count;

	// 总表中渲染
	if(!updatePageMode) {
		// 这里处理最后一页数据内容不够count条时的情况
		if(totalCount - (pageIndex - 1) * count < count) {
			len = totalCount - (pageIndex - 1) * count;
		}
		// 开始修改更新页面数据
		currentPageBooksArr = new Book*[len]; // 新建长度为len的数组
		for(int i = 0; i < len; i++) {
			// debug:这里可能会出现数组溢出，我也不知道，如果出错记得过来看看是不是这里
			//				cout <<  ((pageIndex - 1) * count + i);
			currentPageBooksArr[i] = &booksArr[(pageIndex - 1) * count + i];
		}
	} else {
		// 临时表中渲染
		if(tempBooksArrLen - (pageIndex - 1) * count < count) {
			len = tempBooksArrLen - (pageIndex - 1) * count;
		}
		// 开始修改更新页面数据
		currentPageBooksArr = new Book*[len]; // 新建长度为len的数组
		for(int i = 0; i < len; i++) {
			// debug:这里可能会出现数组溢出，我也不知道，如果出错记得过来看看是不是这里
			//				cout <<  ((pageIndex - 1) * count + i);
			currentPageBooksArr[i] = tempBooksArr[(pageIndex - 1) * count + i];
		}
	}
	currentPageIndex = pageIndex;
	currentPageCount = len;
	return len;
}
// 获取每页展示count条数据的话共可以分多少页
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
//		 删除图书，传入currentPageBooksArr中的index
void Library::removeBook(int index) {
	// 删除用户，真的要删哦，不能恢复的
	fstream fs;
	fs.open("database\\Library.txt", ios::out);
	for(int i = 0; i < totalCount; i++) {
		if(booksArr[i].ISBN == currentPageBooksArr[index]->ISBN) {
			continue;
		}
		fs << booksArr[i].name << " " << booksArr[i].author << " " << booksArr[i].ISBN << " " <<booksArr[i].type << " " << "\n";
	};
	// 关闭文件
	fs.close();
	// 更新信息
	fs.open("database\\LibraryInfo.txt", ios::out);
	fs << --totalCount;
	// 关闭文件
	fs.close();

	// 怎么办？重新读取？ 嗐
	// 从文件中读取数据
	readDataFromFile();

	// 更新当前页需要展示的数据
	updateCurrentPage(1);
};
// 新增图书，新增成功返回当前页图书数量 ,失败了返回-1
int Library::addBook(Book book) {
	if(searchBook(Book("", "", book.ISBN, ""))) {
		return -1;
	}
	// 添加图书，添加到最前面
	fstream fs;
	fs.open("database\\Library.txt", ios::out);
	fs << book.name << " " << book.author << " " << book.ISBN << " " << book.type << "\n";
	for(int i = 0; i < totalCount; i++) {
		string name, author, ISBN, type;
		fs << booksArr[i].name << " " << booksArr[i].author << " " << booksArr[i].ISBN << " " << booksArr[i].type << "\n";
	}
	// 关闭文件
	fs.close();
	// 更新信息
	fs.open("database\\LibraryInfo.txt", ios::out);
	fs << ++totalCount;
	// 关闭文件
	fs.close();

	// 怎么办？重新读取？ 嗐
	// 从文件中读取数据
	readDataFromFile();

	// 更新当前页需要展示的数据
	return updateCurrentPage(1);
}
// 修改图书，新增成功返回当前页图书数量 ,失败了返回-1
int Library::modifyBook(Book book) {
	if(!searchBook(Book("", "", book.ISBN, ""))) {
		return -1;
	}
	// 添加图书，添加到最前面
	fstream fs;
	fs.open("database\\Library.txt", ios::out);
	for(int i = 0; i < totalCount; i++) {
		if(booksArr[i].ISBN == book.ISBN) {
			fs << book.name << " " << book.author << " " << book.ISBN << " " << book.type << "\n";
		} else {
			fs << booksArr[i].name << " " << booksArr[i].author << " " << booksArr[i].ISBN << " " << booksArr[i].type << "\n";
		}
	}
	// 关闭文件
	fs.close();

	// 怎么办？重新读取？ 嗐
	// 从文件中读取数据
	readDataFromFile();

	// 更新当前页需要展示的数据
	return updateCurrentPage(1);
}

