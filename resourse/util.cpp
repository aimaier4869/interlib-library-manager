// ���ļ��ṩһЩ���ߺ���
#include <iostream>
#include <windows.h>
using namespace std;

#include "../include/util.h"
#include "../include/variable.h"

// �ƶ����
void gotoxy(short int row, short int col) {
	COORD pos = {col, row};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

// �޸������ɫ 
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

// ���n��c 
void printChar(int n, char c) {
	for(int i = 0; i < n; i++) {
		cout << c;
	}
}

// ��Ⱦ��� 
void renderFramework() {
	// ����Ҳ�߿� 
	for(int i = 0; i < clientHeight; i++) {
		gotoxy(i, clientWidth);
		cout << '|'; 	
	}
	
	// ����ײ��߿� 
	gotoxy(clientHeight, 0);
	printChar(clientWidth, '-');
	
	// ������� 
	gotoxy(1, 52);
	cout << "ͼ��ݹ���ϵͳ";
	
	// ������������±߿� 
	gotoxy(3, 1);
	printChar(clientWidth - 2, '-');
	gotoxy(5, 1);
	printChar(clientWidth - 2, '-');
}

// ��Ⱦ����Link
void renderLinks() {
	for(int i = 0; i < linksArrLen; i++) {
		gotoxy(LinksArr[i].row, LinksArr[i].col);
		cout << LinksArr[i].text;
	}
}
// ��Ⱦ����Text
void renderTexts() {
	for(int i = 0; i < textsArrLen; i++) {
		gotoxy(TextsArr[i].row, TextsArr[i].col);
		cout << TextsArr[i].text;
	}
}
// ��Ⱦ����InputBox
void renderInputBoxs() {
	for(int i = 0; i < inputBoxsArrLen; i++) {
		InputBoxsArr[i].renderValue();
		gotoxy(InputBoxsArr[i].row + 1, InputBoxsArr[i].col);
		printChar(InputBoxsArr[i].width, '-');
	}
}

// ����
void clearElements() {
	gotoxy(4, 0);
	printChar(clientWidth, ' ');
	for(int i = 6; i < clientHeight; i++) {
		gotoxy(i, 0);
		printChar(clientWidth, ' ');
	}
} 

// ��Ⱦ����Ԫ��
void renderElements() {
	renderLinks();// ��Ⱦ����Link
	renderTexts();// ��Ⱦ����Text
	renderInputBoxs();// ��Ⱦ����InputBox
} 

// ������ȡ����ʱ���ڵ��� 
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

// ���½���Ϣ 
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

