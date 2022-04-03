#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<graphics.h>
#include"clock.h"

/**************************
* ����������ʱ�����ֵĺ���
/**************************/
void output_font()
{
    LOGFONT fontpro;
    fontpro.lfHeight = 70;                         //��
    fontpro.lfWidth = 25;                          //��
    fontpro.lfQuality = ANTIALIASED_QUALITY;       //�����
    fontpro.lfWeight = 3;                          //��ϸ
    fontpro.lfStrikeOut = false;                   //ɾ���߲�Ҫ
    fontpro.lfUnderline = false;                   //�»��߲�Ҫ
    fontpro.lfItalic = false;                      //б�岻Ҫ
    fontpro.lfOrientation = 0;
    fontpro.lfEscapement = 0;                      //�ȿ�����
    fontpro.lfCharSet = ANSI_CHARSET;               //ANSI�ַ���
    fontpro.lfPitchAndFamily = 0;
    _tcscpy(fontpro.lfFaceName, _T("Century"));     //����
    settextcolor(BLACK);                             //��ɫ
    settextstyle(&fontpro);
    RECT r = { -40,-254, 40,-190 };                //һ�����ο򣬹涨һ�����ֵĴ�С
    WCHAR s[3];                                     //����ַ����������������ת��Ϊ�ַ����Ľ��
    Point base;                 //base���������ÿ������ʱ�Ļ�׼λ�ã��������ο�����Ϊ��������

    const int fontlength = 222;  //д���ֵľ��ο�Բ�ĵİ뾶
    for (int i = 1; i <= 12; i++)
    {
        base.x = int(fontlength * sin(PI / 6 * i));
        base.y = int(-fontlength * cos(PI / 6 * i));
        r = { base.x - 40,base.y - 32,base.x + 40,base.y + 32 };
        int_to_wchar(i, s);
        drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

}

/*********************
����12��ʱ��̶��ߵĺ���
*************************/
void setticks()
{
    double params[3] = { 0.5, 3.0, 0 };
    const int shorter_scale = 1;
    setlinecolor(BLACK);
    for (int i = 1; i <= 60; i++)
    {
        if (i % 5 == 0)
        {
            Point A = { int(tickr * sin(PI / 30 * i)), int(-tickr * cos(PI / 30 * i)) };
            Point B = { int(tickR * sin(PI / 30 * i)), int(-tickR * cos(PI / 30 * i)) };
            setlinestyle(BS_SOLID, 4);
            line(int(tickr * sin(PI / 30 * i)), int(-tickr * cos(PI / 30 * i)),
                int(tickR * sin(PI / 30 * i)), int(-tickR * cos(PI / 30 * i)));
            lineSDF(A, B, 4, BLACK, params, 3);
        }
        else
        {
            Point A = { int((tickr + 1) * sin(PI / 30 * i)), int(-(1 + tickr) * cos(PI / 30 * i)) };
            Point B = { int((tickR - 2) * sin(PI / 30 * i)), int(-(-2 + tickR) * cos(PI / 30 * i)) };
            setlinestyle(BS_SOLID, 1);
            line(int((tickr + 1) * sin(PI / 30 * i)), int(-(tickr + 1) * cos(PI / 30 * i)),
                int((tickR - 2) * sin(PI / 30 * i)), int(-(tickR - 2) * cos(PI / 30 * i)));
            lineSDF(A, B, 1, ticks_SDF_color, params, 3);
        }
    }
}