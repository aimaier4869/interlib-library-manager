#include <fstream>
#include "Book.h"

#ifndef LIBRARY_H
#define LIBRARY_H

class Library {
	private:
		Book * booksArr;
	public:
		int totalCount;
		Book ** currentPageBooksArr; // ��ǰҳͼ������
		Book ** tempBooksArr; // ��ʱ���飬����ʱʹ��
		int tempBooksArrLen;
		int updatePageMode; // ��ҳģʽ��0��ʾ���ܱ����л���1��ʾ�ӵ�ǰ������л�
		int currentPageIndex; // ��ǰ��ҳ����չʾ��ҳ��index
		int currentPageCount; // ��ǰҳ����չʾ���û�����
		Library() ;
		// ��ȡ�ļ��е����ݲ����µ������У������û�ɾ���û�ʱ��Ҫ���»�ȡ���ݣ����Է�װ����������
		void readDataFromFile();
		// ͨ���������ң������ҵ���������û�ҵ�����0;
		int searchBook(Book book);
		// ͨ��ISBN�õ�ͼ�����ƣ���Ҫ���ڽ��ļ�¼
		string getBookNameByISBN(string ISBN) ;
		// ��ҳչʾ��������ת֮��ҳ���е���������
		// pageIndexҪ��ת���ڼ�ҳ��countÿҳչʾ���������ݣ�Ĭ��10��
		// �����ⲿ�ж��Ƿ���Ե����һҳ����֤�������pageIndex�ǲ�С��0���Ҳ�������ҳ��
		// ���pageIndex���˵��´��뱨���Ҳ���
		// ������getTotalPageCount�����õ���ҳ��
		int updateCurrentPage(int pageIndex, int count = 10);
		// ��ȡÿҳչʾcount�����ݵĻ������Էֶ���ҳ
		int getTotalPageCount(int count = 10);
//		 ɾ��ͼ�飬����currentPageBooksArr�е�index
		void removeBook(int index);
		// ����ͼ�飬�����ɹ����ص�ǰҳͼ������ ,ʧ���˷���-1
		int addBook(Book book);
		// �޸�ͼ�飬�����ɹ����ص�ǰҳͼ������ ,ʧ���˷���-1
		int modifyBook(Book book);
};

#endif
