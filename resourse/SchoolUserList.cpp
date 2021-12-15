#include <fstream>
#include "../include/SchoolUser.h"

#include "../include/SchoolUserList.h"

#include <iostream>
using namespace std;

// 学校用户列表类，主要功能存储用户，搜索用户，分页展示时的数据处理，新增用户，删除用户，调用重置密码

SchoolUserList::SchoolUserList() {
	// 当前页设置为 0
	currentPageIndex = 0;
	currentPageCount = 0;

	// 从文件中读取数据
	readDataFromFile();

	// 当前页需要展示的用户列表
	updataCurrentPage(1);
};
// 读取文件中的数据并更新到属性中，新增用户删除用户时需要重新获取数据，所以封装到函数中了
void SchoolUserList::readDataFromFile() {
	// 开始从文件中读取
	fstream fs;
	// 先获取信息
	fs.open("database\\SchoolUsersInfo.txt", ios::in);
	fs >> totalCount;
	// 关闭文件
	fs.close();

	// 如果之前有数据那就删掉
//			if(usersArr != NULL) {
//				delete[] usersArr;
//				usersArr = NULL;
//			}

	// 开始读取每一个用户
	usersArr = new SchoolUser[totalCount];
	fs.open("database\\SchoolUsers.txt", ios::in);
	for(int i = 0; i < totalCount; i++) {
		string uname, pwd;
		fs >> uname >> pwd;
		usersArr[i] = SchoolUser(uname, pwd);
	}
	// 关闭文件
	fs.close();
}
// 析构函数
SchoolUserList::~SchoolUserList() {
	delete currentPageUsersArr;
};
// 通过用户名找到唯一的用户，找到了返回1，未找到返回0;
int SchoolUserList::searchUserByUname(string uname) {
	// 如果什么都没输入那么跳转第1页
	if(uname == "") {
		return updataCurrentPage(1);
	}
	// 开始查找
	for(int i = 0; i < totalCount; i++) {
		if(uname == usersArr[i].username) {
			// 找到了
			// debug 解除下面一行注释时会报错
//					clearCurrentPageUsersArr(); // 清掉当前页数组
			currentPageUsersArr = new SchoolUser*[1]; // 新建长度为1的数组
			currentPageUsersArr[0] = &usersArr[i];
			currentPageCount = 1;
			return 1;
		}
	}
	currentPageCount = 0;
	return 0;
};
// 用户登录,-1该用户不存在，0密码不正确，1登录成功
int SchoolUserList::userLogin(string username, string pwd) { 
	int len = searchUserByUname(username);
	//  用户不存在
	if(len == 0) {
		return -1;
	}
	return currentPageUsersArr[0]->checkPwd(pwd);
}
// 修改密码，-1输入的当前密码不正确，1修改成功
int SchoolUserList::userChangePwd(string username, string pwd, string newPwd) {
	int len = searchUserByUname(username);
	if(!currentPageUsersArr[0]->checkPwd(pwd)) {
		return -1;
	}
	currentPageUsersArr[0]->changePwd(newPwd);
	return 1;
}

// 分页展示，返回跳转之后页面中的数据数量
// pageIndex要跳转到第几页，count每页展示多少条数据，默认10条
// 请在外部判断是否可以点击下一页，保证你输入的pageIndex是不小于0并且不超过总页数
// 如果pageIndex错了导致代码报错我不管
// 可以用getTotalPageCount函数拿到总页数
int SchoolUserList::updataCurrentPage(int pageIndex, int count) {

	// 要跳转的页面的数据数量
	int len = count;
	// 这里处理最后一页数据内容不够count条时的情况
	if(totalCount - (pageIndex - 1) * count < count) {
		len = totalCount - (pageIndex - 1) * count;
	}

	// 开始修改更新页面数据
	// debug解除下方注释会报错
//			clearCurrentPageUsersArr(); // 清掉当前页数组
	currentPageUsersArr = new SchoolUser*[len]; // 新建长度为len的数组

	for(int i = 0; i < len; i++) {
		// debug:这里可能会出现数组溢出，我也不知道，如果出错记得过来看看是不是这里
//				cout <<  ((pageIndex - 1) * count + i);
		currentPageUsersArr[i] = &usersArr[(pageIndex - 1) * count + i];
	}

	currentPageIndex = pageIndex;
	currentPageCount = len;
	return len;
}
// 获取每页展示count条数据的话共可以分多少页
int SchoolUserList::getTotalPageCount(int count) {
	// 如果是搜索用户，那么页面中只有一条数据并且只有一页，防止搜索后跳页
	if(currentPageCount == 1 || currentPageCount == 0) {
		return 1;
	}
	// 如果能被整除
	if(totalCount % count == 0) {
		return totalCount / count;
	} else {
		return totalCount / count + 1;
	}
};
// 重置密码，传入currentPageUsersArr中的index
void SchoolUserList::resetPassword(int index) {
	currentPageUsersArr[index]->changePwd("123456");
};
// 删除用户，传入currentPageUsersArr中的index
void SchoolUserList::removeUser(int index) {
	// 删除用户，真的要删哦，不能恢复的
	fstream fs;
	fs.open("database\\SchoolUsers.txt", ios::out);
	for(int i = 0; i < totalCount; i++) {
		if(usersArr[i].username == currentPageUsersArr[index]->username) {
			continue;
		}
		fs << usersArr[i].username << " " << usersArr[i].password << "\n";
	};
	// 关闭文件
	fs.close();
	// 更新信息
	fs.open("database\\SchoolUsersInfo.txt", ios::out);
	fs << --totalCount;
	// 关闭文件
	fs.close();

	// 怎么办？重新读取？ 嗐
	// 从文件中读取数据
	readDataFromFile();

	// 更新当前页需要展示的数据
	updataCurrentPage(1);
};
// 新增用户，新增成功返回当前页用户数量 ,失败了返回-1
int SchoolUserList::addUserByUname(string uname) {
	if(searchUserByUname(uname)) {
		return -1;
	}
	// 添加用户，添加到最前面
	fstream fs;
	fs.open("database\\SchoolUsers.txt", ios::out);
	fs << uname << " 123456\n";
	for(int i = 0; i < totalCount; i++) {
		fs << usersArr[i].username << " " << usersArr[i].password << "\n";
	};
	// 关闭文件
	fs.close();
	// 更新信息
	fs.open("database\\SchoolUsersInfo.txt", ios::out);
	fs << ++totalCount;
	// 关闭文件
	fs.close();

	// 怎么办？重新读取？ 嗐
	// 从文件中读取数据
	readDataFromFile();

	// 更新当前页需要展示的数据
	return updataCurrentPage(1);
}
