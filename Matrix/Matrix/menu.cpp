#include<iostream>
#include<iomanip>
#include<conio.h>
#include "Matrix.h"
using namespace std;


/*****************************
*���ܣ���ӡ����ʼʱ�����˵�
*****************************/
char present_menu()
{
	const char* orders[9] = {"����ӷ�","��������","����ת��",
						     "����˷�","Hadamard�˻�","������",
							 "���Ӧ��","OTSU�㷨","�˳�ϵͳ"};
	const int length = 60;
	const int height = 3;
	for (int i = 0; i < length; i++)
		cout << "*";
	cout << endl;
	for (int i = 1; i <= 9; i++)
	{
		if ((i - 1) % 3 == 0)
			cout << " *";
		cout << "    " << i % 9 << ' ' <<setiosflags(ios::left)<< setw(12) << orders[i - 1];
		cout << resetiosflags(ios::left);//���»ص��Ҷ���
		if (i % 3 == 0)
			cout << "   *" << endl;
	}
	for (int i = 0; i < length; i++)
		cout << "*";
	cout << endl;
	cout << "ѡ��˵���<0-8>: ";
	char choice;

	choice = _getch();
		
	return choice;
	
}