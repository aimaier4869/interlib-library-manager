// 学校用户图书借阅页 

#ifndef PAGE_USER_LOGS_H
#define PAGE_USER_LOGS_H

#include "variable.h"

// 渲染操作区域
void click_user_logs_renderLogs(int len = logs.currentPageCount);

// 渲染页面信息区域
void click_user_logs_renderPageInfo();

// 当搜索按钮被按下时 
void click_user_logs_search(const Link & self, int row, int col);

// 当借阅按钮被按下时
void click_user_logs_returnBook(const Link & self, int row, int col);

// 当下一页按钮被按下
void click_user_logs_nextPage(const Link & self, int row, int col);

// 当上一页按钮被按下
void click_user_logs_prevPage(const Link & self, int row, int col);

void page_user_logs();

#endif
