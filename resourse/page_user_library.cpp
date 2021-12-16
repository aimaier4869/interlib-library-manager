// 学校用户图书借阅页 

#include "../include/page_user_library.h"
#include "../include/page_admin_userlist.h"
#include "../include/util.h"
#include "../include/variable.h"
#include "../include/router.h"

// 渲染操作区域
void click_user_library_renderBookList(int len) {
	// 页面中的位置已写死了 
	// 清屏 
	for(int i = 0; i < 10; i++) {
		gotoxy(18 + i, 5);
		printChar(100 - 5, ' ');
	}
	// 输出信息 
	for(int i = 0; i < len; i++) {
		gotoxy(18 + i, 5);
		cout << lib.currentPageBooksArr[i]->name;
		
		// debug:汉字和英文混合无法正常截取 
		// 截取图书名称 
		gotoxy(18 + i, 34);
		printChar(6, ' ');
		
		gotoxy(18 + i, 40);
		cout << lib.currentPageBooksArr[i]->author;
		
		// 截取作者名称 
		gotoxy(18 + i, 60);
		printChar(50, ' ');

		gotoxy(18 + i, 66);
		cout << lib.currentPageBooksArr[i]->ISBN; 
		gotoxy(18 + i, 86);
		cout << lib.currentPageBooksArr[i]->type; 
		
	}
//	 一页有10条内容也已经写死了 
	for(int i = 0; i < 10; i++) {
		if(i < len) {
			gotoxy(18 + i, 100);
			cout << "借阅";
		} else {
			gotoxy(18 + i, 100);
			printChar(8, ' ');
		}
	} 
} 

// 渲染页面信息区域
void click_user_library_renderPageInfo() {
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	string totalPageCount = to_string(lib.getTotalPageCount(10));
	TextsArr[11].text = "当前第 " + to_string(lib.currentPageIndex) + " 页，共 " + totalPageCount + " 页。";
	// 渲染到页面中
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	printChar(60, ' ');
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	printChar(TextsArr[11].text.length(), ' '); 
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	cout << TextsArr[11].text;
}

// 当搜索按钮被按下时 
void click_user_library_search(const Link & self, int row, int col) {
	// 此时页面中必有四个输入框，分别为图书名称，作者，ISBN，分类号
	Book book = {InputBoxsArr[0].value, InputBoxsArr[1].value, InputBoxsArr[2].value, InputBoxsArr[3].value}; 
	msg("正在搜索图书，请耐心等待。。。");
	lib.searchBook(book);
	// 渲染信息 
	click_user_library_renderBookList();
	// 更新底部的页面信息，此时页面中索引为11的元素必是页面信息 
	click_user_library_renderPageInfo();
	msg("搜索成功！");
}

// 当借阅按钮被按下时
void click_user_library_borrowBook(const Link & self, int row, int col) {
	int index = row - 18;
	if(index < lib.currentPageCount) {
		int len = logs.borrowBook(lib.currentPageBooksArr[index]->ISBN);
		if(len != -1) {
			// 借阅成功重新点击搜索按钮恢复页面 
			click_user_library_search(LinksArr[3], 0, 0);
			msg("借阅图书成功！"); 
		} else {
			msg("你已经有借阅这本书并且尚未归还");
		}
	}
}

// 当下一页按钮被按下
void click_user_library_nextPage(const Link & self, int row, int col) {
	int nextPage = lib.currentPageIndex + 1;
	if(nextPage > lib.getTotalPageCount(10)) {
		msg("没有下一页了哦");
		return;
	}
	// 切换页面 
	lib.updateCurrentPage(nextPage);
	click_user_library_renderBookList(lib.currentPageCount);
	
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	click_user_library_renderPageInfo();
	
	msg("已为你跳转到第 " + to_string(nextPage) + " 页");
}

// 当上一页按钮被按下
void click_user_library_prevPage(const Link & self, int row, int col) {
	int prevPage = lib.currentPageIndex - 1;
	if(prevPage <= 0) {
		msg("没有上一页了哦");
		return;
	}
	// 切换页面 
	lib.updateCurrentPage(prevPage);
	click_user_library_renderBookList(lib.currentPageCount);
	
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	click_user_library_renderPageInfo();
	
	msg("已为你跳转到第 " + to_string(prevPage) + " 页");
}

// 借阅图书导航按钮被按下 
void click_tab_user_library(const Link & self, int row, int col) {
	checkoutPage("page_user_library"); 
	msg("借阅图书页面"); 
}

// 借阅记录导航按钮被按下 
void click_tab_user_logs(const Link & self, int row, int col) {
	checkoutPage("page_user_logs"); 
	msg("借阅记录页面"); 
}

// 帐户设置导航按钮被按下 
void click_tab_user_settings(const Link & self, int row, int col) {
	checkoutPage("page_user_settings"); 
	msg("帐户设置页面"); 
}

void page_user_library() {
	// Links
	linksArrLen = 8;
	Link * linksArr = new Link[linksArrLen];// 创建数组 
	linksArr[0] = Link(4, 3, "*借阅图书",  click_tab_user_library);
	linksArr[1] = Link(4, 20, "借阅记录", click_tab_user_logs);
	linksArr[2] = Link(4, 35, "帐户设置", click_tab_user_settings);
	linksArr[3] = Link(4, 108, "退出登录", click_logout);
	linksArr[4] = Link(12, 100, "| 搜索 |", click_user_library_search);
	// 删除图书按钮区域 
	linksArr[5] = Link(18, 100, "", click_user_library_borrowBook, 10, 4);
	// 上一页下一页 
	linksArr[6] = Link(30, 5, "| 上一页 |", click_user_library_prevPage);
	linksArr[7] = Link(30, 18, "| 下一页 |", click_user_library_nextPage);
	
	if(LinksArr != NULL) {// 释放原本数组内容并重新指定 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 12;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(7, 3, "> 搜索");
	textsArr[1] = Text(9, 5, "图书名称：");
	textsArr[2] = Text(9, 60, "作者：");
	textsArr[3] = Text(11, 5, "ISBN：");
	textsArr[4] = Text(11, 60, "分类号：");
	textsArr[5] = Text(14, 3, "> 图书列表");
	textsArr[6] = Text(16, 5, "图书名称");
	textsArr[7] = Text(16, 40, "作者");
	textsArr[8] = Text(16, 66, "ISBN");
	textsArr[9] = Text(16, 86, "分类号");
	textsArr[10] = Text(16, 100, "操作");
	textsArr[11] = Text(30, 30, ""); // 这是分页信息 
	textsArr[11].text = "当前第 1 页，共 1 页。";
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 4;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(9, 15, "图书名称", ""); // 图书名称 
	inputBoxsArr[1] = InputBox(9, 70, "作者", ""); // 作者 
	inputBoxsArr[2] = InputBox(11, 15, "ISBN", ""); // ISBN 
	inputBoxsArr[3] = InputBox(11, 70, "分类号", ""); // 分类号 
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
	click_user_library_search(linksArr[3], 0, 0);
}
