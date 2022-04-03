#include<iostream>
#include<graphics.h>
#include"clock.h"
using namespace std;

/************************************
* ���ܣ�������ת��Ϊ���ַ��͵��ַ���
* **************************************/
void int_to_wchar(int n, WCHAR* s)
{
    if (n < 10)
    {
        s[0] = WCHAR(n + '0');
        s[1] = '\0';
    }
    else
    {
        s[0] = WCHAR(n / 10 + '0');
        s[1] = WCHAR(n % 10 + '0');
        s[2] = '\0';

    }
}

/********************************************
* ��color1��color2�� ratio��1-ratio��Ȩ�ػ��
* ************************************************/
COLORREF mixcolor(COLORREF color1, COLORREF color2, double ratio)
{
    COLORREF  re;
    BYTE Bcolor = int(GetBValue(color1) * ratio + GetBValue(color2) * (1 - ratio));
    BYTE Rcolor = int(GetRValue(color1) * ratio + GetRValue(color2) * (1 - ratio));
    BYTE Gcolor = int(GetGValue(color1) * ratio + GetGValue(color2) * (1 - ratio));
    re = RGB(Rcolor, Gcolor, Bcolor);
    return re;
}

/*****************************************
�����û�������ѡ��
******************************************/
int get_choice()
{
    cout << "  SSAA������Լ�ģ����������Ҫ�ϳ�ʱ��(Լ45s)" << endl;
    cout << "  ��ˣ��ҽ�����õı�����Ϊ��test.png�Ա�����ٵ���ʾ" << endl;
    cout << "  ��1ֱ�Ӽ��ر���õ�ͼ���Կ��ٿ�ʼ����0��ʾSSAA��ģ��������" << endl;
    
    int n;
    while (true)
    {
        cout << "������: ";
        cin >> n;
        if (cin.good() == 0 || (n != 0 && n != 1))
        {
            cout << "�������" << endl;
            cin.clear();
            cin.ignore(65535, '\n');
        }
        else
            break;
    }
    return n;
}