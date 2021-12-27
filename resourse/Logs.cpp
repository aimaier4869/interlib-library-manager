#include <fstream>
#include "../include/Log.h"
#include "../include/variable.h"
#include "../include/Logs.h"

#include <iostream>
using namespace std;

Logs::Logs() {
	// ��ǰҳ����Ϊ 0
	currentPageIndex = 0;
	currentPageCount = 0;

	// ���ļ��ж�ȡ����
	readDataFromFile();

	// ɸѡ����ǰ��¼���û��ļ�¼
	updateCurrentUserLogs();

	// ��ǰҳ��Ҫչʾ��ͼ���б�
	updateCurrentPage(1);
//			cout << searchBook(Book("", "", "", "T"));
//			cout << currentPageBooksArr[0]->name;
};
// ��ȡ�ļ��е����ݲ����µ������У������û�ɾ���û�ʱ��Ҫ���»�ȡ���ݣ����Է�װ����������
void Logs::readDataFromFile() {
	// ��ʼ���ļ��ж�ȡ
	fstream fs;
	// �Ȼ�ȡ��Ϣ
	fs.open("database\\LogsInfo.txt", ios::in);
	fs >> totalCount;
	// �ر��ļ�
	fs.close();
	if(logsArr != NULL) {
		delete[] logsArr;
	}
	// ��ʼ��ȡÿһ����¼����Ϣ
	logsArr = new Log[totalCount];
	
	fs.open("database\\Logs.txt", ios::in);
	for(int i = 0; i < totalCount; i++) {
		string username, ISBN;
		int state;
		fs >> username >> ISBN >> state;
		logsArr[i] = Log(username, ISBN, state);
	}
	// �ر��ļ�
	fs.close();
}
// ���µ�ǰ��¼���û��ļ�¼��Ϣ
void Logs::updateCurrentUserLogs() {
	int len = 0;
	// ���㹲�ж�������¼
	for(int i = 0; i < totalCount; i++) {
		if(logsArr[i].username == currentUser) {
			len++;
		}
	}
	tempLogsArrLen = len;
	if(tempLogsArr != NULL) {
		delete[] tempLogsArr;
	}
	// ����������֤���ڵ�������
	tempLogsArr = new Log*[len]; // �½�����Ϊlen������
	for(int i = 0, z = 0; i < totalCount; i++) {
		if(logsArr[i].username == currentUser) {
			tempLogsArr[z] = &logsArr[i];
			z++;
		}
	}
}
// ͨ���������ң������ҵ���������û�ҵ�����0;
int Logs::searchLogByISBN(string ISBN) {
	// ���ʲô��û������ô��ת��1ҳ
	if(ISBN == "") {
		return updateCurrentPage(1);
	}
	if(currentPageLogsArr != NULL) {
		delete[] currentPageLogsArr;
	}
	// ��ʼ����
	for(int i = 0; i < tempLogsArrLen; i++) {
		if(ISBN == tempLogsArr[i]->ISBN) {
			// �ҵ���
			// debug �������һ��ע��ʱ�ᱨ��
			currentPageLogsArr = new Log*[1]; // �½�����Ϊ1������
			currentPageLogsArr[0] = tempLogsArr[i];
			currentPageCount = 1;
			return 1;
		}
	}
	currentPageCount = 0;
	return 0;
};
// ��ҳչʾ��������ת֮��ҳ���е���������
// pageIndexҪ��ת���ڼ�ҳ��countÿҳչʾ���������ݣ�Ĭ��10��
// �����ⲿ�ж��Ƿ���Ե����һҳ����֤�������pageIndex�ǲ�С��0���Ҳ�������ҳ��
// ���pageIndex���˵��´��뱨���Ҳ���
// ������getTotalPageCount�����õ���ҳ��
int Logs::updateCurrentPage(int pageIndex, int count) {
	// Ҫ��ת��ҳ�����������
	int len = count;
	// ��ʱ������Ⱦ
	if(tempLogsArrLen - (pageIndex - 1) * count < count) {
		len = tempLogsArrLen - (pageIndex - 1) * count;
	}
	// ��ʼ�޸ĸ���ҳ������
	currentPageLogsArr = new Log*[len]; // �½�����Ϊlen������
	for(int i = 0; i < len; i++) {
		// debug:������ܻ���������������Ҳ��֪�����������ǵù��������ǲ�������
//				cout <<  ((pageIndex - 1) * count + i);
		currentPageLogsArr[i] = tempLogsArr[(pageIndex - 1) * count + i];
	}
	currentPageIndex = pageIndex;
	currentPageCount = len;
	return len;
}
// ��ȡÿҳչʾcount�����ݵĻ������Էֶ���ҳ
int Logs::getTotalPageCount(int count) {
	if(tempLogsArrLen % count == 0) {
		return tempLogsArrLen / count;
	} else {
		return tempLogsArrLen / count + 1;
	}
};
//		 ����ͼ�飬����ISBN���û�Ĭ��Ϊ��ǰ�û�
// ����ʧ�ܷ���-1
int Logs::borrowBook(string ISBN) {
	// ���һ���ǲ���֮ǰ�������飬���һ�û��
	for(int i = 0; i < tempLogsArrLen; i++) {
		if(tempLogsArr[i]->ISBN == ISBN && tempLogsArr[i]->state == 0) {
			return -1;
		}
	}
//			// д����Ϣ��д����ǰ��
	fstream fs;
	fs.open("database\\Logs.txt", ios::out);
	fs << currentUser << " " << ISBN << " " << 0 << "\n";
	for(int i = 0; i < totalCount; i++) {
		fs << logsArr[i].username << " " << logsArr[i].ISBN << " " << logsArr[i].state << "\n";
	};
	// �ر��ļ�
	fs.close();
	// ������Ϣ
	fs.open("database\\LogsInfo.txt", ios::out);
	fs << ++totalCount;
	// �ر��ļ�
	fs.close();
//
//			// ��ô�죿���¶�ȡ�� ��
//			// ���ļ��ж�ȡ����
	readDataFromFile();

	// ɸѡ����ǰ��¼���û��ļ�¼
	updateCurrentUserLogs();
//
//			// ���µ�ǰҳ��Ҫչʾ������
	return updateCurrentPage(1);
};
//		// �黹ͼ�飬�黹ʧ�ܷ���-1
int Logs::returnBook(string ISBN) {
	//			// д����Ϣ��д����ǰ��
	fstream fs;
	fs.open("database\\Logs.txt", ios::out);

	for(int i = 0; i < totalCount; i++) {
		if(logsArr[i].username == currentUser && ISBN == logsArr[i].ISBN) {
			fs << logsArr[i].username << " " << logsArr[i].ISBN << " " << 1 << "\n";
			continue;
		}
		fs << logsArr[i].username << " " << logsArr[i].ISBN << " " << logsArr[i].state << "\n";
	};
	// �ر��ļ�
	fs.close();
//
//			// ��ô�죿���¶�ȡ�� ��
//			// ���ļ��ж�ȡ����
	readDataFromFile();

	// ɸѡ����ǰ��¼���û��ļ�¼
	updateCurrentUserLogs();
//
//			// ���µ�ǰҳ��Ҫչʾ������
	return updateCurrentPage(1);
}


