// ����Աͼ�����ҳ 

#ifndef PAGE_ADMIN_LIBRARY_H
#define PAGE_ADMIN_LIBRARY_H

#include "variable.h"

// ��Ⱦ��������
void click_admin_library_renderBookList(int len = lib.currentPageCount);

// ��Ⱦҳ����Ϣ����
void click_admin_library_renderPageInfo();

// ��������ť������ʱ 
void click_admin_library_search(const Link & self, int row, int col);

// ��ɾ����ť������ʱ
void click_admin_library_removeBook(const Link & self, int row, int col);

// ���޸İ�ť������ʱ
void click_admin_library_modifyBook(const Link & self, int row, int col);

// ����һҳ��ť������
void click_admin_library_nextPage(const Link & self, int row, int col);

// ����һҳ��ť������
void click_admin_library_prevPage(const Link & self, int row, int col);

// ����ҳ��ť������
void click_admin_library_firstPage(const Link & self, int row, int col);

// ��βҳ��ť������
void click_admin_library_lastPage(const Link & self, int row, int col); 

// ����ͼ�鰴ť������ 
void click_admin_library_bookAdd(const Link & self, int row, int col);

void page_admin_library();

#endif
