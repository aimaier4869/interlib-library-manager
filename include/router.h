// 路由，主要是负责切换页面
#include "page_admin_login.h" // 首页 
#include "page_admin_userlist.h" // 用户管理页面 
#include "page_admin_library.h" // 图书管理页面 
#include "page_admin_book_add.h" // 新增图书页面 
#include "page_admin_book_modify.h" // 修改图书页面 
#include "page_user_login.h" // 学校用户登录页面 
#include "page_user_library.h" // 学校用户借阅图书页面 
#include "page_user_logs.h" // 学校用户借阅记录页面
#include "page_user_settings.h" // 帐户设置页面 


// 第二个参数index只为page_admin_book_modify页面服务 
// debug:函数默认参数只可以在声明那边写 
void checkoutPage(string target, int index = 0);
