
#ifndef LOG_H
#define LOG_H

#include <string>
using namespace std;

class Log {
	public:
		string username;
		string ISBN;
		int state; // 借阅状态，0表示还没还，1表示已经还回去了
		Log();
		Log(string logUname, string logISBN, int logState);
};

#endif

