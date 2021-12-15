// ѧУ�û�ͼ�����ҳ 

#ifndef PAGE_USER_LIBRARY_H
#define PAGE_USER_LIBRARY_H

#include "variable.h"

// ��Ⱦ��������
void click_user_library_renderBookList(int len = lib.currentPageCount);

// ��Ⱦҳ����Ϣ����
void click_user_library_renderPageInfo();

// ��������ť������ʱ 
void click_user_library_search(const Link & self, int row, int col);

// �����İ�ť������ʱ
void click_user_library_borrowBook(const Link & self, int row, int col);

// ����һҳ��ť������
void click_user_library_nextPage(const Link & self, int row, int col);

// ����һҳ��ť������
void click_user_library_prevPage(const Link & self, int row, int col);

// ����ͼ�鵼����ť������ 
void click_tab_user_library(const Link & self, int row, int col);

// ���ļ�¼������ť������ 
void click_tab_user_logs(const Link & self, int row, int col);

// �ʻ����õ�����ť������ 
void click_tab_user_settings(const Link & self, int row, int col);

void page_user_library();

#endif
