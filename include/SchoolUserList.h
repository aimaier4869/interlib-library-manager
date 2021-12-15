#include <fstream>
#include "SchoolUser.h"

#ifndef SCHOOLUSERLIST_H
#define SCHOOLUSERLIST_H

// 学校用户列表类，主要功能存储用户，搜索用户，分页展示时的数据处理，新增用户，删除用户，调用重置密码
class SchoolUserList {
	private:
		SchoolUser * usersArr;
	public:
		int totalCount;
		SchoolUser ** currentPageUsersArr; // 当前页面需要渲染的用户列表，每一项是个指针，重新赋值是无需delete之前有的内容，因为学校用户列表被析构是所有学生用户都会被delete
		int currentPageIndex; // 当前在页面中展示的页面index
		int currentPageCount; // 当前页面中展示的用户数量
		// 创建时就从文件中读取所有用户信息，并存到自己的数组中
		SchoolUserList();
		// 读取文件中的数据并更新到属性中，新增用户删除用户时需要重新获取数据，所以封装到函数中了
		void readDataFromFile();
		// 析构函数
		~SchoolUserList();
		// 通过用户名找到唯一的用户，找到了返回1，未找到返回0;
		int searchUserByUname(string uname);
		// 用户登录,-1该用户不存在，0密码不正确，1登录成功
		int userLogin(string username, string pwd);
		// 修改密码，-1输入的当前密码不正确，1修改成功
		int userChangePwd(string username, string pwd, string newPwd);
		// 分页展示，返回跳转之后页面中的数据数量
		// pageIndex要跳转到第几页，count每页展示多少条数据，默认10条
		// 请在外部判断是否可以点击下一页，保证你输入的pageIndex是不小于0并且不超过总页数
		// 如果pageIndex错了导致代码报错我不管
		// 可以用getTotalPageCount函数拿到总页数
		int updataCurrentPage(int pageIndex, int count = 10);
		// 获取每页展示count条数据的话共可以分多少页
		int getTotalPageCount(int count = 10);
		// 重置密码，传入currentPageUsersArr中的index
		void resetPassword(int index);
		// 删除用户，传入currentPageUsersArr中的index
		void removeUser(int index);
		// 新增用户，新增成功返回当前页用户数量 ,失败了返回-1
		int addUserByUname(string uname);
};

#endif
