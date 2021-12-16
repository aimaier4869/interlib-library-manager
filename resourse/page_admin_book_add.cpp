// 新增图书页面 

#include "../include/util.h"
#include "../include/variable.h"
#include "../include/page_admin_book_add.h"
#include "../include/page_admin_userlist.h"

// 确定添加按钮被按下 
void click_admin_library_bookAddOk(const Link & self, int row, int col) {
	// 该按钮被按下时页面中必有4个输入框 
	string bookName = InputBoxsArr[0].value;
	string author = InputBoxsArr[1].value;
	string ISBN = InputBoxsArr[2].value;
	string type = InputBoxsArr[3].value;
	// 验证空值 
	if(bookName == "") {
		msg("图书名称 不能为空！");
		return;
	}
	if(author == "") {
		msg("作者 不能为空！");
		return;
	}
	if(ISBN == "") {
		msg("ISBN 不能为空！");
		return;
	}
	if(type == "") {
		msg("分类号 不能为空！");
		return;
	}
	int len = lib.addBook(Book(bookName, author, ISBN, type));
		// 是否新增成功 
	if(len == -1) {
		msg("添加失败！你输入的ISBN已存在");
	} else {
		// 清空输入框 
		InputBoxsArr[0].value = "";
		InputBoxsArr[1].value = "";
		InputBoxsArr[2].value = "";
		InputBoxsArr[3].value = "";
		gotoxy(InputBoxsArr[0].row, InputBoxsArr[0].col);
		printChar(20, ' ');
		gotoxy(InputBoxsArr[1].row, InputBoxsArr[1].col);
		printChar(20, ' '); 
		gotoxy(InputBoxsArr[2].row, InputBoxsArr[2].col);
		printChar(20, ' '); 
		gotoxy(InputBoxsArr[3].row, InputBoxsArr[3].col);
		printChar(20, ' '); 
		
		// 回到图书管理页面 
		click_tab_library(LinksArr[1], 0, 0);
		// 渲染操作区域中的按钮 
//		click_admin_userlist_renderUserList(len);
//		// 更新底部的页面信息，此时页面中索引为8的元素必是页面信息 
//		click_admin_userlist_renderPageInfo();
		
		msg("添加成功！");
	}
}

void page_admin_book_add() {

	// Links
	linksArrLen = 5;
	Link * linksArr = new Link[linksArrLen];// 创建数组 
	linksArr[0] = Link(4, 3, "用户管理",  click_tab_userlist);
	linksArr[1] = Link(4, 20, "图书管理", click_tab_library);
	linksArr[2] = Link(4, 110, "退出登录", click_logout);
	linksArr[3] = Link(28, 50, "| 取消 |", click_tab_library);
	linksArr[4] = Link(28, 60, "| 确定添加 |", click_admin_library_bookAddOk);
	
	if(LinksArr != NULL) {// 释放原本数组内容并重新指定 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 5;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(9, 35, "> 新增图书");
	textsArr[1] = Text(13, 40, "图书名称：");
	textsArr[2] = Text(16, 40, "作者：");
	textsArr[3] = Text(19, 40, "ISBN：");
	textsArr[4] = Text(22, 40, "分类号：");
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 4;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(13, 52, "图书名称", "");
	inputBoxsArr[1] = InputBox(16, 52, "作者", "");
	inputBoxsArr[2] = InputBox(19, 52, "ISBN", "");
	inputBoxsArr[3] = InputBox(22, 52, "新增页面中的分类号", "");
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
//	click_admin_library_renderUserList(lib.currentPageCount);
}
