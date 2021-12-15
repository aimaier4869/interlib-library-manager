// 提供全局变量
#include "../include/variable.h"
#include "../include/util.h"
#include "../include/common.h" // 页面中的元素 

#include <iostream>
using namespace std; 

//void checkoutPage(string target, int index = 0);
//void printChar(int n, char c);
//void renderModel(bool isFocus);
//void msg(string str);
//void msg(int n);
//void gotoxy(short int y, short int x);

// 页面中被获得焦点的输入框在数组中的索引
int currentInputBoxIndex = -1;

int clientWidth = 120; // 客户端宽度
int clientHeight = 34; // 客户端高度
int linksArrLen = 0; // 数组长度
Link * LinksArr; // 存储页面中所有可点击的元素
int textsArrLen = 0;// 数组长度
Text * TextsArr; // 存储页面中所有只用于显示的文本
int inputBoxsArrLen = 0;// 数组长度
InputBox * InputBoxsArr; // 存储页面中所有只用于显示的文本
string currentUser = ""; // 当前登录的用户名

SchoolUserList hnuer; // 湖大人
Library lib; // 实例化图书馆
Logs logs; // 实例化借阅记录 


