#include <fstream>
using namespace std;

#include "../include/SchoolUser.h"

// ѧУ�û��࣬��Ҫ��;�Ǵ�����Ϣ��������Ϣ�ṹ��

SchoolUser::SchoolUser() {
	username = "";
	password = "";
//			cout << "������SchoolUser��" ;
};
SchoolUser::SchoolUser(string uname, string pwd) {
	username = uname;
	password = pwd;
}
SchoolUser::~SchoolUser() {
//			cout << "������SchoolUser��" ;
};
// ��֤�����Ƿ���ȷ����ȷ����true������ȷ����false
bool SchoolUser::checkPwd(string pwd) {
	return pwd == password;
};
// ��������
void SchoolUser::changePwd(string pwd) {
	password = pwd;
	// ��ʼ���ļ��ж�ȡ
	fstream fs;
	// �Ȼ�ȡ��Ϣ
	int totalCount = 0;
	fs.open("database\\SchoolUsersInfo.txt", ios::in);
	fs >> totalCount;
	// �ر��ļ�
	fs.close();
	// ��ʼ��ȡÿһ���û�
	SchoolUser * usersArr = new SchoolUser[totalCount];
	fs.open("database\\SchoolUsers.txt", ios::in);
	for(int i = 0; i < totalCount; i++) {
		string uname, pwd;
		fs >> uname >> pwd;
		usersArr[i] = SchoolUser(uname, pwd);
	}
	// �ر��ļ�
	fs.close();
	// ��д�ļ�
	fs.open("database\\SchoolUsers.txt", ios::out);
	for(int i = 0; i < totalCount; i++) {
		if(usersArr[i].username == username) {
			fs << usersArr[i].username << " " << password << "\n";
		} else {
			fs << usersArr[i].username << " " << usersArr[i].password << "\n";
		}
	};
	// �ر��ļ�
	fs.close();
};
