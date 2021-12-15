// 管理员图书管理页 

#include "../include/page_admin_library.h"
#include "../include/page_admin_userlist.h"
#include "../include/util.h"
#include "../include/variable.h"
#include "../include/router.h"

// 渲染操作区域
void click_admin_library_renderBookList(int len) {
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
		printChar(6, ' ');

		gotoxy(18 + i, 66);
		cout << lib.currentPageBooksArr[i]->ISBN; 
		gotoxy(18 + i, 86);
		cout << lib.currentPageBooksArr[i]->type; 
		
	}
//	 一页有10条内容也已经写死了 
	for(int i = 0; i < 10; i++) {
		if(i < len) {
			gotoxy(18 + i, 100);
			cout << "删除图书";
			gotoxy(18 + i, 110);
			cout << "修改";
		} else {
			gotoxy(18 + i, 100);
			printChar(8, ' ');
			gotoxy(18 + i, 110);
			printChar(4, ' ');
		}
	} 
} 

// 渲染页面信息区域
void click_admin_library_renderPageInfo() {
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	string totalPageCount = to_string(lib.getTotalPageCount(10));
	TextsArr[11].text = "当前第 " + to_string(lib.currentPageIndex) + " 页，共 " + totalPageCount + " 页。";
	// 渲染到页面中
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	printChar(TextsArr[11].text.length(), ' '); 
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	cout << TextsArr[11].text;
}

// 当搜索按钮被按下时 
void click_admin_library_search(const Link & self, int row, int col) {
	// 此时页面中必有四个输入框，分别为图书名称，作者，ISBN，分类号
	Book book = {InputBoxsArr[0].value, InputBoxsArr[1].value, InputBoxsArr[2].value, InputBoxsArr[3].value}; 
	lib.searchBook(book);
	// 渲染信息 
	click_admin_library_renderBookList();
	// 更新底部的页面信息，此时页面中索引为11的元素必是页面信息 
	click_admin_library_renderPageInfo();
	msg("搜索成功！");
}

// 当删除按钮被按下时
void click_admin_library_removeBook(const Link & self, int row, int col) {
	int index = row - 18;
	if(index < lib.currentPageCount) {
		lib.removeBook(index);
		// 删除后重新点击搜索按钮恢复页面 
		click_admin_library_search(LinksArr[3], 0, 0);
		msg("删除图书成功！"); 
	}
}

// 当修改按钮被按下时
void click_admin_library_modifyBook(const Link & self, int row, int col) {
	int index = row - 18;
	if(index < lib.currentPageCount) {
		// 切换到修改图书页面
		checkoutPage("page_admin_book_modify", index); 
	}
}

// 当下一页按钮被按下
void click_admin_library_nextPage(const Link & self, int row, int col) {
	int nextPage = lib.currentPageIndex + 1;
	if(nextPage > lib.getTotalPageCount(10)) {
		msg("没有下一页了哦");
		return;
	}
	// 切换页面 
	lib.updateCurrentPage(nextPage);
	click_admin_library_renderBookList(lib.currentPageCount);
	
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	click_admin_library_renderPageInfo();
	
	msg("已为你跳转到第 " + to_string(nextPage) + " 页");
}

// 当上一页按钮被按下
void click_admin_library_prevPage(const Link & self, int row, int col) {
	int prevPage = lib.currentPageIndex - 1;
	if(prevPage <= 0) {
		msg("没有上一页了哦");
		return;
	}
	// 切换页面 
	lib.updateCurrentPage(prevPage);
	click_admin_library_renderBookList(lib.currentPageCount);
	
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	click_admin_library_renderPageInfo();
	
	msg("已为你跳转到第 " + to_string(prevPage) + " 页");
}

// 新增图书按钮被按下 
void click_admin_library_bookAdd(const Link & self, int row, int col) {
	checkoutPage("page_admin_book_add"); 
	msg("新增图书"); 
}

void page_admin_library() {
	// Links
	linksArrLen = 9;
	Link * linksArr = new Link[linksArrLen];// 创建数组 
	linksArr[0] = Link(4, 3, "用户管理",  click_tab_userlist);
	linksArr[1] = Link(4, 20, "*图书管理", click_tab_library);
	linksArr[2] = Link(4, 108, "退出登录", click_logout);
	linksArr[3] = Link(12, 100, "| 搜索 |", click_admin_library_search);
	linksArr[4] = Link(14, 16, "| + 新增图书 |", click_admin_library_bookAdd);
	// 删除图书按钮区域 
	linksArr[5] = Link(18, 100, "删除图书", click_admin_library_removeBook, 10);
	// 修改按钮区域 
	linksArr[6] = Link(18, 110, "修改", click_admin_library_modifyBook, 10);
	// 上一页下一页 
	linksArr[7] = Link(30, 5, "| 上一页 |", click_admin_library_prevPage);
	linksArr[8] = Link(30, 18, "| 下一页 |", click_admin_library_nextPage);
	
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
	
	click_admin_library_search(linksArr[3], 0, 0);
}
