#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Matrix.h"
using namespace cv;
using namespace std;


/****************************************
*���ܣ��������ӷ��͹�����˻�
*�������û������choice�������������ֲ���
*��Ϊ�����ֲ�������Ҫ��������ͬ�;��󣬶��������ʽ��ͬ������entry-wise�Ĳ���
���Խ�������ͬһ��������ʵ��
**********************************************/
void matriplus_and_hadamulti(const char choice)
{
    const char* content = NULL;
    content = (choice == '1' ? "�ӷ�" : "������˻�");
    while (true)
    {
        present_title(content);
        int nrows=0, ncols=0;
        nrows = input_size(0);
        if (nrows == 0)
            break;
        ncols = input_size(1);
        if (ncols == 0)
            break;

        int* matrix1 = new(nothrow) int[nrows * ncols];
        if (matrix1 == NULL)
        {
            cout << "�ڴ����ʧ��" << endl;
            return;
        }
        int* matrix2 = new(nothrow) int[nrows * ncols];
        if (matrix2 == NULL)
        {
            cout << "�ڴ����ʧ��" << endl;
            return;
        }
        int* result = NULL;

        cout << "\n�������һ��������" << content << "����ľ��� : ";
        input_matrix(matrix1, nrows, ncols);
        cout << "\n������ڶ���������" << content << "����ľ��� : ";
        input_matrix(matrix2, nrows, ncols);

        if (choice == '1')
            result = inner_plus(matrix1, matrix2, nrows, ncols);
        else
            result = inner_hadamulti(matrix1,matrix2, nrows, ncols);

        output_plus_hadam(matrix1, matrix2, result, nrows, ncols,choice);

        delete[] matrix1;
        delete[] matrix2;
        delete[] result;
        matrix1 = matrix2 = result = NULL;
        int re = return_menu();
        if (re == 0)
            break;
    }
}


/****************************************
*���ܣ�ʵ�ֶԾ���ӷ������������˻������
*������������������ľ���matrix1,matrix2,������result,����ͬ�;�����У����Լ� 
���ֶ��ߵĲ���choice
****************************************/
void output_plus_hadam(int* matrix1, int* matrix2, int* result, int nrows, int ncols, const char choice)
{
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "��" << setw(4 * ncols + 2) << "��";
        cout << "     ";
    }
    cout << endl;
    for (int i = 0; i < nrows; i++)
    {
        cout << "��";
        for (int j = 0; j < ncols; j++)
            cout << setw(4) << matrix1[ncols * i + j];
        cout << "��" ;

        if (i == nrows / 2)
            if (choice == '1')
                cout << setw(3) << "+" << "  ";
            else
                cout << setw(3) << "��" << "  ";
        else
            cout << "     ";

        cout << "��";
        for (int j = 0; j < ncols; j++)
            cout << setw(4) << matrix2[ncols * i + j];
        cout << "��" ;

        if (i == nrows / 2)
            cout << setw(3) << "=" << "  ";
        else
            cout << setw(5) << ' ';

        cout << "��";
        for (int j = 0; j < ncols; j++)
            cout << setw(4) << result[ncols * i + j];
        cout << "��" << endl;;
    }
    for (int i = 0; i < 3; i++)
    {
        cout << "��" << setw(4 * ncols + 2) << "��";
        cout << "     ";
    }
    cout << endl;
}

int main()
{
    while (true) // ע���ѭ���˳�������
    {
        system("cls"); // ��������
        char choice=present_menu(); // ���ò˵���ʾ���������в������
        // ��Ҫ������˵�ѡ����choice
        if (choice == '0') // ѡ���˳�
        {
            char ch;
            cout << "\nȷ���˳���?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                break;
            else
                continue;
        }

        switch (choice)
        {
            // ���������������������Ʋ���ɣ����������������������͵ȣ�����ѡ��ӷ�������в���
            case '1':
                matriplus_and_hadamulti(choice);
                break;
            case '2':
                nummulti();
                break;
            case '3':
                matritrans();
                break;
            case '4':
                matrimulti();
                break;
            case '5':
                matriplus_and_hadamulti(choice);
                break;
            case '6':
                conv();
                break;
            case '7':
                conv_application();
                break;
            case '8':
                OSTU_demo();
                cout << "����˵�8" << endl;
                break;
            default:
                cout << "\n�����������������" << endl;
                wait_for_enter();
        }
    }
    return 0;
}