// ѧУ�û�ͼ�����ҳ 

#include "../include/page_user_settings.h"
#include "../include/page_user_library.h"
#include "../include/page_admin_userlist.h"
#include "../include/util.h"
#include "../include/variable.h"

// ��ȷ���޸İ�ť������ 
void click_user_settings_changePwdOk(const Link & self, int row, int col) {
	
	string currentPwd = InputBoxsArr[0].value;
	string newPwd = InputBoxsArr[1].value;
	string againNewPwd = InputBoxsArr[2].value;
	
	if(currentPwd == "") {
		msg("��ǰ���벻��Ϊ�գ�");
		return; 
	} 
	if(newPwd == "") {
		msg("�����벻��Ϊ�գ�");
		return; 
	}
	if(againNewPwd == "" && againNewPwd != newPwd) {
		msg("��������������벻һ�£�");
		return; 
	}
	if(currentPwd == newPwd) {
		msg("������������벻����ͬ��");
		return; 
	}
	
	if(hnuer.userChangePwd(currentUser, currentPwd, newPwd) == -1) {
		msg("��ǰ���벻��ȷ��");
		return; 
	}
	
	click_logout(LinksArr[3], 0, 0);
	msg("�޸�����ɹ��������µ�¼");
}

void page_user_settings() {
	// Links
	linksArrLen = 8;
	Link * linksArr = new Link[linksArrLen];// �������� 
	linksArr[0] = Link(4, 3, "����ͼ��",  click_tab_user_library);
	linksArr[1] = Link(4, 20, "���ļ�¼", click_tab_user_logs);
	linksArr[2] = Link(4, 35, "*�ʻ�����", click_tab_user_settings);
	linksArr[3] = Link(4, 108, "�˳���¼", click_logout);
	linksArr[4] = Link(26, 30, "| ȷ���޸� |", click_user_settings_changePwdOk);
	
	
	if(LinksArr != NULL) {// �ͷ�ԭ���������ݲ�����ָ�� 
		delete[] LinksArr;
	}
	LinksArr = linksArr;
	
	// Texts
	textsArrLen = 7;
	Text * textsArr = new Text[textsArrLen];
	textsArr[0] = Text(7, 3, "> �ʻ�������Ϣ");
	textsArr[1] = Text(10, 11, "�û�����");
	textsArr[2] = Text(10, 20, currentUser);
	textsArr[3] = Text(13, 3, "> �޸�����");
	textsArr[4] = Text(16, 9, "��ǰ���룺");
	textsArr[5] = Text(19, 11, "�����룺");
	textsArr[6] = Text(22, 3, "�ٴ����������룺");
	
	if(TextsArr != NULL) {
		delete[] TextsArr;
	}
	TextsArr = textsArr;
	
	// InputBoxs
	inputBoxsArrLen = 3;
	InputBox * inputBoxsArr = new InputBox[inputBoxsArrLen];
	inputBoxsArr[0] = InputBox(16, 20, "��ǰ����", ""); // ��ǰ���� 
	inputBoxsArr[1] = InputBox(19, 20, "������", ""); // ������ 
	inputBoxsArr[2] = InputBox(22, 20, "�ظ�������", ""); // �ٴ����������� 
	inputBoxsArr[0].isPassword = true;
	inputBoxsArr[1].isPassword = true;
	inputBoxsArr[2].isPassword = true;
	
	if(InputBoxsArr != NULL) {
		delete[] InputBoxsArr;
	}
	InputBoxsArr = inputBoxsArr;
	
}
