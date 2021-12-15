#include <fstream>
using namespace std;

#include "../include/SchoolUser.h"

// 学校用户类，主要用途是储存信息（描述信息结构）

SchoolUser::SchoolUser() {
	username = "";
	password = "";
//			cout << "创建了SchoolUser；" ;
};
SchoolUser::SchoolUser(string uname, string pwd) {
	username = uname;
	password = pwd;
}
SchoolUser::~SchoolUser() {
//			cout << "析构了SchoolUser；" ;
};
// 验证密码是否正确，正确返回true，不正确返回false
bool SchoolUser::checkPwd(string pwd) {
	return pwd == password;
};
// 更改密码
void SchoolUser::changePwd(string pwd) {
	password = pwd;
	// 开始从文件中读取
	fstream fs;
	// 先获取信息
	int totalCount = 0;
	fs.open("database\\SchoolUsersInfo.txt", ios::in);
	fs >> totalCount;
	// 关闭文件
	fs.close();
	// 开始读取每一个用户
	SchoolUser * usersArr = new SchoolUser[totalCount];
	fs.open("database\\SchoolUsers.txt", ios::in);
	for(int i = 0; i < totalCount; i++) {
		string uname, pwd;
		fs >> uname >> pwd;
		usersArr[i] = SchoolUser(uname, pwd);
	}
	// 关闭文件
	fs.close();
	// 重写文件
	fs.open("database\\SchoolUsers.txt", ios::out);
	for(int i = 0; i < totalCount; i++) {
		if(usersArr[i].username == username) {
			fs << usersArr[i].username << " " << password << "\n";
		} else {
			fs << usersArr[i].username << " " << usersArr[i].password << "\n";
		}
	};
	// 关闭文件
	fs.close();
};
