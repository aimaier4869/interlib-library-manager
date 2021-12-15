// 学校用户图书借阅页

#include "../include/page_user_logs.h"
#include "../include/page_user_library.h" 
#include "../include/page_admin_userlist.h" 
#include "../include/util.h"
#include "../include/variable.h"

// 渲染操作区域
void click_user_logs_renderLogs(int len) {
	// 页面中的位置已写死了 
	// 清屏 
	for(int i = 0; i < 10; i++) {
		gotoxy(18 + i, 5);
		printChar(100 - 5, ' ');
	}
	// 输出信息 
	for(int i = 0; i < len; i++) {
		gotoxy(18 + i, 5);
		string bookName = lib.getBookNameByISBN(logs.currentPageLogsArr[i]->ISBN);
		if(bookName != "") {
			cout << bookName;
		} else {
			cout << "未找到，该图书可能已被删除！"; 
		}

		gotoxy(18 + i, 58);
		cout << logs.currentPageLogsArr[i]->ISBN; 
		gotoxy(18 + i, 84);
		if(!logs.currentPageLogsArr[i]->state) {
			// 如果是0输出尚未归还
			cout << "尚未归还"; 
		}else {
			cout << "";
		}
		
	}
//	 一页有10条内容也已经写死了 
	for(int i = 0; i < 10; i++) {
		if(i < len && !logs.currentPageLogsArr[i]->state) {
			gotoxy(18 + i, 100);
			cout << "归还";
		} else {
			gotoxy(18 + i, 100);
			printChar(8, ' ');
		}
	} 
} 

// 渲染页面信息区域
void click_user_logs_renderPageInfo() {
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	string totalPageCount = to_string(logs.getTotalPageCount(10));
	TextsArr[7].text = "当前第 " + to_string(logs.currentPageIndex) + " 页，共 " + totalPageCount + " 页。";
	// 渲染到页面中
	gotoxy(TextsArr[7].row, TextsArr[7].col);
	printChar(TextsArr[7].text.length(), ' '); 
	gotoxy(TextsArr[7].row, TextsArr[7].col);
	cout << TextsArr[7].text;
}

// 当搜索按钮被按下时 
void click_user_logs_search(const Link & self, int row, int col) {
	// 此时页面中必有四个输入框，分别为图书名称，作者，ISBN，分类号
	string ISBN = InputBoxsArr[0].value;
	logs.searchLogByISBN(ISBN);
//	// 渲染信息 
	click_user_logs_renderLogs();
//	// 更新底部的页面信息，此时页面中索引为7的元素必是页面信息 
	click_user_logs_renderPageInfo();
	msg("搜索成功！");
}

// 当借阅按钮被按下时
void click_user_logs_returnBook(const Link & self, int row, int col) {
	int index = row - 18;
	if(index < logs.currentPageCount && !logs.currentPageLogsArr[index]->state) {
		int len = logs.returnBook(logs.currentPageLogsArr[index]->ISBN);
		if(len != -1) {
			// 借阅成功重新点击搜索按钮恢复页面 
			click_user_logs_search(LinksArr[3], 0, 0);
			msg("归还图书成功！"); 
		} else {
			msg("归还图书失败！");
		}
	}
}

// 当下一页按钮被按下
void click_user_logs_nextPage(const Link & self, int row, int col) {
	int nextPage = logs.currentPageIndex + 1;
	if(nextPage > logs.getTotalPageCount(10)) {
		msg("没有下一页了哦");
		return;
	}
	// 切换页面 
	logs.updateCurrentPage(nextPage);
	click_user_logs_renderLogs(logs.currentPageCount);
	
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	click_user_logs_renderPageInfo();
	
	msg("已为你跳转到第 " + to_string(nextPage) + " 页");
}

// 当上一页按钮被按下
void click_user_logs_prevPage(const Link & self, int row, int col) {
	int prevPage = logs.currentPageIndex - 1;
	if(prevPage <= 0) {
		msg("没有上一页了哦");
		return;
	}
	// 切换页面 
	logs.updateCurrentPage(prevPage);
	click_user_logs_renderLogs(logs.currentPageCount);
	
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	click_user_logs_renderPageInfo();
	
	msg("已为你跳转到第 " + to_string(prevPage) + " 页");
}

void page_user_logs() {
	// Links
	linksArrLen = 8;
	Link * linksArr = new Link[linksArrLen];// 创建数组 
	linksArr[0] = Link(4, 3, "借阅图书",  click_tab_user_library);
	linksArr[1] = Link(4, 20, "*借阅记录", click_tab_user_logs);
	linksArr[2] = Link(4, 35, "帐户设置", click_tab_user_settings);
	linksArr[3] = Link(4, 108, "退出登录", click_logout);
	linksArr[4] = Link(10, 40, "| 搜索 |", click_user_logs_search);
	// 归还图书按钮区域 
	linksArr[5] = Link(18, 100, "", click_user_logs_returnBook, 10, 4);
	// 上一页下一页 
	linksArr[6] = Link(30, 5, "| 上一页 |", click_user_logs_prevPage);
	linksArr[7] = Link(30, 18, "| 下一页 |", click_user_logs_nextPage);
	
	if(LinksArr != NULL) {// 释放原本数组内容并重新指定 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 8;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(7, 3, "> 搜索");
	textsArr[1] = Text(10, 5, "ISBN：");
	textsArr[2] = Text(14, 3, "> 图书列表");
	textsArr[3] = Text(16, 5, "图书名称");
	textsArr[4] = Text(16, 58, "ISBN");
	textsArr[5] = Text(16, 84, "状态");
	textsArr[6] = Text(16, 100, "操作");
	textsArr[7] = Text(30, 30, ""); // 这是分页信息 
	textsArr[7].text = "当前第 1 页，共 1 页。";
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 1;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(10, 15, "ISBN", ""); // ISBN 
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
	click_user_logs_search(linksArr[4], 0, 0);
}
