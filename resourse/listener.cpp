#include <windows.h>                			//GetAsyncKeyState所需头文件
#include <iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //用来检测按键的点击事件
using namespace std;

#include "../include/variable.h"
#include "../include/listener.h"

// 开始监听鼠标点击
void lunch_listener() {
	// 移除快速编辑模式(对于win10用户)
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);

	while(1) {                      			//循环检测
		if(KEY_DOWN(VK_LBUTTON)) {  			//鼠标左键按下
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(h,&p);               //获取鼠标在窗口上的位置
			GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont); //获取字体信息
			int col=p.x/=consoleCurrentFont.dwFontSize.X;
			int row=p.y/=consoleCurrentFont.dwFontSize.Y;

			// 监听所有的链接Link
			for(int i = 0; i < linksArrLen; i++) {
				if(LinksArr[i].check(row, col)) {
//					currentInputBoxIndex = i;
					LinksArr[i].click(row, col);
				}
			}

			// 监听所有的输入框
			for(int i = 0; i < inputBoxsArrLen; i++) {

				if(InputBoxsArr[i].check(row, col)) {
					currentInputBoxIndex = i;
					InputBoxsArr[i].click();
				}
			}

//			printf("key down (%d,%d)\n",row,col);
		}
		Sleep(100);                  			//等待100毫秒，减少CPU占用
	}
}
