#include <conio.h>
#include <iostream>
#include<iomanip>
#include "Matrix.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/***********************************
���ܣ�ʵ��һ����������
������matrix:ָ��һ�������ָ��
      nrows:����
	  ncols:����
**********************************/
void output_matrix(int* matrix, int nrows, int ncols)
{
	cout << "\n��" << setw(4 * ncols+2) << "��";
	cout << endl;
	for (int i = 0; i < nrows; i++)
	{
		cout << "��";
		for (int j = 0; j < ncols; j++)
			cout << setw(4) << matrix[ncols * i + j];
		cout << "��" << endl;
	}		
	cout << "��" << setw(4 * ncols+2) << "��";
}


/*************************
���ܣ����ڲ�ʵ�־���ӷ�
����:matrix1,2:ָ������ͬ�;����ֱ��
     nrows:����
	 ncols:����
����ֵ��ָ������ָ��
*****************************/
int* inner_plus(int* matrix1, int* matrix2, int nrows, int ncols)
{
	int* sum = new(nothrow) int[nrows * ncols];
	if (sum == NULL)
	{
		cout << "�ڴ����ʧ��" << endl;
		exit(0);
	}
	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			sum[i * ncols + j] = matrix1[i * ncols + j] + matrix2[i * ncols + j];
	return sum;
}