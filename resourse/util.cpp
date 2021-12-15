// 此文件提供一些工具函数
#include <iostream>
#include <windows.h>
using namespace std;

#include "../include/util.h"
#include "../include/variable.h"

// 移动光标
void gotoxy(short int row, short int col) {
	COORD pos = {col, row};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

// 修改输出颜色 
int changeColor(int r, int g, int b) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)return GetLastError();
	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))return GetLastError();
	dwMode |= 0x0004;
	if (!SetConsoleMode(hOut, dwMode))return GetLastError();
//	for(int i = 0; i < n; i++) {
//		if(c == 'a'){
//			wprintf(L"\x1b[48;2;%d;%d;%dm", 255, 255, 255);
//		}else {
//			wprintf(L"\x1b[48;2;%d;%d;%dm", 0, 0, 0);
//		}
		wprintf(L"\x1b[38;2;%d;%d;%dm", r, g, b);
//	}
	return 0;
}

// 输出n次c 
void printChar(int n, char c) {
	for(int i = 0; i < n; i++) {
		cout << c;
	}
}

// 渲染框架 
void renderFramework() {
	// 输出右侧边框 
	for(int i = 0; i < clientHeight; i++) {
		gotoxy(i, clientWidth);
		cout << '|'; 	
	}
	
	// 输出底部边框 
	gotoxy(clientHeight, 0);
	printChar(clientWidth, '-');
	
	// 输出标题 
	gotoxy(1, 52);
	cout << "图书馆管理系统";
	
	// 输出导航栏上下边框 
	gotoxy(3, 1);
	printChar(clientWidth - 2, '-');
	gotoxy(5, 1);
	printChar(clientWidth - 2, '-');
}

// 渲染所有Link
void renderLinks() {
	for(int i = 0; i < linksArrLen; i++) {
		gotoxy(LinksArr[i].row, LinksArr[i].col);
		cout << LinksArr[i].text;
	}
}
// 渲染所有Text
void renderTexts() {
	for(int i = 0; i < textsArrLen; i++) {
		gotoxy(TextsArr[i].row, TextsArr[i].col);
		cout << TextsArr[i].text;
	}
}
// 渲染所有InputBox
void renderInputBoxs() {
	for(int i = 0; i < inputBoxsArrLen; i++) {
		InputBoxsArr[i].renderValue();
		gotoxy(InputBoxsArr[i].row + 1, InputBoxsArr[i].col);
		printChar(InputBoxsArr[i].width, '-');
	}
}

// 清屏
void clearElements() {
	gotoxy(4, 0);
	printChar(clientWidth, ' ');
	for(int i = 6; i < clientHeight; i++) {
		gotoxy(i, 0);
		printChar(clientWidth, ' ');
	}
} 

// 渲染所有元素
void renderElements() {
	renderLinks();// 渲染所有Link
	renderTexts();// 渲染所有Text
	renderInputBoxs();// 渲染所有InputBox
} 

// 输入框获取焦点时的遮挡层 
void renderModel(bool isFocus) {
	if(isFocus) {
		changeColor(95, 99, 103);	
	}else {
		changeColor(255, 255, 255);	
	}
	renderFramework();
	renderElements();
	
	changeColor(255, 255, 255);
	InputBoxsArr[currentInputBoxIndex].renderValue();
	gotoxy(InputBoxsArr[currentInputBoxIndex].row + 1, InputBoxsArr[currentInputBoxIndex].col);
	printChar(InputBoxsArr[currentInputBoxIndex].width, '-');
}

// 左下角消息 
void msg(string str) {
	gotoxy(clientHeight + 1, 0);
	printChar(clientWidth, ' ');
	gotoxy(clientHeight + 1, 0);
	cout << str; 
}
void msg(int n) {
	gotoxy(clientHeight + 1, 0);
	printChar(clientWidth, ' ');
	gotoxy(clientHeight + 1, 0);
	cout << n; 
}

