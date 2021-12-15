#include <iostream>
#include<cstdlib>    //使用system需调用cstdlib库,调整命令行大小 
#include <windows.h>
using namespace std;
//#include "./include/Logs.h" // 借阅记录类  
//#include "./include/SchoolUserList.h" // 学校用户类 
//#include "./include/Library.h" // 学校用户类
//#include "./include/variable.h" // 提供全局的一些变量
#include "./include/util.h" // 提供一些工具 
#include "./include/router.h" // 路由，主要负责切换页面 
#include "./include/listener.h" // 事件监听器 

int main() {
	system("mode con cols=123 lines=36"); // 保证命令行窗口的宽高足够大 
	renderFramework(); // 渲染框架 
	checkoutPage("page_admin_login"); // 渲染管理员登录页 
	gotoxy(clientHeight + 1, 0);
	lunch_listener();
	return 0;
}
