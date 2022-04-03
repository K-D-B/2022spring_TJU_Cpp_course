#include<iostream>
#include<iomanip>
#include<cmath>
#include"Matrix.h"
using namespace std;

/**********************************
* ���ܣ����ڲ�ʵ�־�����
* ���������������matrix�������conv_kernel,����������������
*		is_normalize:�Ƿ���Ҫ���Ծ���˵ĺ�
**********************************/
int* inner_conv(int* matrix, int* conv_kernel, int nrows, int ncols,bool is_normalize)
{
	int kernel_sum = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			kernel_sum += conv_kernel[i * 3 + j];
	int* result = new(nothrow) int[nrows * ncols];
	if (result == NULL)
	{ 
		cout << "�ڴ����ʧ�ܣ�" << endl;
		exit(0);
	}
		
	int val = 0;
	memset(result, 0, sizeof(int)*nrows * ncols);
	for(int i=1;i<=nrows;i++)
		for (int j = 1; j <= ncols; j++)
		{
			val = 0;
			for (int k = -1; k <= 1; k++)
				for (int m = -1; m <= 1; m++)
				{
					val += matrix[(i + k) * (ncols + 2) + j + m] * conv_kernel[(k+1) * 3 + m+1];
					//cout << "����matrix " << matrix[(i + k) * (ncols + 2) + j + m] << ' ' ;
					//cout << "����kernel " << conv_kernel[(i + k) * 3 + j + m] << ' ' << endl;
				}
			if(is_normalize==false)
				result[(i - 1)*ncols+j - 1] = val;
			else
			{
				if (kernel_sum != 0)
					val /= kernel_sum;
				if (val > 255)
					val = 255;
				else if (val < 0)
					val = 0;
				result[(i - 1) * ncols + j - 1] = val;
			}
		}
	return result;
}

/**********************************
���ܣ�ʵ�־������Ĺ���
**********************************/
void conv()
{
	const char* content = "���";
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

		int* matrix = new(nothrow) int[(nrows+2) * (ncols+2)];
		if (matrix == NULL)
		{
			cout << "�ڴ����ʧ��" << endl;
			return;
		}
		memset(matrix, 0, sizeof(int) * ((nrows + 2) * (ncols + 2)));
		int conv_kernel[9];

		cout << "�����������ľ���: " << endl;
		input_matrix(matrix, nrows, ncols,true);
		cout << "trial" << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
				cout << matrix[i * 5 + j]<<' ';
			cout << endl;
		}
		cout << "����������: " << endl;
		input_matrix(conv_kernel, 3, 3);
		output_matrix(conv_kernel, 3,3);

		int* result = inner_conv(matrix, conv_kernel, nrows, ncols);
		cout << "�����ľ���Ϊ" << endl;
		output_matrix(result, nrows, ncols);
		delete []result;
		delete []matrix;
		matrix = result = NULL;
		int re = return_menu();
		if (re == 0)
			break;
	}
}