// �ṩȫ�ֱ���
#include <iostream>
#include <conio.h> // �õ�getch
using namespace std;

#include "../include/variable.h"
#include "../include/common.h"
#include "../include/util.h"


void testClick(const Link & self, int row, int col) {
//	cout << self.text;
	msg(self.text); 
}

// ҳ���пɵ����Ԫ�� 
	Link::Link(){};
	Link::~Link(){};
	Link::Link(int row, int col, string text, void (*handle)(const Link & self, int row, int col), int height, int width) {
		this->text = text;
		this->col = col;
		this->row = row;
		this->width = width ? width : text.length();
		this->height = height;
		this->handle = handle;
	};
	// ��֤�Ƿ�������� 
	bool Link::check(int row, int col) {
		return row >= this->row && row < this->row + this->height && col >= this->col && col <= this->col + this->width;
	};
	// ���ж�Ϊ���ʱ����������� 
	void Link::click(int row, int col) {
		(*handle)(*this, row, col);
	};

// ҳ����ֻ������ʾ���ı� 

	Text::Text(){}
	Text::~Text(){}
	Text::Text(int row, int col, string text) {
		this->text = text;
		this->col = col;
		this->row = row;
	}

// ҳ���е������

	InputBox::InputBox(){};
	InputBox::~InputBox(){};
	InputBox::InputBox(int row, int col, string label, string value, int height, int width) {
		this->label = label;
		this->value = value;
		this->col = col;
		this->row = row;
		this->width = width ? width : 20;
		this->height = height;
		this->isPassword = false;
	}
	// ��֤�Ƿ�������� 
	bool InputBox::check(int row, int col) {
		return row >= this->row && row < this->row + this->height && col >= this->col && col <= this->col + this->width;
	};
	void InputBox::renderValue() {
		gotoxy(this->row, this->col);
		if(this->isPassword) { // ���������������* 
			printChar(this->value.length(), '*');
		}else {
			cout << this->value;	
		}
	}
	// ���ж�Ϊ���ʱ����������� 
	void InputBox::click() {
		// �������½ǵ���ʾ��Ϣ 
		msg("���������� " + this->label + ",�� �س� ���������롣"); 
		// ��Ⱦ�ڵ��� 
		renderModel(true);
		if(!this->isPassword) {
			// ������������ 
			// ���ԭ�е���� 
			gotoxy(this->row, this->col);
			printChar(this->value.length(), ' ');
		
			gotoxy(this->row, this->col);// ����ƶ��������ͷ 
			string temp;
			getline(cin, temp);
			this->value = temp;
		} else {
			// ���������� 
			gotoxy(this->row, this->col + this->value.length());// ����ƶ��������ͷ
			char key;
			while(1) {
				key = getch();
				if(key >= 97 && key < 97 + 26 || key >= 65 && key < 65 + 26 || key >= 48 && key < 48 + 10) {
					this->value += key;
					cout << "*";
				}else if(key == 13) { 
				// �����ǻس���������� 
					break;
				}else if(key == 8 && this->value.length() > 0) { 
				// �������˸������value�����һ���ַ�ȥ��
					this->value = this->value.substr(0, this->value.length() - 1);
					gotoxy(this->row, this->col + this->value.length());
					cout << " ";
					gotoxy(this->row, this->col + this->value.length());
				}
			}
		} 
			
		renderModel(false); // ȥ���ڵ��� 
		currentInputBoxIndex = -1; // ������������ 
		msg("���������"); 
	}







