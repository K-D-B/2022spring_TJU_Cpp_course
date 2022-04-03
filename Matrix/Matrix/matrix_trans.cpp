#include<iostream>
#include"Matrix.h"
using namespace std;

/*******************************
���ܣ����ڲ�ʵ�־����ת��
������ԭ������������
����ֵ��ָ������ָ��
*************************************/
int* inner_trans(int* matrix, int nrows, int ncols)
{
	int* result = new(nothrow) int[ncols * nrows];
	if (result == NULL)
	{
		cout << "�ڴ����ʧ��" << endl;
		exit(0);
	}
	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			result[j * nrows + i] = matrix[i * ncols + j];
	return result;
}

/************************
���ܣ�ʵ�־����ת�ù���
****************************/
void matritrans()
{
	const char* content = "ת��";
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

		int* matrix = new(nothrow) int[nrows * ncols];
		if (matrix == NULL)
		{
			cout << "�ڴ�ռ����ʧ�ܣ�" << endl;
			return;
		}
		int* result = inner_trans(matrix,nrows,ncols);
		

		cout << "\n�������ת�õľ���: ";
		input_matrix(matrix, nrows, ncols);
		result=inner_trans(matrix, nrows, ncols);
		cout << "ת�ú�ľ���Ϊ" << endl;
		output_matrix(result, ncols, nrows);

		delete []result;
		delete[] matrix;
		matrix = result = NULL;
		int re = return_menu();
		if (re == 0)
			break;
	}
	
}