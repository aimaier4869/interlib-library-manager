// ����Աͼ�����ҳ 

#include "../include/page_admin_library.h"
#include "../include/page_admin_userlist.h"
#include "../include/util.h"
#include "../include/variable.h"
#include "../include/router.h"

// ��Ⱦ��������
void click_admin_library_renderBookList(int len) {
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
		printChar(6, ' ');

		gotoxy(18 + i, 66);
		cout << lib.currentPageBooksArr[i]->ISBN; 
		gotoxy(18 + i, 86);
		cout << lib.currentPageBooksArr[i]->type; 
		
	}
//	 һҳ��10������Ҳ�Ѿ�д���� 
	for(int i = 0; i < 10; i++) {
		if(i < len) {
			gotoxy(18 + i, 100);
			cout << "ɾ��ͼ��";
			gotoxy(18 + i, 110);
			cout << "�޸�";
		} else {
			gotoxy(18 + i, 100);
			printChar(8, ' ');
			gotoxy(18 + i, 110);
			printChar(4, ' ');
		}
	} 
} 

// ��Ⱦҳ����Ϣ����
void click_admin_library_renderPageInfo() {
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	string totalPageCount = to_string(lib.getTotalPageCount(10));
	TextsArr[11].text = "��ǰ�� " + to_string(lib.currentPageIndex) + " ҳ���� " + totalPageCount + " ҳ��";
	// ��Ⱦ��ҳ����
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	printChar(TextsArr[11].text.length(), ' '); 
	gotoxy(TextsArr[11].row, TextsArr[11].col);
	cout << TextsArr[11].text;
}

// ��������ť������ʱ 
void click_admin_library_search(const Link & self, int row, int col) {
	// ��ʱҳ���б����ĸ�����򣬷ֱ�Ϊͼ�����ƣ����ߣ�ISBN�������
	Book book = {InputBoxsArr[0].value, InputBoxsArr[1].value, InputBoxsArr[2].value, InputBoxsArr[3].value}; 
	lib.searchBook(book);
	// ��Ⱦ��Ϣ 
	click_admin_library_renderBookList();
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ11��Ԫ�ر���ҳ����Ϣ 
	click_admin_library_renderPageInfo();
	msg("�����ɹ���");
}

// ��ɾ����ť������ʱ
void click_admin_library_removeBook(const Link & self, int row, int col) {
	int index = row - 18;
	if(index < lib.currentPageCount) {
		lib.removeBook(index);
		// ɾ�������µ��������ť�ָ�ҳ�� 
		click_admin_library_search(LinksArr[3], 0, 0);
		msg("ɾ��ͼ��ɹ���"); 
	}
}

// ���޸İ�ť������ʱ
void click_admin_library_modifyBook(const Link & self, int row, int col) {
	int index = row - 18;
	if(index < lib.currentPageCount) {
		// �л����޸�ͼ��ҳ��
		checkoutPage("page_admin_book_modify", index); 
	}
}

// ����һҳ��ť������
void click_admin_library_nextPage(const Link & self, int row, int col) {
	int nextPage = lib.currentPageIndex + 1;
	if(nextPage > lib.getTotalPageCount(10)) {
		msg("û����һҳ��Ŷ");
		return;
	}
	// �л�ҳ�� 
	lib.updateCurrentPage(nextPage);
	click_admin_library_renderBookList(lib.currentPageCount);
	
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	click_admin_library_renderPageInfo();
	
	msg("��Ϊ����ת���� " + to_string(nextPage) + " ҳ");
}

// ����һҳ��ť������
void click_admin_library_prevPage(const Link & self, int row, int col) {
	int prevPage = lib.currentPageIndex - 1;
	if(prevPage <= 0) {
		msg("û����һҳ��Ŷ");
		return;
	}
	// �л�ҳ�� 
	lib.updateCurrentPage(prevPage);
	click_admin_library_renderBookList(lib.currentPageCount);
	
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	click_admin_library_renderPageInfo();
	
	msg("��Ϊ����ת���� " + to_string(prevPage) + " ҳ");
}

// ����ͼ�鰴ť������ 
void click_admin_library_bookAdd(const Link & self, int row, int col) {
	checkoutPage("page_admin_book_add"); 
	msg("����ͼ��"); 
}

void page_admin_library() {
	// Links
	linksArrLen = 9;
	Link * linksArr = new Link[linksArrLen];// �������� 
	linksArr[0] = Link(4, 3, "�û�����",  click_tab_userlist);
	linksArr[1] = Link(4, 20, "*ͼ�����", click_tab_library);
	linksArr[2] = Link(4, 108, "�˳���¼", click_logout);
	linksArr[3] = Link(12, 100, "| ���� |", click_admin_library_search);
	linksArr[4] = Link(14, 16, "| + ����ͼ�� |", click_admin_library_bookAdd);
	// ɾ��ͼ�鰴ť���� 
	linksArr[5] = Link(18, 100, "ɾ��ͼ��", click_admin_library_removeBook, 10);
	// �޸İ�ť���� 
	linksArr[6] = Link(18, 110, "�޸�", click_admin_library_modifyBook, 10);
	// ��һҳ��һҳ 
	linksArr[7] = Link(30, 5, "| ��һҳ |", click_admin_library_prevPage);
	linksArr[8] = Link(30, 18, "| ��һҳ |", click_admin_library_nextPage);
	
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
	
	click_admin_library_search(linksArr[3], 0, 0);
}
