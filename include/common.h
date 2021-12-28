

#ifndef COMMON_H
#define COMMON_H

// ҳ���е�Ԫ������ 
#include <iostream>
#include <conio.h> // �õ�getch
using namespace std;

#include "Logs.h" // ���ļ�¼��  
#include "SchoolUserList.h" // ѧУ�û��� 
#include "Library.h" // ѧУ�û���

// ���ļ���ǰ�����룬�������ĳ���ļ��г���δ�������Ͱ������������

// ҳ���пɵ����Ԫ��
class Link {
	public:
		string text; // ����
		int col; // ������
		int row; // ������
		int width; // ���
		int height; // �߶�
		void (*handle)(const Link & self, int row, int col);
		Link();
		~Link();
		Link(int row, int col, string text, void (*handle)(const Link & self, int row, int col), int height = 1, int width = 0);
		// ��֤�Ƿ��������
		bool check(int row, int col);
		// ���ж�Ϊ���ʱ�����������
		void click(int row, int col);
};

// ҳ����ֻ������ʾ���ı�
class Text {
	public:
		string text; // ����
		int col; // ������
		int row; // ������
		Text();
		~Text();
		Text(int row, int col, string text);
		// ����=�����
		Text& operator =(const Text * b);
};

// ҳ���е������
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
		InputBox(int row, int col, string label = "���������", string value = "", int height = 2, int width = 0);
		// ��֤�Ƿ��������
		bool check(int row, int col);
		void renderValue();
		// ���ж�Ϊ���ʱ�����������
		void click();
};

void testClick(const Link & self, int row, int col);

#endif



