#include <windows.h>                			//GetAsyncKeyState����ͷ�ļ�
#include <iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //������ⰴ���ĵ���¼�
using namespace std;

#ifndef LISTENER_H
#define LISTENER_H

//POINT p;
static HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
static HWND h = GetForegroundWindow();
static CONSOLE_FONT_INFO consoleCurrentFont;

// ��ʼ��������� 
void lunch_listener(); 

#endif
