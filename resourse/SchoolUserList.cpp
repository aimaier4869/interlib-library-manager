#include <fstream>
#include "../include/SchoolUser.h"

#include "../include/SchoolUserList.h"

#include <iostream>
using namespace std;

// ѧУ�û��б��࣬��Ҫ���ܴ洢�û��������û�����ҳչʾʱ�����ݴ��������û���ɾ���û���������������

SchoolUserList::SchoolUserList() {
	// ��ǰҳ����Ϊ 0
	currentPageIndex = 0;
	currentPageCount = 0;

	// ���ļ��ж�ȡ����
	readDataFromFile();

	// ��ǰҳ��Ҫչʾ���û��б�
	updataCurrentPage(1);
};
// ��ȡ�ļ��е����ݲ����µ������У������û�ɾ���û�ʱ��Ҫ���»�ȡ���ݣ����Է�װ����������
void SchoolUserList::readDataFromFile() {
	// ��ʼ���ļ��ж�ȡ
	fstream fs;
	// �Ȼ�ȡ��Ϣ
	fs.open("database\\SchoolUsersInfo.txt", ios::in);
	fs >> totalCount;
	// �ر��ļ�
	fs.close();

	// ���֮ǰ�������Ǿ�ɾ��
//			if(usersArr != NULL) {
//				delete[] usersArr;
//				usersArr = NULL;
//			}

	// ��ʼ��ȡÿһ���û�
	usersArr = new SchoolUser[totalCount];
	fs.open("database\\SchoolUsers.txt", ios::in);
	for(int i = 0; i < totalCount; i++) {
		string uname, pwd;
		fs >> uname >> pwd;
		usersArr[i] = SchoolUser(uname, pwd);
	}
	// �ر��ļ�
	fs.close();
}
// ��������
SchoolUserList::~SchoolUserList() {
	delete currentPageUsersArr;
};
// ͨ���û����ҵ�Ψһ���û����ҵ��˷���1��δ�ҵ�����0;
int SchoolUserList::searchUserByUname(string uname) {
	// ���ʲô��û������ô��ת��1ҳ
	if(uname == "") {
		return updataCurrentPage(1);
	}
	// ��ʼ����
	for(int i = 0; i < totalCount; i++) {
		if(uname == usersArr[i].username) {
			// �ҵ���
			// debug �������һ��ע��ʱ�ᱨ��
//					clearCurrentPageUsersArr(); // �����ǰҳ����
			currentPageUsersArr = new SchoolUser*[1]; // �½�����Ϊ1������
			currentPageUsersArr[0] = &usersArr[i];
			currentPageCount = 1;
			return 1;
		}
	}
	currentPageCount = 0;
	return 0;
};
// �û���¼,-1���û������ڣ�0���벻��ȷ��1��¼�ɹ�
int SchoolUserList::userLogin(string username, string pwd) { 
	int len = searchUserByUname(username);
	//  �û�������
	if(len == 0) {
		return -1;
	}
	return currentPageUsersArr[0]->checkPwd(pwd);
}
// �޸����룬-1����ĵ�ǰ���벻��ȷ��1�޸ĳɹ�
int SchoolUserList::userChangePwd(string username, string pwd, string newPwd) {
	int len = searchUserByUname(username);
	if(!currentPageUsersArr[0]->checkPwd(pwd)) {
		return -1;
	}
	currentPageUsersArr[0]->changePwd(newPwd);
	return 1;
}

// ��ҳչʾ��������ת֮��ҳ���е���������
// pageIndexҪ��ת���ڼ�ҳ��countÿҳչʾ���������ݣ�Ĭ��10��
// �����ⲿ�ж��Ƿ���Ե����һҳ����֤�������pageIndex�ǲ�С��0���Ҳ�������ҳ��
// ���pageIndex���˵��´��뱨���Ҳ���
// ������getTotalPageCount�����õ���ҳ��
int SchoolUserList::updataCurrentPage(int pageIndex, int count) {

	// Ҫ��ת��ҳ�����������
	int len = count;
	// ���ﴦ�����һҳ�������ݲ���count��ʱ�����
	if(totalCount - (pageIndex - 1) * count < count) {
		len = totalCount - (pageIndex - 1) * count;
	}

	// ��ʼ�޸ĸ���ҳ������
	// debug����·�ע�ͻᱨ��
//			clearCurrentPageUsersArr(); // �����ǰҳ����
	currentPageUsersArr = new SchoolUser*[len]; // �½�����Ϊlen������

	for(int i = 0; i < len; i++) {
		// debug:������ܻ���������������Ҳ��֪�����������ǵù��������ǲ�������
//				cout <<  ((pageIndex - 1) * count + i);
		currentPageUsersArr[i] = &usersArr[(pageIndex - 1) * count + i];
	}

	currentPageIndex = pageIndex;
	currentPageCount = len;
	return len;
}
// ��ȡÿҳչʾcount�����ݵĻ������Էֶ���ҳ
int SchoolUserList::getTotalPageCount(int count) {
	// ����������û�����ôҳ����ֻ��һ�����ݲ���ֻ��һҳ����ֹ��������ҳ
	if(currentPageCount == 1 || currentPageCount == 0) {
		return 1;
	}
	// ����ܱ�����
	if(totalCount % count == 0) {
		return totalCount / count;
	} else {
		return totalCount / count + 1;
	}
};
// �������룬����currentPageUsersArr�е�index
void SchoolUserList::resetPassword(int index) {
	currentPageUsersArr[index]->changePwd("123456");
};
// ɾ���û�������currentPageUsersArr�е�index
void SchoolUserList::removeUser(int index) {
	// ɾ���û������ҪɾŶ�����ָܻ���
	fstream fs;
	fs.open("database\\SchoolUsers.txt", ios::out);
	for(int i = 0; i < totalCount; i++) {
		if(usersArr[i].username == currentPageUsersArr[index]->username) {
			continue;
		}
		fs << usersArr[i].username << " " << usersArr[i].password << "\n";
	};
	// �ر��ļ�
	fs.close();
	// ������Ϣ
	fs.open("database\\SchoolUsersInfo.txt", ios::out);
	fs << --totalCount;
	// �ر��ļ�
	fs.close();

	// ��ô�죿���¶�ȡ�� ��
	// ���ļ��ж�ȡ����
	readDataFromFile();

	// ���µ�ǰҳ��Ҫչʾ������
	updataCurrentPage(1);
};
// �����û��������ɹ����ص�ǰҳ�û����� ,ʧ���˷���-1
int SchoolUserList::addUserByUname(string uname) {
	if(searchUserByUname(uname)) {
		return -1;
	}
	// ����û�����ӵ���ǰ��
	fstream fs;
	fs.open("database\\SchoolUsers.txt", ios::out);
	fs << uname << " 123456\n";
	for(int i = 0; i < totalCount; i++) {
		fs << usersArr[i].username << " " << usersArr[i].password << "\n";
	};
	// �ر��ļ�
	fs.close();
	// ������Ϣ
	fs.open("database\\SchoolUsersInfo.txt", ios::out);
	fs << ++totalCount;
	// �ر��ļ�
	fs.close();

	// ��ô�죿���¶�ȡ�� ��
	// ���ļ��ж�ȡ����
	readDataFromFile();

	// ���µ�ǰҳ��Ҫչʾ������
	return updataCurrentPage(1);
}
