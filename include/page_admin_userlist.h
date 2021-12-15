// 用户管理页面 

#ifndef PAGE_ADMIN_USERLIST_H
#define PAGE_ADMIN_USERLIST_H

#include "variable.h"

// 渲染操作区域
void click_admin_userlist_renderUserList(int len = hnuer.currentPageCount);

// 渲染页面信息区域
void click_admin_userlist_renderPageInfo();

// 当搜索按钮被按下时 
void click_admin_userlist_search(const Link & self, int row, int col);

// 当添加新用户按钮被按下时 
void click_admin_userlist_add(const Link & self, int row, int col);

// 当删除按钮被按下时
void click_admin_userlist_removeUser(const Link & self, int row, int col);

// 当重置密码按钮被按下时
void click_admin_userlist_resetUserPassword(const Link & self, int row, int col);

// 当下一页按钮被按下
void click_admin_userlist_nextPage(const Link & self, int row, int col);

// 当上一页按钮被按下
void click_admin_userlist_prevPage(const Link & self, int row, int col);

// 图书管理导航按钮被按下 
void click_tab_library(const Link & self, int row, int col);

// 用户管理导航按钮被按下 
void click_tab_userlist(const Link & self, int row, int col);

// 退出登录 
void click_logout(const Link & self, int row, int col);

void page_admin_userlist();

#endif
