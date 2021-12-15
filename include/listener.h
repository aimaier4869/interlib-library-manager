#include <windows.h>                			//GetAsyncKeyState所需头文件
#include <iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //用来检测按键的点击事件
using namespace std;

#ifndef LISTENER_H
#define LISTENER_H

//POINT p;
static HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
static HWND h = GetForegroundWindow();
static CONSOLE_FONT_INFO consoleCurrentFont;

// 开始监听鼠标点击 
void lunch_listener(); 

#endif
