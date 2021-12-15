// 修改图书页面 

#ifndef PAGE_ADMIN_BOOK_MODIFY_H
#define PAGE_ADMIN_BOOK_MODIFY_H

#include "variable.h" 

// 确定修改按钮被按下 
void click_admin_library_bookModifyOk(const Link & self, int row, int col);

// 把图书在currentPageBooksArr中的索引传给这个函数 
void page_admin_book_modify(int index = 0);

#endif
