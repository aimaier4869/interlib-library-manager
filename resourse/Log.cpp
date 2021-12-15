
#include "../include/Log.h"


Log::Log() {
	username = "";
	ISBN = "";
	state = 0;
};
Log::Log(string logUname, string logISBN, int logState) {
	username = logUname;
	ISBN = logISBN;
	state = logState;
};


