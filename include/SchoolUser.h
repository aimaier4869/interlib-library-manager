#include <fstream>
using namespace std;

#ifndef SCHOOLUSER_H
#define SCHOOLUSER_H

// ѧУ�û��࣬��Ҫ��;�Ǵ�����Ϣ��������Ϣ�ṹ��
class SchoolUser {
	public:
		string password; // ���룬������������ó�privateʱд���ļ�ʱ����鷳
		string username; // �û�����ѧ�Ź���
		SchoolUser();
		SchoolUser(string uname, string pwd);
		~SchoolUser();
		// ��֤�����Ƿ���ȷ����ȷ����true������ȷ����false
		bool checkPwd(string pwd);
		// ��������
		void changePwd(string pwd);
};

#endif
