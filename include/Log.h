
#ifndef LOG_H
#define LOG_H

#include <string>
using namespace std;

class Log {
	public:
		string username;
		string ISBN;
		int state; // ����״̬��0��ʾ��û����1��ʾ�Ѿ�����ȥ��
		Log();
		Log(string logUname, string logISBN, int logState);
};

#endif

