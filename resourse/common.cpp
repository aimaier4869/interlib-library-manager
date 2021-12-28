// 页面中的元素定义
#include <iostream>
#include <conio.h> // 用到getch
#include <fstream>
using namespace std;

#include "../include/variable.h"
#include "../include/common.h"
#include "../include/util.h"


void testClick(const Link & self, int row, int col) {
//	cout << self.text;
	msg(self.text);
}

// 页面中可点击的元素
Link::Link() {};
Link::~Link() {};
Link::Link(int row, int col, string text, void (*handle)(const Link & self, int row, int col), int height, int width) {
	this->text = text;
	this->col = col;
	this->row = row;
	this->width = width ? width : text.length();
	this->height = height;
	this->handle = handle;
};
// 验证是否被鼠标点击了
bool Link::check(int row, int col) {
	return row >= this->row && row < this->row + this->height && col >= this->col && col <= this->col + this->width;
};
// 被判定为点击时运行这个函数
void Link::click(int row, int col) {
	(*handle)(*this, row, col);
};

// 页面中只用于显示的文本

Text::Text() {}
Text::~Text() {}
Text::Text(int row, int col, string text) {
	this->text = text;
	this->col = col;
	this->row = row;
}

// 页面中的输入框

InputBox::InputBox() {};
InputBox::~InputBox() {};
InputBox::InputBox(int row, int col, string label, string value, int height, int width) {
	this->label = label;
	this->value = value;
	this->col = col;
	this->row = row;
	this->width = width ? width : 20;
	this->height = height;
	this->isPassword = false;
}
// 验证是否被鼠标点击了
bool InputBox::check(int row, int col) {
	return row >= this->row && row < this->row + this->height && col >= this->col && col <= this->col + this->width;
};
void InputBox::renderValue() {
	gotoxy(this->row, this->col);
	if(this->isPassword) { // 如果是密码框则输出*
		printChar(this->value.length(), '*');
	} else {
		cout << this->value;
	}
}
// 被判定为点击时运行这个函数
void InputBox::click() {
	// 更新右下角的提示信息
	msg("你正在输入 " + this->label + ",按 回车 键结束输入。");
	// 渲染遮挡层
	renderModel(true);
	// 分类号单独处理，这是新加的
	if(this->label == "分类号") {
		// 如果是分类号框

		// 清屏
		for(int i = 6; i < 32; i++) {
			gotoxy(i, 0);
			printChar(this->col - 10, ' ');
		}
		for(int i = this->row + 2; i < 32; i++) {
			gotoxy(i, this->col - 10);
			printChar(130 - this->col, ' ');
		}

		// 从文件中读取分类号信息
		string arr[545][2];
		fstream fs;
		fs.open("database\\Types.txt", ios::in);
		for(int i = 0; i < 545; i++) {
			fs >> arr[i][0] >> arr[i][1];
		}
		fs.close();

		// 渲染列表
		for(int i = 0, r = 7; i < 545; i++) {
			if(arr[i][0].length() - 1 == this->value.length() && arr[i][0].substr(0, this->value.length()) == this->value) {
				gotoxy(r++, 5);
				cout << arr[i][0] << "\t" << arr[i][1];
			}
		}

		// 光标移动到输入框开头
		gotoxy(this->row, this->col + this->value.length());
		char key;
		while(1) {
			key = getch();
			if(key >= 97 && key < 97 + 26 || key >= 65 && key < 65 + 26 || key >= 48 && key < 48 + 10) {
				if(key >= 97) {
					key -= 32;
				}
				this->value += key;
				cout << key;
				// 清屏
				for(int i = 6; i < 32; i++) {
					gotoxy(i, 0);
					printChar(this->col - 10, ' ');
				}
				// 更新分类列表
				for(int i = 0, r = 7; i < 545; i++) {
					if(arr[i][0].length() - 1 == this->value.length() && arr[i][0].substr(0, this->value.length()) == this->value) {
						gotoxy(r++, 5);
						cout << arr[i][0] << "\t" << arr[i][1];
					}
				}
				gotoxy(this->row, this->col + this->value.length());
			} else if(key == 13) {
				// 清屏
				for(int i = 6; i < 32; i++) {
					gotoxy(i, 0);
					printChar(this->col - 10, ' ');
				}
				// 按的是回车则结束输入
				break;
			} else if(key == 8 && this->value.length() > 0) {
				// 按的是退格键，把value的最后一个字符去掉
				this->value = this->value.substr(0, this->value.length() - 1);
				gotoxy(this->row, this->col + this->value.length());
				cout << " ";
				gotoxy(this->row, this->col + this->value.length());
				// 清屏
				for(int i = 6; i < 32; i++) {
					gotoxy(i, 0);
					printChar(this->col - 10, ' ');
				}
				// 更新分类列表
				for(int i = 0, r = 7; i < 545; i++) {
					if(arr[i][0].length() - 1 == this->value.length() && arr[i][0].substr(0, this->value.length()) == this->value) {
						gotoxy(r++, 5);
						cout << arr[i][0] << "\t" << arr[i][1];
					}
				}
				gotoxy(this->row, this->col + this->value.length());
			}
		}

	} else if(!this->isPassword) {
		// 如果不是密码框
		// 清掉原有的输出
		gotoxy(this->row, this->col);
		printChar(this->value.length(), ' ');

		gotoxy(this->row, this->col);// 光标移动到输入框开头
		string temp;
		getline(cin, temp);
		this->value = temp;
	} else {
		// 如果是密码框
		gotoxy(this->row, this->col + this->value.length());// 光标移动到输入框开头
		char key;
		while(1) {
			key = getch();
			if(key >= 97 && key < 97 + 26 || key >= 65 && key < 65 + 26 || key >= 48 && key < 48 + 10) {
				this->value += key;
				cout << "*";
			} else if(key == 13) {
				// 按的是回车则结束输入
				break;
			} else if(key == 8 && this->value.length() > 0) {
				// 按的是退格键，把value的最后一个字符去掉
				this->value = this->value.substr(0, this->value.length() - 1);
				gotoxy(this->row, this->col + this->value.length());
				cout << " ";
				gotoxy(this->row, this->col + this->value.length());
			}
		}
	}

	// 点击搜索按钮
	if(this->label == "分类号") {
		for(int i = 0; i < linksArrLen; i++) {
			if(LinksArr[i].text == "| 搜索 |") {
				LinksArr[i].click(0, 0);
				break;
			}
		}
	}

	renderModel(false); // 去掉遮挡层
	currentInputBoxIndex = -1; // 将激活的输入框
	msg("输入结束！");
}







