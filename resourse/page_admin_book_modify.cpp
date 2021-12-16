// ����ͼ��ҳ�� 

#include "../include/page_admin_book_modify.h"
#include "../include/util.h"
#include "../include/variable.h"
#include "../include/page_admin_userlist.h"

// ȷ���޸İ�ť������ 
void click_admin_library_bookModifyOk(const Link & self, int row, int col) {
	// �ð�ť������ʱҳ���б���4������� 
	string bookName = InputBoxsArr[0].value;
	string author = InputBoxsArr[1].value;
	string ISBN = TextsArr[5].text;
	string type = InputBoxsArr[2].value;
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
	int len = lib.modifyBook(Book(bookName, author, ISBN, type));
		// �Ƿ��޸ĳɹ� 
	if(len == -1) {
		msg("�޸�ʧ�ܣ��������ISBN������");
	} else {
		
		// �ص�ͼ�����ҳ�� 
		click_tab_library(LinksArr[1], 0, 0);
		
		msg("�޸ĳɹ���");
	}
}

// ��ͼ����currentPageBooksArr�е���������������� 
void page_admin_book_modify(int index) {

	// Links
	linksArrLen = 5;
	Link * linksArr = new Link[linksArrLen];// �������� 
	linksArr[0] = Link(4, 3, "�û�����",  click_tab_userlist);
	linksArr[1] = Link(4, 20, "ͼ�����", click_tab_library);
	linksArr[2] = Link(4, 110, "�˳���¼", click_logout);
	linksArr[3] = Link(28, 50, "| ȡ�� |", click_tab_library);
	linksArr[4] = Link(28, 60, "| ȷ���޸� |", click_admin_library_bookModifyOk);
	
	if(LinksArr != NULL) {// �ͷ�ԭ���������ݲ�����ָ�� 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 6;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(9, 35, "> �޸�ͼ��");
	textsArr[1] = Text(16, 40, "ͼ�����ƣ�");
	textsArr[2] = Text(19, 40, "���ߣ�");
	textsArr[3] = Text(13, 40, "ISBN��");
	textsArr[4] = Text(22, 40, "����ţ�");
	textsArr[5] = Text(13, 52, lib.currentPageBooksArr[index]->ISBN);
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 3;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(16, 52, "ͼ������", lib.currentPageBooksArr[index]->name);
	inputBoxsArr[1] = InputBox(19, 52, "����", lib.currentPageBooksArr[index]->author);
	inputBoxsArr[2] = InputBox(22, 52, "�޸�ҳ���еķ����", lib.currentPageBooksArr[index]->type);
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
}
