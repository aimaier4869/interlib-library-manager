// ·�ɣ���Ҫ�Ǹ����л�ҳ��
#include "../include/page_admin_login.h" // ��ҳ 
#include "../include/page_admin_userlist.h" // �û�����ҳ�� 
#include "../include/page_admin_library.h" // ͼ�����ҳ�� 
#include "../include/page_admin_book_add.h" // ����ͼ��ҳ�� 
#include "../include/page_admin_book_modify.h" // �޸�ͼ��ҳ�� 
#include "../include/page_user_login.h" // ѧУ�û���¼ҳ�� 
#include "../include/page_user_library.h" // ѧУ�û�����ͼ��ҳ�� 
#include "../include/page_user_logs.h" // ѧУ�û����ļ�¼ҳ��
#include "../include/page_user_settings.h" // �ʻ�����ҳ�� 

#include "../include/router.h"
#include "../include/util.h"


// �ڶ�������indexֻΪpage_admin_book_modifyҳ����� 
// debug:����Ĭ�ϲ���ֻ�����������Ǳ�д 
void checkoutPage(string target, int index) {
	clearElements(); // ���� 
	if(target == "page_admin_login") {
		page_admin_login();
	}else if(target == "page_admin_userlist") {
		page_admin_userlist();
	}else if(target == "page_admin_library") {
		page_admin_library();
	}else if(target == "page_admin_book_add") {
		page_admin_book_add();
	}else if(target == "page_admin_book_modify") {
		page_admin_book_modify(index);
	}else if(target == "page_user_login") {
		page_user_login();
	}else if(target == "page_user_library") {
		page_user_library();
	}else if(target == "page_user_logs") {
		page_user_logs();
	}else if(target == "page_user_settings") {
		page_user_settings();
	}
	renderElements(); // ��Ⱦ��ǰҳ���е�Ԫ�� 
} 
