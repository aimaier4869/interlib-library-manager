#include <windows.h>                			//GetAsyncKeyState����ͷ�ļ�
#include <iostream>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //������ⰴ���ĵ���¼�
using namespace std;

#include "../include/variable.h"
#include "../include/listener.h"

// ��ʼ���������
void lunch_listener() {
	// �Ƴ����ٱ༭ģʽ(����win10�û�)
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);

	while(1) {                      			//ѭ�����
		if(KEY_DOWN(VK_LBUTTON)) {  			//����������
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(h,&p);               //��ȡ����ڴ����ϵ�λ��
			GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont); //��ȡ������Ϣ
			int col=p.x/=consoleCurrentFont.dwFontSize.X;
			int row=p.y/=consoleCurrentFont.dwFontSize.Y;

			// �������е�����Link
			for(int i = 0; i < linksArrLen; i++) {
				if(LinksArr[i].check(row, col)) {
//					currentInputBoxIndex = i;
					LinksArr[i].click(row, col);
				}
			}

			// �������е������
			for(int i = 0; i < inputBoxsArrLen; i++) {

				if(InputBoxsArr[i].check(row, col)) {
					currentInputBoxIndex = i;
					InputBoxsArr[i].click();
				}
			}

//			printf("key down (%d,%d)\n",row,col);
		}
		Sleep(100);                  			//�ȴ�100���룬����CPUռ��
	}
}
