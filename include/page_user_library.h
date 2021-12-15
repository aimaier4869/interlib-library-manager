// 学校用户图书借阅页 

#ifndef PAGE_USER_LIBRARY_H
#define PAGE_USER_LIBRARY_H

#include "variable.h"

// 渲染操作区域
void click_user_library_renderBookList(int len = lib.currentPageCount);

// 渲染页面信息区域
void click_user_library_renderPageInfo();

// 当搜索按钮被按下时 
void click_user_library_search(const Link & self, int row, int col);

// 当借阅按钮被按下时
void click_user_library_borrowBook(const Link & self, int row, int col);

// 当下一页按钮被按下
void click_user_library_nextPage(const Link & self, int row, int col);

// 当上一页按钮被按下
void click_user_library_prevPage(const Link & self, int row, int col);

// 借阅图书导航按钮被按下 
void click_tab_user_library(const Link & self, int row, int col);

// 借阅记录导航按钮被按下 
void click_tab_user_logs(const Link & self, int row, int col);

// 帐户设置导航按钮被按下 
void click_tab_user_settings(const Link & self, int row, int col);

void page_user_library();

#endif
