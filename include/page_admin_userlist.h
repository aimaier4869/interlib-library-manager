// �û�����ҳ�� 

#ifndef PAGE_ADMIN_USERLIST_H
#define PAGE_ADMIN_USERLIST_H

#include "variable.h"

// ��Ⱦ��������
void click_admin_userlist_renderUserList(int len = hnuer.currentPageCount);

// ��Ⱦҳ����Ϣ����
void click_admin_userlist_renderPageInfo();

// ��������ť������ʱ 
void click_admin_userlist_search(const Link & self, int row, int col);

// ��������û���ť������ʱ 
void click_admin_userlist_add(const Link & self, int row, int col);

// ��ɾ����ť������ʱ
void click_admin_userlist_removeUser(const Link & self, int row, int col);

// ���������밴ť������ʱ
void click_admin_userlist_resetUserPassword(const Link & self, int row, int col);

// ����һҳ��ť������
void click_admin_userlist_nextPage(const Link & self, int row, int col);

// ����һҳ��ť������
void click_admin_userlist_prevPage(const Link & self, int row, int col);

// ͼ���������ť������ 
void click_tab_library(const Link & self, int row, int col);

// �û���������ť������ 
void click_tab_userlist(const Link & self, int row, int col);

// �˳���¼ 
void click_logout(const Link & self, int row, int col);

void page_admin_userlist();

#endif
