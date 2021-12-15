#include <fstream>
#include "Book.h"

#ifndef LIBRARY_H
#define LIBRARY_H

class Library {
	private:
		Book * booksArr;
	public:
		int totalCount;
		Book ** currentPageBooksArr; // 当前页图书数组
		Book ** tempBooksArr; // 临时数组，搜索时使用
		int tempBooksArrLen;
		int updatePageMode; // 换页模式：0表示从总表中切换，1表示从当前结果中切换
		int currentPageIndex; // 当前在页面中展示的页面index
		int currentPageCount; // 当前页面中展示的用户数量
		Library() ;
		// 读取文件中的数据并更新到属性中，新增用户删除用户时需要重新获取数据，所以封装到函数中了
		void readDataFromFile();
		// 通过条件查找，返回找到的数量，没找到就是0;
		int searchBook(Book book);
		// 通过ISBN拿到图书名称，主要用于借阅记录
		string getBookNameByISBN(string ISBN) ;
		// 分页展示，返回跳转之后页面中的数据数量
		// pageIndex要跳转到第几页，count每页展示多少条数据，默认10条
		// 请在外部判断是否可以点击下一页，保证你输入的pageIndex是不小于0并且不超过总页数
		// 如果pageIndex错了导致代码报错我不管
		// 可以用getTotalPageCount函数拿到总页数
		int updateCurrentPage(int pageIndex, int count = 10);
		// 获取每页展示count条数据的话共可以分多少页
		int getTotalPageCount(int count = 10);
//		 删除图书，传入currentPageBooksArr中的index
		void removeBook(int index);
		// 新增图书，新增成功返回当前页图书数量 ,失败了返回-1
		int addBook(Book book);
		// 修改图书，新增成功返回当前页图书数量 ,失败了返回-1
		int modifyBook(Book book);
};

#endif
