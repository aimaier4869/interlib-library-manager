// ѧУ�û�ͼ�����ҳ 

#ifndef PAGE_USER_LOGS_H
#define PAGE_USER_LOGS_H

#include "variable.h"

// ��Ⱦ��������
void click_user_logs_renderLogs(int len = logs.currentPageCount);

// ��Ⱦҳ����Ϣ����
void click_user_logs_renderPageInfo();

// ��������ť������ʱ 
void click_user_logs_search(const Link & self, int row, int col);

// �����İ�ť������ʱ
void click_user_logs_returnBook(const Link & self, int row, int col);

// ����һҳ��ť������
void click_user_logs_nextPage(const Link & self, int row, int col);

// ����һҳ��ť������
void click_user_logs_prevPage(const Link & self, int row, int col);

void page_user_logs();

#endif
