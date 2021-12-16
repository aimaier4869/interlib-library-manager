// ����ͼ��ҳ�� 

#include "../include/util.h"
#include "../include/variable.h"
#include "../include/page_admin_book_add.h"
#include "../include/page_admin_userlist.h"

// ȷ����Ӱ�ť������ 
void click_admin_library_bookAddOk(const Link & self, int row, int col) {
	// �ð�ť������ʱҳ���б���4������� 
	string bookName = InputBoxsArr[0].value;
	string author = InputBoxsArr[1].value;
	string ISBN = InputBoxsArr[2].value;
	string type = InputBoxsArr[3].value;
	// ��֤��ֵ 
	if(bookName == "") {
		msg("ͼ������ ����Ϊ�գ�");
		return;
	}
	if(author == "") {
		msg("���� ����Ϊ�գ�");
		return;
	}
	if(ISBN == "") {
		msg("ISBN ����Ϊ�գ�");
		return;
	}
	if(type == "") {
		msg("����� ����Ϊ�գ�");
		return;
	}
	int len = lib.addBook(Book(bookName, author, ISBN, type));
		// �Ƿ������ɹ� 
	if(len == -1) {
		msg("���ʧ�ܣ��������ISBN�Ѵ���");
	} else {
		// �������� 
		InputBoxsArr[0].value = "";
		InputBoxsArr[1].value = "";
		InputBoxsArr[2].value = "";
		InputBoxsArr[3].value = "";
		gotoxy(InputBoxsArr[0].row, InputBoxsArr[0].col);
		printChar(20, ' ');
		gotoxy(InputBoxsArr[1].row, InputBoxsArr[1].col);
		printChar(20, ' '); 
		gotoxy(InputBoxsArr[2].row, InputBoxsArr[2].col);
		printChar(20, ' '); 
		gotoxy(InputBoxsArr[3].row, InputBoxsArr[3].col);
		printChar(20, ' '); 
		
		// �ص�ͼ�����ҳ�� 
		click_tab_library(LinksArr[1], 0, 0);
		// ��Ⱦ���������еİ�ť 
//		click_admin_userlist_renderUserList(len);
//		// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
//		click_admin_userlist_renderPageInfo();
		
		msg("��ӳɹ���");
	}
}

void page_admin_book_add() {

	// Links
	linksArrLen = 5;
	Link * linksArr = new Link[linksArrLen];// �������� 
	linksArr[0] = Link(4, 3, "�û�����",  click_tab_userlist);
	linksArr[1] = Link(4, 20, "ͼ�����", click_tab_library);
	linksArr[2] = Link(4, 110, "�˳���¼", click_logout);
	linksArr[3] = Link(28, 50, "| ȡ�� |", click_tab_library);
	linksArr[4] = Link(28, 60, "| ȷ����� |", click_admin_library_bookAddOk);
	
	if(LinksArr != NULL) {// �ͷ�ԭ���������ݲ�����ָ�� 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 5;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(9, 35, "> ����ͼ��");
	textsArr[1] = Text(13, 40, "ͼ�����ƣ�");
	textsArr[2] = Text(16, 40, "���ߣ�");
	textsArr[3] = Text(19, 40, "ISBN��");
	textsArr[4] = Text(22, 40, "����ţ�");
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 4;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(13, 52, "ͼ������", "");
	inputBoxsArr[1] = InputBox(16, 52, "����", "");
	inputBoxsArr[2] = InputBox(19, 52, "ISBN", "");
	inputBoxsArr[3] = InputBox(22, 52, "����ҳ���еķ����", "");
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
//	click_admin_library_renderUserList(lib.currentPageCount);
}
