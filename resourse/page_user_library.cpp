// ѧУ�û�ͼ�����ҳ 

#include "../include/page_user_library.h"
#include "../include/page_admin_userlist.h"
#include "../include/util.h"
#include "../include/variable.h"
#include "../include/router.h"

// ��Ⱦ��������
void click_user_library_renderBookList(int len) {
	// ҳ���е�λ����д���� 
	// ���� 
	for(int i = 0; i < 10; i++) {
		gotoxy(18 + i, 5);
		printChar(100 - 5, ' ');
	}
	// �����Ϣ 
	for(int i = 0; i < len; i++) {
		gotoxy(18 + i, 5);
		cout << lib.currentPageBooksArr[i]->name;
		
		// debug:���ֺ�Ӣ�Ļ���޷�������ȡ 
		// ��ȡͼ������ 
		gotoxy(18 + i, 34);
		printChar(6, ' ');
		
		gotoxy(18 + i, 40);
		cout << lib.currentPageBooksArr[i]->author;
		
		// ��ȡ�������� 
		gotoxy(18 + i, 60);
		printChar(50, ' ');

		gotoxy(18 + i, 66);
		cout << lib.currentPageBooksArr[i]->ISBN; 
		gotoxy(18 + i, 86);
		cout << lib.currentPageBooksArr[i]->type; 
		
	}
//	 һҳ��10������Ҳ�Ѿ�д���� 
	for(int i = 0; i < 10; i++) {
		if(i < len) {
			gotoxy(18 + i, 100);
			cout << "����";
		} else {
			gotoxy(18 + i, 100);
			printChar(8, ' ');
		}
	} 
} 

// ��Ⱦҳ����Ϣ����
void click_user_library_renderPageInfo() {
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	string totalPageCount = to_string(lib.getTotalPageCount(10));
	TextsArr[11].text = "��ǰ�� " + to_string(lib.currentPageIndex) + " ҳ���� " + totalPageCount + " ҳ��";
	// ��Ⱦ��ҳ����
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	printChar(60, ' ');
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	printChar(TextsArr[11].text.length(), ' '); 
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	cout << TextsArr[11].text;
}

// ��������ť������ʱ 
void click_user_library_search(const Link & self, int row, int col) {
	// ��ʱҳ���б����ĸ�����򣬷ֱ�Ϊͼ�����ƣ����ߣ�ISBN�������
	Book book = {InputBoxsArr[0].value, InputBoxsArr[1].value, InputBoxsArr[2].value, InputBoxsArr[3].value}; 
	msg("��������ͼ�飬�����ĵȴ�������");
	lib.searchBook(book);
	// ��Ⱦ��Ϣ 
	click_user_library_renderBookList();
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ11��Ԫ�ر���ҳ����Ϣ 
	click_user_library_renderPageInfo();
	msg("�����ɹ���");
}

// �����İ�ť������ʱ
void click_user_library_borrowBook(const Link & self, int row, int col) {
	int index = row - 18;
	if(index < lib.currentPageCount) {
		int len = logs.borrowBook(lib.currentPageBooksArr[index]->ISBN);
		if(len != -1) {
			// ���ĳɹ����µ��������ť�ָ�ҳ�� 
			click_user_library_search(LinksArr[3], 0, 0);
			msg("����ͼ��ɹ���"); 
		} else {
			msg("���Ѿ��н����Ȿ�鲢����δ�黹");
		}
	}
}

// ����һҳ��ť������
void click_user_library_nextPage(const Link & self, int row, int col) {
	int nextPage = lib.currentPageIndex + 1;
	if(nextPage > lib.getTotalPageCount(10)) {
		msg("û����һҳ��Ŷ");
		return;
	}
	// �л�ҳ�� 
	lib.updateCurrentPage(nextPage);
	click_user_library_renderBookList(lib.currentPageCount);
	
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	click_user_library_renderPageInfo();
	
	msg("��Ϊ����ת���� " + to_string(nextPage) + " ҳ");
}

// ����һҳ��ť������
void click_user_library_prevPage(const Link & self, int row, int col) {
	int prevPage = lib.currentPageIndex - 1;
	if(prevPage <= 0) {
		msg("û����һҳ��Ŷ");
		return;
	}
	// �л�ҳ�� 
	lib.updateCurrentPage(prevPage);
	click_user_library_renderBookList(lib.currentPageCount);
	
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	click_user_library_renderPageInfo();
	
	msg("��Ϊ����ת���� " + to_string(prevPage) + " ҳ");
}

// ����ͼ�鵼����ť������ 
void click_tab_user_library(const Link & self, int row, int col) {
	checkoutPage("page_user_library"); 
	msg("����ͼ��ҳ��"); 
}

// ���ļ�¼������ť������ 
void click_tab_user_logs(const Link & self, int row, int col) {
	checkoutPage("page_user_logs"); 
	msg("���ļ�¼ҳ��"); 
}

// �ʻ����õ�����ť������ 
void click_tab_user_settings(const Link & self, int row, int col) {
	checkoutPage("page_user_settings"); 
	msg("�ʻ�����ҳ��"); 
}

void page_user_library() {
	// Links
	linksArrLen = 8;
	Link * linksArr = new Link[linksArrLen];// �������� 
	linksArr[0] = Link(4, 3, "*����ͼ��",  click_tab_user_library);
	linksArr[1] = Link(4, 20, "���ļ�¼", click_tab_user_logs);
	linksArr[2] = Link(4, 35, "�ʻ�����", click_tab_user_settings);
	linksArr[3] = Link(4, 108, "�˳���¼", click_logout);
	linksArr[4] = Link(12, 100, "| ���� |", click_user_library_search);
	// ɾ��ͼ�鰴ť���� 
	linksArr[5] = Link(18, 100, "", click_user_library_borrowBook, 10, 4);
	// ��һҳ��һҳ 
	linksArr[6] = Link(30, 5, "| ��һҳ |", click_user_library_prevPage);
	linksArr[7] = Link(30, 18, "| ��һҳ |", click_user_library_nextPage);
	
	if(LinksArr != NULL) {// �ͷ�ԭ���������ݲ�����ָ�� 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 12;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(7, 3, "> ����");
	textsArr[1] = Text(9, 5, "ͼ�����ƣ�");
	textsArr[2] = Text(9, 60, "���ߣ�");
	textsArr[3] = Text(11, 5, "ISBN��");
	textsArr[4] = Text(11, 60, "����ţ�");
	textsArr[5] = Text(14, 3, "> ͼ���б�");
	textsArr[6] = Text(16, 5, "ͼ������");
	textsArr[7] = Text(16, 40, "����");
	textsArr[8] = Text(16, 66, "ISBN");
	textsArr[9] = Text(16, 86, "�����");
	textsArr[10] = Text(16, 100, "����");
	textsArr[11] = Text(30, 30, ""); // ���Ƿ�ҳ��Ϣ 
	textsArr[11].text = "��ǰ�� 1 ҳ���� 1 ҳ��";
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 4;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(9, 15, "ͼ������", ""); // ͼ������ 
	inputBoxsArr[1] = InputBox(9, 70, "����", ""); // ���� 
	inputBoxsArr[2] = InputBox(11, 15, "ISBN", ""); // ISBN 
	inputBoxsArr[3] = InputBox(11, 70, "�����", ""); // ����� 
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
	click_user_library_search(linksArr[3], 0, 0);
}
