// �ṩȫ�ֱ���
#include "../include/variable.h"
#include "../include/util.h"
#include "../include/common.h" // ҳ���е�Ԫ�� 

#include <iostream>
using namespace std; 

//void checkoutPage(string target, int index = 0);
//void printChar(int n, char c);
//void renderModel(bool isFocus);
//void msg(string str);
//void msg(int n);
//void gotoxy(short int y, short int x);

// ҳ���б���ý����������������е�����
int currentInputBoxIndex = -1;

int clientWidth = 120; // �ͻ��˿��
int clientHeight = 34; // �ͻ��˸߶�
int linksArrLen = 0; // ���鳤��
Link * LinksArr; // �洢ҳ�������пɵ����Ԫ��
int textsArrLen = 0;// ���鳤��
Text * TextsArr; // �洢ҳ��������ֻ������ʾ���ı�
int inputBoxsArrLen = 0;// ���鳤��
InputBox * InputBoxsArr; // �洢ҳ��������ֻ������ʾ���ı�
string currentUser = ""; // ��ǰ��¼���û���

SchoolUserList hnuer; // ������
Library lib; // ʵ����ͼ���
Logs logs; // ʵ�������ļ�¼ 


