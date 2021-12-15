#include <fstream>
#include "Log.h"

#ifndef LOGS_H
#define LOGS_H

class Logs {
	private:
		Log * logsArr;
	public:
		int totalCount;
		Log ** currentPageLogsArr; // ��ǰҳͼ������
		Log ** tempLogsArr; // ��ʱ���飬�ļ���ȡ��ɺ���Ѹ��û������м�¼�ҳ����ŵ����������
		int tempLogsArrLen;
//		int searchMode; // ����ģʽ��0��ʾ���ܱ���������1��ʾ����ʱ��������
//		int updatePageMode; // ��ҳģʽ��0��ʾ���ܱ����л���1��ʾ�ӵ�ǰ������л�
		int currentPageIndex; // ��ǰ��ҳ����չʾ��ҳ��index
		int currentPageCount; // ��ǰҳ����չʾ���û�����
		Logs();
		// ��ȡ�ļ��е����ݲ����µ������У������û�ɾ���û�ʱ��Ҫ���»�ȡ���ݣ����Է�װ����������
		void readDataFromFile();
		// ���µ�ǰ��¼���û��ļ�¼��Ϣ
		void updateCurrentUserLogs();
		// ͨ���������ң������ҵ���������û�ҵ�����0;
		int searchLogByISBN(string ISBN);
		// ��ҳչʾ��������ת֮��ҳ���е���������
		// pageIndexҪ��ת���ڼ�ҳ��countÿҳչʾ���������ݣ�Ĭ��10��
		// �����ⲿ�ж��Ƿ���Ե����һҳ����֤�������pageIndex�ǲ�С��0���Ҳ�������ҳ��
		// ���pageIndex���˵��´��뱨���Ҳ���
		// ������getTotalPageCount�����õ���ҳ��
		int updateCurrentPage(int pageIndex, int count = 10);
		// ��ȡÿҳչʾcount�����ݵĻ������Էֶ���ҳ
		int getTotalPageCount(int count = 10);
//		 ����ͼ�飬����ISBN���û�Ĭ��Ϊ��ǰ�û�
		// ����ʧ�ܷ���-1
		int borrowBook(string ISBN);
//		// �黹ͼ�飬�黹ʧ�ܷ���-1
		int returnBook(string ISBN);
};

#endif
