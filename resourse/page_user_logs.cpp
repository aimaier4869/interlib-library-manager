// ѧУ�û�ͼ�����ҳ

#include "../include/page_user_logs.h"
#include "../include/page_user_library.h" 
#include "../include/page_admin_userlist.h" 
#include "../include/util.h"
#include "../include/variable.h"

// ��Ⱦ��������
void click_user_logs_renderLogs(int len) {
	// ҳ���е�λ����д���� 
	// ���� 
	for(int i = 0; i < 10; i++) {
		gotoxy(18 + i, 5);
		printChar(100 - 5, ' ');
	}
	// �����Ϣ 
	for(int i = 0; i < len; i++) {
		gotoxy(18 + i, 5);
		string bookName = lib.getBookNameByISBN(logs.currentPageLogsArr[i]->ISBN);
		if(bookName != "") {
			cout << bookName;
		} else {
			cout << "δ�ҵ�����ͼ������ѱ�ɾ����"; 
		}

		gotoxy(18 + i, 58);
		cout << logs.currentPageLogsArr[i]->ISBN; 
		gotoxy(18 + i, 84);
		if(!logs.currentPageLogsArr[i]->state) {
			// �����0�����δ�黹
			cout << "��δ�黹"; 
		}else {
			cout << "";
		}
		
	}
//	 һҳ��10������Ҳ�Ѿ�д���� 
	for(int i = 0; i < 10; i++) {
		if(i < len && !logs.currentPageLogsArr[i]->state) {
			gotoxy(18 + i, 100);
			cout << "�黹";
		} else {
			gotoxy(18 + i, 100);
			printChar(8, ' ');
		}
	} 
} 

// ��Ⱦҳ����Ϣ����
void click_user_logs_renderPageInfo() {
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	string totalPageCount = to_string(logs.getTotalPageCount(10));
	TextsArr[7].text = "��ǰ�� " + to_string(logs.currentPageIndex) + " ҳ���� " + totalPageCount + " ҳ��";
	// ��Ⱦ��ҳ����
	gotoxy(TextsArr[7].row, TextsArr[7].col);
	printChar(TextsArr[7].text.length(), ' '); 
	gotoxy(TextsArr[7].row, TextsArr[7].col);
	cout << TextsArr[7].text;
}

// ��������ť������ʱ 
void click_user_logs_search(const Link & self, int row, int col) {
	// ��ʱҳ���б����ĸ�����򣬷ֱ�Ϊͼ�����ƣ����ߣ�ISBN�������
	string ISBN = InputBoxsArr[0].value;
	logs.searchLogByISBN(ISBN);
//	// ��Ⱦ��Ϣ 
	click_user_logs_renderLogs();
//	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ7��Ԫ�ر���ҳ����Ϣ 
	click_user_logs_renderPageInfo();
	msg("�����ɹ���");
}

// �����İ�ť������ʱ
void click_user_logs_returnBook(const Link & self, int row, int col) {
	int index = row - 18;
	if(index < logs.currentPageCount && !logs.currentPageLogsArr[index]->state) {
		int len = logs.returnBook(logs.currentPageLogsArr[index]->ISBN);
		if(len != -1) {
			// ���ĳɹ����µ��������ť�ָ�ҳ�� 
			click_user_logs_search(LinksArr[3], 0, 0);
			msg("�黹ͼ��ɹ���"); 
		} else {
			msg("�黹ͼ��ʧ�ܣ�");
		}
	}
}

// ����һҳ��ť������
void click_user_logs_nextPage(const Link & self, int row, int col) {
	int nextPage = logs.currentPageIndex + 1;
	if(nextPage > logs.getTotalPageCount(10)) {
		msg("û����һҳ��Ŷ");
		return;
	}
	// �л�ҳ�� 
	logs.updateCurrentPage(nextPage);
	click_user_logs_renderLogs(logs.currentPageCount);
	
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	click_user_logs_renderPageInfo();
	
	msg("��Ϊ����ת���� " + to_string(nextPage) + " ҳ");
}

// ����һҳ��ť������
void click_user_logs_prevPage(const Link & self, int row, int col) {
	int prevPage = logs.currentPageIndex - 1;
	if(prevPage <= 0) {
		msg("û����һҳ��Ŷ");
		return;
	}
	// �л�ҳ�� 
	logs.updateCurrentPage(prevPage);
	click_user_logs_renderLogs(logs.currentPageCount);
	
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	click_user_logs_renderPageInfo();
	
	msg("��Ϊ����ת���� " + to_string(prevPage) + " ҳ");
}

void page_user_logs() {
	// Links
	linksArrLen = 8;
	Link * linksArr = new Link[linksArrLen];// �������� 
	linksArr[0] = Link(4, 3, "����ͼ��",  click_tab_user_library);
	linksArr[1] = Link(4, 20, "*���ļ�¼", click_tab_user_logs);
	linksArr[2] = Link(4, 35, "�ʻ�����", click_tab_user_settings);
	linksArr[3] = Link(4, 108, "�˳���¼", click_logout);
	linksArr[4] = Link(10, 40, "| ���� |", click_user_logs_search);
	// �黹ͼ�鰴ť���� 
	linksArr[5] = Link(18, 100, "", click_user_logs_returnBook, 10, 4);
	// ��һҳ��һҳ 
	linksArr[6] = Link(30, 5, "| ��һҳ |", click_user_logs_prevPage);
	linksArr[7] = Link(30, 18, "| ��һҳ |", click_user_logs_nextPage);
	
	if(LinksArr != NULL) {// �ͷ�ԭ���������ݲ�����ָ�� 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 8;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(7, 3, "> ����");
	textsArr[1] = Text(10, 5, "ISBN��");
	textsArr[2] = Text(14, 3, "> ͼ���б�");
	textsArr[3] = Text(16, 5, "ͼ������");
	textsArr[4] = Text(16, 58, "ISBN");
	textsArr[5] = Text(16, 84, "״̬");
	textsArr[6] = Text(16, 100, "����");
	textsArr[7] = Text(30, 30, ""); // ���Ƿ�ҳ��Ϣ 
	textsArr[7].text = "��ǰ�� 1 ҳ���� 1 ҳ��";
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 1;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(10, 15, "ISBN", ""); // ISBN 
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
	click_user_logs_search(linksArr[4], 0, 0);
}
