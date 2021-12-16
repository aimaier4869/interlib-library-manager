// �û�����ҳ�� 

#include "../include/page_admin_userlist.h"
#include "../include/util.h"
#include "../include/variable.h"
#include "../include/router.h"

// ��Ⱦ��������
void click_admin_userlist_renderUserList(int len) {
	// ҳ���е�λ����д���� 
	// ���� 
	for(int i = 0; i < 10; i++) {
		gotoxy(17 + i, 5);
		// debug:֮ǰд����65-17 
		printChar(65 - 5, ' ');
	}
	for(int i = 0; i < len; i++) {
		gotoxy(17 + i, 5);
		cout << hnuer.currentPageUsersArr[i]->username;
		gotoxy(17 + i, 35);
		if(hnuer.currentPageUsersArr[i]->password == "123456") {
			cout << "123456";
		}else {
			cout << "******";
		}
	}
	// һҳ��10������Ҳ�Ѿ�д���� 
	for(int i = 0; i < 10; i++) {
		if(i < len) {
			gotoxy(17 + i, 71);
			cout << "ɾ���û�";
			gotoxy(17 + i, 83);
			cout << "��������";
		} else {
			gotoxy(17 + i, 71);
			printChar(8, ' ');
			gotoxy(17 + i, 83);
			printChar(8, ' ');
		}
	} 
} 

// ��Ⱦҳ����Ϣ����
void click_admin_userlist_renderPageInfo() {
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	string totalPageCount = to_string(hnuer.getTotalPageCount(10));
	TextsArr[8].text = "��ǰ�� " + to_string(hnuer.currentPageIndex) + " ҳ���� " + totalPageCount + " ҳ��";
	// ��Ⱦ��ҳ����
	gotoxy(TextsArr[8].row, TextsArr[8].col);
	printChar(60, ' ');
	gotoxy(TextsArr[8].row, TextsArr[8].col);
	printChar(TextsArr[8].text.length(), ' '); 
	gotoxy(TextsArr[8].row, TextsArr[8].col);
	cout << TextsArr[8].text;
}

// ��������ť������ʱ 
void click_admin_userlist_search(const Link & self, int row, int col) {
	// ��ʱҳ���б���������������е�һ��Ϊ���������
	string uname = InputBoxsArr[0].value;
	int len = hnuer.searchUserByUname(uname);
	// ��Ⱦ���������еİ�ť 
	click_admin_userlist_renderUserList(len);
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	click_admin_userlist_renderPageInfo();
	msg("�����ɹ���");
}

// ��������û���ť������ʱ 
void click_admin_userlist_add(const Link & self, int row, int col) {
	// ��ʱҳ���б���������������е�һ��Ϊ���������
	string uname = InputBoxsArr[1].value;
	if(uname == "") {
		msg("�û�������Ϊ�գ�");
		return;
	}
	int len = hnuer.addUserByUname(uname);
	
	// �Ƿ������ɹ� 
	if(len == -1) {
		msg("���ʧ�ܣ��������ѧ���Ѵ���");
	} else {
		// �������� 
		InputBoxsArr[1].value = "";
		gotoxy(InputBoxsArr[1].row, InputBoxsArr[1].col);
		printChar(20, ' '); 
		// ��Ⱦ���������еİ�ť 
		click_admin_userlist_renderUserList(len);
		// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
		click_admin_userlist_renderPageInfo();
		msg("��ӳɹ���");
	}
	
}

// ��ɾ����ť������ʱ
void click_admin_userlist_removeUser(const Link & self, int row, int col) {
	int index = row - 17;
	if(index < hnuer.currentPageCount) {
		hnuer.removeUser(index);
		click_admin_userlist_renderUserList(hnuer.currentPageCount);
		// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
		click_admin_userlist_renderPageInfo();
		msg("ɾ���û��ɹ���"); 
	}
}

// ���������밴ť������ʱ
void click_admin_userlist_resetUserPassword(const Link & self, int row, int col) {
	int index = row - 17;
	if(index < hnuer.currentPageCount) {
		hnuer.resetPassword(index);
		click_admin_userlist_renderUserList(hnuer.currentPageCount);
		msg("��������ɹ���"); 
	}
}

