#include <fstream>
#include "Log.h"

#ifndef LOGS_H
#define LOGS_H

class Logs {
	private:
		Log * logsArr;
	public:
		int totalCount;
		Log ** currentPageLogsArr; // 当前页图书数组
		Log ** tempLogsArr; // 临时数组，文件读取完成后请把该用户的所有记录找出来放到这个数组中
		int tempLogsArrLen;
//		int searchMode; // 搜索模式：0表示从总表中搜索，1表示从临时表中搜索
//		int updatePageMode; // 换页模式：0表示从总表中切换，1表示从当前结果中切换
		int currentPageIndex; // 当前在页面中展示的页面index
		int currentPageCount; // 当前页面中展示的用户数量
		Logs();
		// 读取文件中的数据并更新到属性中，新增用户删除用户时需要重新获取数据，所以封装到函数中了
		void readDataFromFile();
		// 更新当前登录的用户的记录信息
		void updateCurrentUserLogs();
		// 通过条件查找，返回找到的数量，没找到就是0;
		int searchLogByISBN(string ISBN);
		// 分页展示，返回跳转之后页面中的数据数量
		// pageIndex要跳转到第几页，count每页展示多少条数据，默认10条
		// 请在外部判断是否可以点击下一页，保证你输入的pageIndex是不小于0并且不超过总页数
		// 如果pageIndex错了导致代码报错我不管
		// 可以用getTotalPageCount函数拿到总页数
		int updateCurrentPage(int pageIndex, int count = 10);
		// 获取每页展示count条数据的话共可以分多少页
		int getTotalPageCount(int count = 10);
//		 借阅图书，传入ISBN，用户默认为当前用户
		// 借阅失败返回-1
		int borrowBook(string ISBN);
//		// 归还图书，归还失败返回-1
		int returnBook(string ISBN);
};

#endif
