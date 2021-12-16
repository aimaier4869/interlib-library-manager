// 用户管理页面 

#include "../include/page_admin_userlist.h"
#include "../include/util.h"
#include "../include/variable.h"
#include "../include/router.h"

// 渲染操作区域
void click_admin_userlist_renderUserList(int len) {
	// 页面中的位置已写死了 
	// 清屏 
	for(int i = 0; i < 10; i++) {
		gotoxy(17 + i, 5);
		// debug:之前写的是65-17 
		printChar(65 - 5, ' ');
	}
	for(int i = 0; i < len; i++) {
		gotoxy(17 + i, 5);
		cout << hnuer.currentPageUsersArr[i]->username;
		gotoxy(17 + i, 35);
		if(hnuer.currentPageUsersArr[i]->password == "123456") {
			cout << "123456";
		}else {
			cout << "******";
		}
	}
	// 一页有10条内容也已经写死了 
	for(int i = 0; i < 10; i++) {
		if(i < len) {
			gotoxy(17 + i, 71);
			cout << "删除用户";
			gotoxy(17 + i, 83);
			cout << "重置密码";
		} else {
			gotoxy(17 + i, 71);
			printChar(8, ' ');
			gotoxy(17 + i, 83);
			printChar(8, ' ');
		}
	} 
} 

// 渲染页面信息区域
void click_admin_userlist_renderPageInfo() {
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	string totalPageCount = to_string(hnuer.getTotalPageCount(10));
	TextsArr[8].text = "当前第 " + to_string(hnuer.currentPageIndex) + " 页，共 " + totalPageCount + " 页。";
	// 渲染到页面中
	gotoxy(TextsArr[8].row, TextsArr[8].col);
	printChar(60, ' ');
	gotoxy(TextsArr[8].row, TextsArr[8].col);
	printChar(TextsArr[8].text.length(), ' '); 
	gotoxy(TextsArr[8].row, TextsArr[8].col);
	cout << TextsArr[8].text;
}

// 当搜索按钮被按下时 
void click_admin_userlist_search(const Link & self, int row, int col) {
	// 此时页面中必有两个输入框，其中第一个为搜索输入框
	string uname = InputBoxsArr[0].value;
	int len = hnuer.searchUserByUname(uname);
	// 渲染操作区域中的按钮 
	click_admin_userlist_renderUserList(len);
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	click_admin_userlist_renderPageInfo();
	msg("搜索成功！");
}

// 当添加新用户按钮被按下时 
void click_admin_userlist_add(const Link & self, int row, int col) {
	// 此时页面中必有两个输入框，其中第一个为搜索输入框
	string uname = InputBoxsArr[1].value;
	if(uname == "") {
		msg("用户名不能为空！");
		return;
	}
	int len = hnuer.addUserByUname(uname);
	
	// 是否新增成功 
	if(len == -1) {
		msg("添加失败！你输入的学号已存在");
	} else {
		// 清空输入框 
		InputBoxsArr[1].value = "";
		gotoxy(InputBoxsArr[1].row, InputBoxsArr[1].col);
		printChar(20, ' '); 
		// 渲染操作区域中的按钮 
		click_admin_userlist_renderUserList(len);
		// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
		click_admin_userlist_renderPageInfo();
		msg("添加成功！");
	}
	
}

// 当删除按钮被按下时
void click_admin_userlist_removeUser(const Link & self, int row, int col) {
	int index = row - 17;
	if(index < hnuer.currentPageCount) {
		hnuer.removeUser(index);
		click_admin_userlist_renderUserList(hnuer.currentPageCount);
		// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
		click_admin_userlist_renderPageInfo();
		msg("删除用户成功！"); 
	}
}

// 当重置密码按钮被按下时
void click_admin_userlist_resetUserPassword(const Link & self, int row, int col) {
	int index = row - 17;
	if(index < hnuer.currentPageCount) {
		hnuer.resetPassword(index);
		click_admin_userlist_renderUserList(hnuer.currentPageCount);
		msg("重置密码成功！"); 
	}
}

