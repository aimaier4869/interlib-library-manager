// 用户登录页面

#include "../include/page_user_login.h"
#include "../include/page_admin_login.h"
#include "../include/util.h"
#include "../include/variable.h"
#include "../include/router.h"

// 用户登录页面中的登录按钮点击事件 
void click_user_login(const Link & self, int row, int col) {
	// 当登录页面中的登录按钮被点击时，页面中必有两个输入框
	// 其中第一个为用户名，第二个为密码 
	// 获取输入的用户名和密码 
	string username = InputBoxsArr[0].value;
	string password = InputBoxsArr[1].value;
	
	if(username == "") {
		msg("用户名不能为空！");
		return; 
	}
	if(password == "") {
		msg("密码不能为空！");
		return; 
	}

	// 验证用户名和密码是否匹配 
	int success = hnuer.userLogin(username, password);
	if(success == -1) {
		msg("该用户不存在！");
	}else if(success == 0) {
		msg("登录失败，用户名或密码错误，请检查后重试");
	} else {
		// 如果正确那就登录成功了 
		checkoutPage("page_user_library"); 
		currentUser = username; 
		// debug:用户登录后需要更新一下当前用户借阅记录 
		logs.updateCurrentUserLogs();
		msg("登录成功"); 	
	}
	
}

void page_user_login() {
	// Links
	linksArrLen = 3;
	Link * linksArr = new Link[linksArrLen];// 创建数组 
	linksArr[0] = Link(4, 3, "管理员登录",  click_tab_admin_login);
	linksArr[1] = Link(4, 20, "*学校用户登录", click_tab_user_login);
	linksArr[2] = Link(22, 65, "| 登录 |", click_user_login);
	
	if(LinksArr != NULL) {// 释放原本数组内容并重新指定 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 3;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(11, 52, "学校用户登录");
	textsArr[1] = Text(15, 44, "账号：");
	textsArr[2] = Text(18, 44, "密码：");
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 2;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(15, 50, "账号", "");
	inputBoxsArr[1] = InputBox(18, 50, "密码", "");
	inputBoxsArr[1].isPassword = true;
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
}

