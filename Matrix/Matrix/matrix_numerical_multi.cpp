#include <conio.h>
#include <iostream>
#include<iomanip>
#include "Matrix.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/************************
ʵ�־������˵Ĺ���
*************************/
void nummulti()
{
	const char* content = "����";
	while (true)
	{
		present_title(content);

		int nrows, ncols;
		nrows = input_size(0);
		if (nrows == 0)
			break;
		ncols = input_size(1);
		if (ncols == 0)
			break;

		//��ʼ���ӷ�
		int* matrix1 = new(nothrow) int[nrows * ncols];  //����һά����
		if (matrix1 == NULL)
		{
			cout << "�ڴ����ʧ�ܣ�" << endl;
			return;
		}

		cout << "\n�������������������ľ���: ";
		input_matrix(matrix1, nrows, ncols);
		int multiplier = input_multiplier();
		
		int *result = inner_nummulti(matrix1, nrows, ncols,multiplier);
		output_matrix(result, nrows, ncols);
		delete[]matrix1;
		delete[]result;
		matrix1 = result = NULL;

		int re = return_menu();
		if (re == 0)
			break;
	}
}

/*********************************
���ܣ����ڲ�ʵ�־�������
������ԭ����������������
����ֵ��ָ��������ĳ˻�
*******************************/
int* inner_nummulti(int* matrix1, int nrows, int ncols, int multiplier)
{
	int* result = new(nothrow) int[nrows * ncols];
	if (result == NULL)
	{
		cout << "�ڴ����ʧ�ܣ�" << endl;
		exit(0);
	}
	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			result[ncols * i + j] = multiplier * matrix1[ncols * i + j];
	return result;
}

/*************************
���ܣ���������ʱ�ĳ���
����ֵ������
***************************/
int input_multiplier()
{
	int multiplier;
	while (true)
	{
		cout << "\n���������: ";
		cin >> multiplier;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	return multiplier;
}

/******************************
���ܣ�����������˵���ʽ
������ԭ���󣬳����������������������
******************************/
void output_matrix_nummulti(int* matrix, int multiplier, int* result,int nrows,int ncols)
{
	cout << "�þ���������������" << endl;
	cout << "��" << setw(4 * ncols + 2) << "��";
	cout << "     ";
	cout << "��" << setw(4 * ncols + 2) << "��" << endl;;
	for (int i = 0; i < nrows; i++)
	{
		cout << "��";
		for (int j = 0; j < ncols; j++)
			cout << setw(4) << matrix[ncols * i + j];
		cout << "��" << endl;
		if (i == nrows / 2)
			cout << " x" << setw(3) << multiplier;
		cout << "��";
		for (int j = 0; j < ncols; j++)
			cout << setw(4) << result[ncols * i + j];
		cout << "��" << endl;
	}
	cout << "��" << setw(4 * ncols + 2) << "��";
	cout << "     ";
	cout << "��" << setw(4 * ncols + 2) << "��";
}
