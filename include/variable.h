

#ifndef VARIABLE_H
#define VARIABLE_H

// 提供全局变量
#include <iostream>
#include <conio.h> // 用到getch
using namespace std;

#include "Logs.h" // 借阅记录类  
#include "SchoolUserList.h" // 学校用户类 
#include "Library.h" // 学校用户类
#include "common.h" // 页面中的元素 


// 该文件最前被引入，所以如果某个文件中出现未定义错误就把声明语句放这儿

extern SchoolUserList hnuer; // 实例化所学校用户列表 
extern Library lib; // 实例化图书馆
extern Logs logs; // 实例化借阅记录 

//void checkoutPage(string target, int index = 0);
//void printChar(int n, char c);
//void renderModel(bool isFocus);
//void msg(string str);
//void msg(int n);
//void gotoxy(short int y, short int x);


// 页面中被获得焦点的输入框在数组中的索引
extern int currentInputBoxIndex;

extern int clientWidth; // 客户端宽度
extern int clientHeight; // 客户端高度
extern int linksArrLen; // 数组长度
extern Link * LinksArr; // 存储页面中所有可点击的元素
extern int textsArrLen;// 数组长度
extern Text * TextsArr; // 存储页面中所有只用于显示的文本
extern int inputBoxsArrLen;// 数组长度
extern InputBox * InputBoxsArr; // 存储页面中所有只用于显示的文本
extern string currentUser; // 当前登录的用户名


#endif



