#include <fstream>
#include "../include/Log.h"
#include "../include/variable.h"
#include "../include/Logs.h"

#include <iostream>
using namespace std;

Logs::Logs() {
	// 当前页设置为 0
	currentPageIndex = 0;
	currentPageCount = 0;

	// 从文件中读取数据
	readDataFromFile();

	// 筛选出当前登录的用户的记录
	updateCurrentUserLogs();

	// 当前页需要展示的图书列表
	updateCurrentPage(1);
//			cout << searchBook(Book("", "", "", "T"));
//			cout << currentPageBooksArr[0]->name;
};
// 读取文件中的数据并更新到属性中，新增用户删除用户时需要重新获取数据，所以封装到函数中了
void Logs::readDataFromFile() {
	// 开始从文件中读取
	fstream fs;
	// 先获取信息
	fs.open("database\\LogsInfo.txt", ios::in);
	fs >> totalCount;
	// 关闭文件
	fs.close();
	if(logsArr != NULL) {
		delete[] logsArr;
	}
	// 开始读取每一条记录的信息
	logsArr = new Log[totalCount];
	
	fs.open("database\\Logs.txt", ios::in);
	for(int i = 0; i < totalCount; i++) {
		string username, ISBN;
		int state;
		fs >> username >> ISBN >> state;
		logsArr[i] = Log(username, ISBN, state);
	}
	// 关闭文件
	fs.close();
}
// 更新当前登录的用户的记录信息
void Logs::updateCurrentUserLogs() {
	int len = 0;
	// 计算共有多少条记录
	for(int i = 0; i < totalCount; i++) {
		if(logsArr[i].username == currentUser) {
			len++;
		}
	}
	tempLogsArrLen = len;
	if(tempLogsArr != NULL) {
		delete[] tempLogsArr;
	}
	// 经过重重验证终于到这里了
	tempLogsArr = new Log*[len]; // 新建长度为len的数组
	for(int i = 0, z = 0; i < totalCount; i++) {
		if(logsArr[i].username == currentUser) {
			tempLogsArr[z] = &logsArr[i];
			z++;
		}
	}
}
// 通过条件查找，返回找到的数量，没找到就是0;
int Logs::searchLogByISBN(string ISBN) {
	// 如果什么都没输入那么跳转第1页
	if(ISBN == "") {
		return updateCurrentPage(1);
	}
	if(currentPageLogsArr != NULL) {
		delete[] currentPageLogsArr;
	}
	// 开始查找
	for(int i = 0; i < tempLogsArrLen; i++) {
		if(ISBN == tempLogsArr[i]->ISBN) {
			// 找到了
			// debug 解除下面一行注释时会报错
			currentPageLogsArr = new Log*[1]; // 新建长度为1的数组
			currentPageLogsArr[0] = tempLogsArr[i];
			currentPageCount = 1;
			return 1;
		}
	}
	currentPageCount = 0;
	return 0;
};
// 分页展示，返回跳转之后页面中的数据数量
// pageIndex要跳转到第几页，count每页展示多少条数据，默认10条
// 请在外部判断是否可以点击下一页，保证你输入的pageIndex是不小于0并且不超过总页数
// 如果pageIndex错了导致代码报错我不管
// 可以用getTotalPageCount函数拿到总页数
int Logs::updateCurrentPage(int pageIndex, int count) {
	// 要跳转的页面的数据数量
	int len = count;
	// 临时表中渲染
	if(tempLogsArrLen - (pageIndex - 1) * count < count) {
		len = tempLogsArrLen - (pageIndex - 1) * count;
	}
	// 开始修改更新页面数据
	currentPageLogsArr = new Log*[len]; // 新建长度为len的数组
	for(int i = 0; i < len; i++) {
		// debug:这里可能会出现数组溢出，我也不知道，如果出错记得过来看看是不是这里
//				cout <<  ((pageIndex - 1) * count + i);
		currentPageLogsArr[i] = tempLogsArr[(pageIndex - 1) * count + i];
	}
	currentPageIndex = pageIndex;
	currentPageCount = len;
	return len;
}
// 获取每页展示count条数据的话共可以分多少页
int Logs::getTotalPageCount(int count) {
	if(tempLogsArrLen % count == 0) {
		return tempLogsArrLen / count;
	} else {
		return tempLogsArrLen / count + 1;
	}
};
//		 借阅图书，传入ISBN，用户默认为当前用户
// 借阅失败返回-1
int Logs::borrowBook(string ISBN) {
	// 检查一下是不是之前借过这个书，并且还没还
	for(int i = 0; i < tempLogsArrLen; i++) {
		if(tempLogsArr[i]->ISBN == ISBN && tempLogsArr[i]->state == 0) {
			return -1;
		}
	}
//			// 写入信息，写到最前面
	fstream fs;
	fs.open("database\\Logs.txt", ios::out);
	fs << currentUser << " " << ISBN << " " << 0 << "\n";
	for(int i = 0; i < totalCount; i++) {
		fs << logsArr[i].username << " " << logsArr[i].ISBN << " " << logsArr[i].state << "\n";
	};
	// 关闭文件
	fs.close();
	// 更新信息
	fs.open("database\\LogsInfo.txt", ios::out);
	fs << ++totalCount;
	// 关闭文件
	fs.close();
//
//			// 怎么办？重新读取？ 嗐
//			// 从文件中读取数据
	readDataFromFile();

	// 筛选出当前登录的用户的记录
	updateCurrentUserLogs();
//
//			// 更新当前页需要展示的数据
	return updateCurrentPage(1);
};
//		// 归还图书，归还失败返回-1
int Logs::returnBook(string ISBN) {
	//			// 写入信息，写到最前面
	fstream fs;
	fs.open("database\\Logs.txt", ios::out);

	for(int i = 0; i < totalCount; i++) {
		if(logsArr[i].username == currentUser && ISBN == logsArr[i].ISBN) {
			fs << logsArr[i].username << " " << logsArr[i].ISBN << " " << 1 << "\n";
			continue;
		}
		fs << logsArr[i].username << " " << logsArr[i].ISBN << " " << logsArr[i].state << "\n";
	};
	// 关闭文件
	fs.close();
//
//			// 怎么办？重新读取？ 嗐
//			// 从文件中读取数据
	readDataFromFile();

	// 筛选出当前登录的用户的记录
	updateCurrentUserLogs();
//
//			// 更新当前页需要展示的数据
	return updateCurrentPage(1);
}