// ����һҳ��ť������
void click_admin_userlist_nextPage(const Link & self, int row, int col) {
	int nextPage = hnuer.currentPageIndex + 1;
	if(nextPage > hnuer.getTotalPageCount(10)) {
		msg("û����һҳ��Ŷ");
		return;
	}
	// �л�ҳ�� 
	hnuer.updataCurrentPage(nextPage);
	click_admin_userlist_renderUserList(hnuer.currentPageCount);
	
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	click_admin_userlist_renderPageInfo();
	
	msg("��Ϊ����ת���� " + to_string(nextPage) + "ҳ");
}

// ����һҳ��ť������
void click_admin_userlist_prevPage(const Link & self, int row, int col) {
	int prevPage = hnuer.currentPageIndex - 1;
	if(prevPage <= 0) {
		msg("û����һҳ��Ŷ");
		return;
	}
	// �л�ҳ�� 
	hnuer.updataCurrentPage(prevPage);
	click_admin_userlist_renderUserList(hnuer.currentPageCount);
	
	// ���µײ���ҳ����Ϣ����ʱҳ��������Ϊ8��Ԫ�ر���ҳ����Ϣ 
	click_admin_userlist_renderPageInfo();
	
	msg("��Ϊ����ת���� " + to_string(prevPage) + "ҳ");
}

// ͼ���������ť������ 
void click_tab_library(const Link & self, int row, int col) {
	checkoutPage("page_admin_library"); 
	msg("ͼ�����ҳ��"); 
}

// �û���������ť������ 
void click_tab_userlist(const Link & self, int row, int col) {
	checkoutPage("page_admin_userlist"); 
	msg("�û�����ҳ��"); 
}

// �˳���¼��ť���� 
void click_logout(const Link & self, int row, int col) {
	checkoutPage("page_admin_login"); 
	currentUser = ""; 
	msg("�˳���¼�ɹ���"); 
}

void page_admin_userlist() {
	// Links
	linksArrLen = 9;
	Link * linksArr = new Link[linksArrLen];// �������� 
	linksArr[0] = Link(4, 3, "*�û�����",  testClick);
	linksArr[1] = Link(4, 20, "ͼ�����", click_tab_library);
	linksArr[2] = Link(4, 108, "�˳���¼", click_logout);
	linksArr[3] = Link(9, 40, "| ���� |", click_admin_userlist_search);
	linksArr[4] = Link(9, 100, "| ��� |", click_admin_userlist_add);
	// ɾ���û���ť���� 
	linksArr[5] = Link(17, 71, "", click_admin_userlist_removeUser, 10, 8);
	// �������밴ť���� 
	linksArr[6] = Link(17, 83, "", click_admin_userlist_resetUserPassword, 10, 8;
	// ��һҳ��һҳ 
	linksArr[7] = Link(30, 5, "| ��һҳ |", click_admin_userlist_prevPage);
	linksArr[8] = Link(30, 18, "| ��һҳ |", click_admin_userlist_nextPage);
	
	if(LinksArr != NULL) {// �ͷ�ԭ���������ݲ�����ָ�� 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 9;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(7, 3, "> ����");
	textsArr[1] = Text(9, 5, "ѧ��/���ţ�");
	textsArr[2] = Text(7, 62, "> ������û�");
	textsArr[3] = Text(9, 64, "ѧ��/���ţ�");
	textsArr[4] = Text(13, 3, "> �û��б�");
	textsArr[5] = Text(15, 5, "ѧ��/����");
	textsArr[6] = Text(15, 35, "����");
	textsArr[7] = Text(15, 71, "����");
	textsArr[8] = Text(30, 30, "");
	string totalPageCount = to_string(hnuer.getTotalPageCount(10));
	textsArr[8].text = "��ǰ�� 1 ҳ���� " + totalPageCount + " ҳ��";
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 2;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(9, 16, "ѧ��/����", ""); // ���� 
	inputBoxsArr[1] = InputBox(9, 75, "ѧ��/����", ""); // ���� 
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
	click_admin_userlist_search(linksArr[3], 0, 0);	
}