// 当下一页按钮被按下
void click_admin_userlist_nextPage(const Link & self, int row, int col) {
	int nextPage = hnuer.currentPageIndex + 1;
	if(nextPage > hnuer.getTotalPageCount(10)) {
		msg("没有下一页了哦");
		return;
	}
	// 切换页面 
	hnuer.updataCurrentPage(nextPage);
	click_admin_userlist_renderUserList(hnuer.currentPageCount);
	
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	click_admin_userlist_renderPageInfo();
	
	msg("已为你跳转到第 " + to_string(nextPage) + "页");
}

// 当上一页按钮被按下
void click_admin_userlist_prevPage(const Link & self, int row, int col) {
	int prevPage = hnuer.currentPageIndex - 1;
	if(prevPage <= 0) {
		msg("没有上一页了哦");
		return;
	}
	// 切换页面 
	hnuer.updataCurrentPage(prevPage);
	click_admin_userlist_renderUserList(hnuer.currentPageCount);
	
	// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
	click_admin_userlist_renderPageInfo();
	
	msg("已为你跳转到第 " + to_string(prevPage) + "页");
}

// 图书管理导航按钮被按下 
void click_tab_library(const Link & self, int row, int col) {
	checkoutPage("page_admin_library"); 
	msg("图书管理页面"); 
}

// 用户管理导航按钮被按下 
void click_tab_userlist(const Link & self, int row, int col) {
	checkoutPage("page_admin_userlist"); 
	msg("用户管理页面"); 
}

// 退出登录按钮按下 
void click_logout(const Link & self, int row, int col) {
	checkoutPage("page_admin_login"); 
	currentUser = ""; 
	msg("退出登录成功！"); 
}

void page_admin_userlist() {
	// Links
	linksArrLen = 9;
	Link * linksArr = new Link[linksArrLen];// 创建数组 
	linksArr[0] = Link(4, 3, "*用户管理",  testClick);
	linksArr[1] = Link(4, 20, "图书管理", click_tab_library);
	linksArr[2] = Link(4, 108, "退出登录", click_logout);
	linksArr[3] = Link(9, 40, "| 搜索 |", click_admin_userlist_search);
	linksArr[4] = Link(9, 100, "| 添加 |", click_admin_userlist_add);
	// 删除用户按钮区域 
	linksArr[5] = Link(17, 71, "", click_admin_userlist_removeUser, 10, 8);
	// 重置密码按钮区域 
	linksArr[6] = Link(17, 83, "", click_admin_userlist_resetUserPassword, 10, 8;
	// 上一页下一页 
	linksArr[7] = Link(30, 5, "| 上一页 |", click_admin_userlist_prevPage);
	linksArr[8] = Link(30, 18, "| 下一页 |", click_admin_userlist_nextPage);
	
	if(LinksArr != NULL) {// 释放原本数组内容并重新指定 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 9;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(7, 3, "> 搜索");
	textsArr[1] = Text(9, 5, "学号/工号：");
	textsArr[2] = Text(7, 62, "> 添加新用户");
	textsArr[3] = Text(9, 64, "学号/工号：");
	textsArr[4] = Text(13, 3, "> 用户列表");
	textsArr[5] = Text(15, 5, "学号/工号");
	textsArr[6] = Text(15, 35, "密码");
	textsArr[7] = Text(15, 71, "操作");
	textsArr[8] = Text(30, 30, "");
	string totalPageCount = to_string(hnuer.getTotalPageCount(10));
	textsArr[8].text = "当前第 1 页，共 " + totalPageCount + " 页。";
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 2;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(9, 16, "学号/工号", ""); // 搜索 
	inputBoxsArr[1] = InputBox(9, 75, "学号/工号", ""); // 新增 
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
	click_admin_userlist_search(linksArr[3], 0, 0);	
}
