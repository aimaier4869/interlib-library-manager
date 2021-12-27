// 管理员图书管理页 

#ifndef PAGE_ADMIN_LIBRARY_H
#define PAGE_ADMIN_LIBRARY_H

#include "variable.h"

// 渲染操作区域
void click_admin_library_renderBookList(int len = lib.currentPageCount);

// 渲染页面信息区域
void click_admin_library_renderPageInfo();

// 当搜索按钮被按下时 
void click_admin_library_search(const Link & self, int row, int col);

// 当删除按钮被按下时
void click_admin_library_removeBook(const Link & self, int row, int col);

// 当修改按钮被按下时
void click_admin_library_modifyBook(const Link & self, int row, int col);

// 当下一页按钮被按下
void click_admin_library_nextPage(const Link & self, int row, int col);

// 当上一页按钮被按下
void click_admin_library_prevPage(const Link & self, int row, int col);

// 当首页按钮被按下
void click_admin_library_firstPage(const Link & self, int row, int col);

// 当尾页按钮被按下
void click_admin_library_lastPage(const Link & self, int row, int col); 

// 新增图书按钮被按下 
void click_admin_library_bookAdd(const Link & self, int row, int col);

void page_admin_library();

#endif
