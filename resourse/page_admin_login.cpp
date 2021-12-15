// ����Ա��¼ҳ��

#include "../include/page_admin_login.h"
#include "../include/variable.h"
#include "../include/util.h"
#include "../include/router.h"

// ����Ա��¼ҳ���еĵ�¼��ť����¼� 
void click_admin_login(const Link & self, int row, int col) {
	// ����¼ҳ���еĵ�¼��ť�����ʱ��ҳ���б������������
	// ���е�һ��Ϊ�û������ڶ���Ϊ���� 
	// ��ȡ������û��������� 
	string username = InputBoxsArr[0].value;
	string password = InputBoxsArr[1].value;
	// ��֤�û����������Ƿ�ƥ�� 
	
	if(username == "") {
		msg("�û�������Ϊ�գ�");
		return; 
	}
	if(password == "") {
		msg("���벻��Ϊ�գ�");
		return; 
	}

	// ��֤�û����������Ƿ�ƥ�� 
	int success = hnuer.userLogin(username, password);
	if(success == -1) {
		msg("���û������ڣ�");
	}else if(success == 0) {
		msg("��¼ʧ�ܣ��û���������������������");
	} else {
		// �����ȷ�Ǿ͵�¼�ɹ��� 
		checkoutPage("page_admin_userlist"); 
		currentUser = username; 
		msg("��¼�ɹ�"); 	
	}
	
}

// ����Ա��¼������ť������ 
void click_tab_admin_login(const Link & self, int row, int col) {
	checkoutPage("page_admin_login"); 
	msg("����Ա��¼ҳ��"); 
}

// ѧУ�û���¼������ť������ 
void click_tab_user_login(const Link & self, int row, int col) {
	checkoutPage("page_user_login"); 
	msg("ѧУ�û���¼ҳ��"); 
}

void page_admin_login() {
	// Links
	linksArrLen = 3;
	Link * linksArr = new Link[linksArrLen];// �������� 
	linksArr[0] = Link(4, 3, "*����Ա��¼",  click_tab_admin_login);
	linksArr[1] = Link(4, 20, "ѧУ�û���¼", click_tab_user_login);
	linksArr[2] = Link(22, 65, "| ��¼ |", click_admin_login);
	
	if(LinksArr != NULL) {// �ͷ�ԭ���������ݲ�����ָ�� 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 3;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(11, 52, "����Ա��¼");
	textsArr[1] = Text(15, 44, "�˺ţ�");
	textsArr[2] = Text(18, 44, "���룺");
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 2;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(15, 50, "�˺�", "");
	inputBoxsArr[1] = InputBox(18, 50, "����", "");
	inputBoxsArr[1].isPassword = true;
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;

}

