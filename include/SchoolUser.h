#include <fstream>
using namespace std;

#ifndef SCHOOLUSER_H
#define SCHOOLUSER_H

// 学校用户类，主要用途是储存信息（描述信息结构）
class SchoolUser {
	public:
		string password; // 密码，如果把密码设置成private时写入文件时会很麻烦
		string username; // 用户名，学号工号
		SchoolUser();
		SchoolUser(string uname, string pwd);
		~SchoolUser();
		// 验证密码是否正确，正确返回true，不正确返回false
		bool checkPwd(string pwd);
		// 更改密码
		void changePwd(string pwd);
};

#endif
