// ���ļ��ṩһЩ���ߺ���
#include <iostream>
#include <windows.h>
using namespace std;

#ifndef UTIL_H
#define UTIL_H

// �ƶ����
void gotoxy(short int row, short int col);

// �޸������ɫ 
int changeColor(int r, int g, int b);

// ���n��c 
void printChar(int n, char c);

// ��Ⱦ��� 
void renderFramework();

// ��Ⱦ����Link
void renderLinks();

// ��Ⱦ����Text
void renderTexts();

// ��Ⱦ����InputBox
void renderInputBoxs();

// ����
void clearElements();

// ��Ⱦ����Ԫ��
void renderElements();

// ������ȡ����ʱ���ڵ��� 
void renderModel(bool isFocus);

// ���½���Ϣ 
void msg(string str);
void msg(int n);

#endif

