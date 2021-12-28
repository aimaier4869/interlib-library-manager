

#ifndef COMMON_H
#define COMMON_H

// 页面中的元素声明 
#include <iostream>
#include <conio.h> // 用到getch
using namespace std;

#include "Logs.h" // 借阅记录类  
#include "SchoolUserList.h" // 学校用户类 
#include "Library.h" // 学校用户类

// 该文件最前被引入，所以如果某个文件中出现未定义错误就把声明语句放这儿

// 页面中可点击的元素
class Link {
	public:
		string text; // 文字
		int col; // 所在列
		int row; // 所在行
		int width; // 宽度
		int height; // 高度
		void (*handle)(const Link & self, int row, int col);
		Link();
		~Link();
		Link(int row, int col, string text, void (*handle)(const Link & self, int row, int col), int height = 1, int width = 0);
		// 验证是否被鼠标点击了
		bool check(int row, int col);
		// 被判定为点击时运行这个函数
		void click(int row, int col);
};

// 页面中只用于显示的文本
class Text {
	public:
		string text; // 文字
		int col; // 所在列
		int row; // 所在行
		Text();
		~Text();
		Text(int row, int col, string text);
		// 重载=运算符
		Text& operator =(const Text * b);
};

// 页面中的输入框
class InputBox {
	public:
		string label;
		string value;
		int col;
		int row;
		int width;
		int height;
		bool isPassword;
		InputBox();
		~InputBox();
		InputBox(int row, int col, string label = "输入框内容", string value = "", int height = 2, int width = 0);
		// 验证是否被鼠标点击了
		bool check(int row, int col);
		void renderValue();
		// 被判定为点击时运行这个函数
		void click();
};

void testClick(const Link & self, int row, int col);

#endif



