

#ifndef VARIABLE_H
#define VARIABLE_H

// �ṩȫ�ֱ���
#include <iostream>
#include <conio.h> // �õ�getch
using namespace std;

#include "Logs.h" // ���ļ�¼��  
#include "SchoolUserList.h" // ѧУ�û��� 
#include "Library.h" // ѧУ�û���
#include "common.h" // ҳ���е�Ԫ�� 


// ���ļ���ǰ�����룬�������ĳ���ļ��г���δ�������Ͱ������������

extern SchoolUserList hnuer; // ʵ������ѧУ�û��б� 
extern Library lib; // ʵ����ͼ���
extern Logs logs; // ʵ�������ļ�¼ 

//void checkoutPage(string target, int index = 0);
//void printChar(int n, char c);
//void renderModel(bool isFocus);
//void msg(string str);
//void msg(int n);
//void gotoxy(short int y, short int x);


// ҳ���б���ý����������������е�����
extern int currentInputBoxIndex;

extern int clientWidth; // �ͻ��˿��
extern int clientHeight; // �ͻ��˸߶�
extern int linksArrLen; // ���鳤��
extern Link * LinksArr; // �洢ҳ�������пɵ����Ԫ��
extern int textsArrLen;// ���鳤��
extern Text * TextsArr; // �洢ҳ��������ֻ������ʾ���ı�
extern int inputBoxsArrLen;// ���鳤��
extern InputBox * InputBoxsArr; // �洢ҳ��������ֻ������ʾ���ı�
extern string currentUser; // ��ǰ��¼���û���


#endif



