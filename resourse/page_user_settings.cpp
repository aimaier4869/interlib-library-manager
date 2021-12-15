// 学校用户图书借阅页 

#include "../include/page_user_settings.h"
#include "../include/page_user_library.h"
#include "../include/page_admin_userlist.h"
#include "../include/util.h"
#include "../include/variable.h"

// 当确认修改按钮被按下 
void click_user_settings_changePwdOk(const Link & self, int row, int col) {
	
	string currentPwd = InputBoxsArr[0].value;
	string newPwd = InputBoxsArr[1].value;
	string againNewPwd = InputBoxsArr[2].value;
	
	if(currentPwd == "") {
		msg("当前密码不能为空！");
		return; 
	} 
	if(newPwd == "") {
		msg("新密码不能为空！");
		return; 
	}
	if(againNewPwd == "" && againNewPwd != newPwd) {
		msg("两次输入的新密码不一致！");
		return; 
	}
	if(currentPwd == newPwd) {
		msg("新密码与旧密码不能相同！");
		return; 
	}
	
	if(hnuer.userChangePwd(currentUser, currentPwd, newPwd) == -1) {
		msg("当前密码不正确！");
		return; 
	}
	
	click_logout(LinksArr[3], 0, 0);
	msg("修改密码成功！请重新登录");
}

void page_user_settings() {
	// Links
	linksArrLen = 8;
	Link * linksArr = new Link[linksArrLen];// 创建数组 
	linksArr[0] = Link(4, 3, "借阅图书",  click_tab_user_library);
	linksArr[1] = Link(4, 20, "借阅记录", click_tab_user_logs);
	linksArr[2] = Link(4, 35, "*帐户设置", click_tab_user_settings);
	linksArr[3] = Link(4, 108, "退出登录", click_logout);
	linksArr[4] = Link(26, 30, "| 确认修改 |", click_user_settings_changePwdOk);
	
	
	if(LinksArr != NULL) {// 释放原本数组内容并重新指定 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 7;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(7, 3, "> 帐户基本信息");
	textsArr[1] = Text(10, 11, "用户名：");
	textsArr[2] = Text(10, 20, currentUser);
	textsArr[3] = Text(13, 3, "> 修改密码");
	textsArr[4] = Text(16, 9, "当前密码：");
	textsArr[5] = Text(19, 11, "新密码：");
	textsArr[6] = Text(22, 3, "再次输入新密码：");
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 3;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(16, 20, "当前密码", ""); // 当前密码 
	inputBoxsArr[1] = InputBox(19, 20, "新密码", ""); // 新密码 
	inputBoxsArr[2] = InputBox(22, 20, "重复新密码", ""); // 再次输入新密码 
	inputBoxsArr[0].isPassword = true;
	inputBoxsArr[1].isPassword = true;
	inputBoxsArr[2].isPassword = true;
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
}
