#include <iostream>
#include<cstdlib>    //ʹ��system�����cstdlib��,���������д�С 
#include <windows.h>
using namespace std;
//#include "./include/Logs.h" // ���ļ�¼��  
//#include "./include/SchoolUserList.h" // ѧУ�û��� 
//#include "./include/Library.h" // ѧУ�û���
//#include "./include/variable.h" // �ṩȫ�ֵ�һЩ����
#include "./include/util.h" // �ṩһЩ���� 
#include "./include/router.h" // ·�ɣ���Ҫ�����л�ҳ�� 
#include "./include/listener.h" // �¼������� 

int main() {
	system("mode con cols=123 lines=36"); // ��֤�����д��ڵĿ���㹻�� 
	renderFramework(); // ��Ⱦ��� 
	checkoutPage("page_admin_login"); // ��Ⱦ����Ա��¼ҳ 
	gotoxy(clientHeight + 1, 0);
	lunch_listener();
	return 0;
}
