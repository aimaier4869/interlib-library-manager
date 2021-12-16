// 新增图书页面 

#include "../include/page_admin_book_modify.h"
#include "../include/util.h"
#include "../include/variable.h"
#include "../include/page_admin_userlist.h"

// 确定修改按钮被按下 
void click_admin_library_bookModifyOk(const Link & self, int row, int col) {
	// 该按钮被按下时页面中必有4个输入框 
	string bookName = InputBoxsArr[0].value;
	string author = InputBoxsArr[1].value;
	string ISBN = TextsArr[5].text;
	string type = InputBoxsArr[2].value;
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
	int len = lib.modifyBook(Book(bookName, author, ISBN, type));
		// 是否修改成功 
	if(len == -1) {
		msg("修改失败！你输入的ISBN不存在");
	} else {
		
		// 回到图书管理页面 
		click_tab_library(LinksArr[1], 0, 0);
		
		msg("修改成功！");
	}
}

// 把图书在currentPageBooksArr中的索引传给这个函数 
void page_admin_book_modify(int index) {

	// Links
	linksArrLen = 5;
	Link * linksArr = new Link[linksArrLen];// 创建数组 
	linksArr[0] = Link(4, 3, "用户管理",  click_tab_userlist);
	linksArr[1] = Link(4, 20, "图书管理", click_tab_library);
	linksArr[2] = Link(4, 110, "退出登录", click_logout);
	linksArr[3] = Link(28, 50, "| 取消 |", click_tab_library);
	linksArr[4] = Link(28, 60, "| 确定修改 |", click_admin_library_bookModifyOk);
	
	if(LinksArr != NULL) {// 释放原本数组内容并重新指定 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 6;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(9, 35, "> 修改图书");
	textsArr[1] = Text(16, 40, "图书名称：");
	textsArr[2] = Text(19, 40, "作者：");
	textsArr[3] = Text(13, 40, "ISBN：");
	textsArr[4] = Text(22, 40, "分类号：");
	textsArr[5] = Text(13, 52, lib.currentPageBooksArr[index]->ISBN);
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 3;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(16, 52, "图书名称", lib.currentPageBooksArr[index]->name);
	inputBoxsArr[1] = InputBox(19, 52, "作者", lib.currentPageBooksArr[index]->author);
	inputBoxsArr[2] = InputBox(22, 52, "修改页面中的分类号", lib.currentPageBooksArr[index]->type);
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
}
