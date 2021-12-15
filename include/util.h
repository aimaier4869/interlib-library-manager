// 此文件提供一些工具函数
#include <iostream>
#include <windows.h>
using namespace std;

#ifndef UTIL_H
#define UTIL_H

// 移动光标
void gotoxy(short int row, short int col);

// 修改输出颜色 
int changeColor(int r, int g, int b);

// 输出n次c 
void printChar(int n, char c);

// 渲染框架 
void renderFramework();

// 渲染所有Link
void renderLinks();

// 渲染所有Text
void renderTexts();

// 渲染所有InputBox
void renderInputBoxs();

// 清屏
void clearElements();

// 渲染所有元素
void renderElements();

// 输入框获取焦点时的遮挡层 
void renderModel(bool isFocus);

// 左下角消息 
void msg(string str);
void msg(int n);

#endif

