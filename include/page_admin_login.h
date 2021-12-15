// 管理员登录页面

#ifndef PAGE_ADMIN_LOGIN_H
#define PAGE_ADMIN_LOGIN_H

#include "variable.h"


// 管理员登录页面中的登录按钮点击事件 
void click_admin_login(const Link & self, int row, int col); 

// 管理员登录导航按钮被按下 
void click_tab_admin_login(const Link & self, int row, int col);

// 学校用户登录导航按钮被按下 
void click_tab_user_login(const Link & self, int row, int col);

void page_admin_login();

#endif

