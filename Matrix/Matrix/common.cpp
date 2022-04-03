#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include"Matrix.h"
using namespace cv;
using namespace std;

/*********************************
*���ܣ���һ���س�
**********************************/
void wait_for_enter()
{
    cout << endl
        << "���س�������";
    while (_getch() != '\r')
        ;
    cout << endl
        << endl;
}

/*******************************
*���ܣ�����ʾ��Ϻ󣬵õ��û�������ǰ�����򷵻ز˵���ָ��
**********************************/
int return_menu()   //����0���˳�������1���������
{
    char order;
    cout << "\nҪ�������е�ǰ�����𣿣���N/n�������˵�����Y/y����) :";
    order=_getch();

    int re;
    while (true)
    {
        if (order == 'Y' || order == 'y')
        {
            re = 1;
            break;
        }
        else if(order=='N'||order=='n')
        {
            re = 0;
            break;
        }
        order = _getch();
    }
    return re;
}

/******************************
*���ܣ�����һ������/����
*������flag:�������ֵ�ǰ��������л�����
*************************************/
int input_size(int flag)  //flagΪ0���������У�Ϊ1����������,choice����ͬ��ѡ��
{
	int size;
	while (true)
	{
		cout << "\n����������" << ((flag == 0) ? "����" : "����") << "(��0�˳�): ";
		cin >> size;
		if (cin.good() == 0)
		{
			cout << "���벻����Ҫ������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		else if (size > 100 || size < 0)
		{
			cout << "���뷶Χ����ȷ������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else if (size == 0)
		{
			char ch;
			cout << "\nȷ���˳���?(��y/Y�˳�)" << endl;
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
				break;
			else
				continue;
		}
		else
			break;
	}
	return size;
}

/********************************
*���ܣ�ʵ��һ�����������
*������matrix��ָ�룬ָ��һ�ν������ٵĿռ�
       nrows:����
	   ncols:����
	   is_conv:��ǰ������Ƿ��Ǵ�����ľ�������ǣ�λ�û����в��
*************************************/
void input_matrix(int* matrix, int nrows, int ncols,bool is_conv)
{
	cout << "\n�밴�����к��е�˳������" << endl;
	for (int i = 0+is_conv; i < nrows+is_conv; i++)
	{
		cout << "\n�������" << i + 1-is_conv << "��:";
		for (int j = 0 + is_conv; j < ncols + is_conv; j++)
		{
			cin >> matrix[i * (ncols+2*is_conv) + j];
			if (cin.good() == 0)
			{
				cout << "\n��" << i + 1 - is_conv << "��,��" << j + 1 - is_conv << "�еľ���Ԫ�������������Ը�Ԫ������������" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
				j--;  //���ȥ�����䣡
			}
		}
	}
	
}

/*****************************
����;��ӡÿ��ģ�鿪ʼǰ�ı��ⲿ��
����:content:�ַ����������洢ÿ�����ܵ�����
*********************************/
void present_title(const char *content)
{
	system("cls");
	for (int i = 0; i < 70; i++)
		cout << "*";
	cout << endl;
	cout << setw(47) << "��������о���" << content << "����" << endl;
	for (int i = 0; i < 70; i++)
		cout << "*";
}

