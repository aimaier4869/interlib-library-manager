#include <fstream>
#include "SchoolUser.h"

#ifndef SCHOOLUSERLIST_H
#define SCHOOLUSERLIST_H

// ѧУ�û��б��࣬��Ҫ���ܴ洢�û��������û�����ҳչʾʱ�����ݴ��������û���ɾ���û���������������
class SchoolUserList {
	private:
		SchoolUser * usersArr;
	public:
		int totalCount;
		SchoolUser ** currentPageUsersArr; // ��ǰҳ����Ҫ��Ⱦ���û��б�ÿһ���Ǹ�ָ�룬���¸�ֵ������delete֮ǰ�е����ݣ���ΪѧУ�û��б�����������ѧ���û����ᱻdelete
		int currentPageIndex; // ��ǰ��ҳ����չʾ��ҳ��index
		int currentPageCount; // ��ǰҳ����չʾ���û�����
		// ����ʱ�ʹ��ļ��ж�ȡ�����û���Ϣ�����浽�Լ���������
		SchoolUserList();
		// ��ȡ�ļ��е����ݲ����µ������У������û�ɾ���û�ʱ��Ҫ���»�ȡ���ݣ����Է�װ����������
		void readDataFromFile();
		// ��������
		~SchoolUserList();
		// ͨ���û����ҵ�Ψһ���û����ҵ��˷���1��δ�ҵ�����0;
		int searchUserByUname(string uname);
		// �û���¼,-1���û������ڣ�0���벻��ȷ��1��¼�ɹ�
		int userLogin(string username, string pwd);
		// �޸����룬-1����ĵ�ǰ���벻��ȷ��1�޸ĳɹ�
		int userChangePwd(string username, string pwd, string newPwd);
		// ��ҳչʾ��������ת֮��ҳ���е���������
		// pageIndexҪ��ת���ڼ�ҳ��countÿҳչʾ���������ݣ�Ĭ��10��
		// �����ⲿ�ж��Ƿ���Ե����һҳ����֤�������pageIndex�ǲ�С��0���Ҳ�������ҳ��
		// ���pageIndex���˵��´��뱨���Ҳ���
		// ������getTotalPageCount�����õ���ҳ��
		int updataCurrentPage(int pageIndex, int count = 10);
		// ��ȡÿҳչʾcount�����ݵĻ������Էֶ���ҳ
		int getTotalPageCount(int count = 10);
		// �������룬����currentPageUsersArr�е�index
		void resetPassword(int index);
		// ɾ���û�������currentPageUsersArr�е�index
		void removeUser(int index);
		// �����û��������ɹ����ص�ǰҳ�û����� ,ʧ���˷���-1
		int addUserByUname(string uname);
};

#endif
