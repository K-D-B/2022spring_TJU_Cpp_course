#include<iostream>
#include<graphics.h>
#include"clock.h"
using namespace std;

/********************************************
* ���ܣ���һ��ֱ�߿����
* ������
        A,B��ֱ�ߵ������˵㣬line_width:�߿�linecolor:ֱ����ɫ��
         params:���������ĺ��ʲ��� ,scale:ģ��������ݵķ�Χ
/**********************************************/
void lineSDF(Point A, Point B, int line_width, COLORREF linecolor, double params[], int scale = 3)
{
    double ratio, d;
    for (int i = min(A.x, B.x) - scale; i < max(A.x, B.x) + scale; i++)
    {
        for (int j = min(A.y, B.y) - scale; j < max(A.y, B.y) + scale; j++)
        {
            Point P = { i,j };
            Point AP = { P.x - A.x,P.y - A.y }, AB = { B.x - A.x,B.y - A.y };
            ratio = (AP.x * AB.x + AP.y * AB.y) * 1.0 / (AB.x * AB.x + AB.y * AB.y);
            if (ratio >= 0 && ratio <= 1)
            {
                d = sqrt(pow(AP.x, 2) + pow(AP.y, 2) - pow(ratio, 2) * (pow(AB.x, 2) + pow(AB.y, 2))) - line_width / 2.0;
                double alpha = params[0] - d / params[1];
                if (d < 0)
                    alpha = 1;
                if (alpha >= 0 && alpha <= 1)
                {
                    COLORREF bg = getpixel(i, j);
                    COLORREF re = mixcolor(bg, linecolor, 1 - alpha + params[2]);
                    putpixel(i, j, re);
                }
            }
        }
    }
}

void SSAA(int SSAA_times = 2)
{
    IMAGE ssaa_img(width * SSAA_times, width * SSAA_times);
    //ssaa_times=2ʱ��ԭͼһ��pixel�²���4��
    SetWorkingImage(&ssaa_img);
    setbkcolor(BACKGROUND_COLOR);
    setlinestyle(PS_SOLID, 18);
    cleardevice();
    setorigin(width * SSAA_times / 2, width * SSAA_times / 2);

    //��������Ӱ
    setlinestyle(PS_NULL, 2);
    setfillcolor(SHADOW_COLOR);
    fillcircle(SHADOW_X * SSAA_times, SHADOW_Y * SSAA_times, SHADOW_RADIUS * SSAA_times);
    setlinecolor(SHADOW_COLOR);
    for (int i = SHADOW_RADIUS * SSAA_times - 64; i <= SHADOW_RADIUS * SSAA_times; i++)
    {
        setlinecolor(mixcolor(SHADOW_COLOR, WHITE, (280.0 * SSAA_times - i) / 64.0));
        circle(SHADOW_X * SSAA_times, SHADOW_Y * SSAA_times, i);
    }
    setlinestyle(PS_SOLID, 18);
   
    //���漸����为�𻭳����Ե
    setlinecolor(0x4EAAC7); //����ɫ
    circle(0, 0, 280 * SSAA_times);
    setlinecolor(0x8FF6FF);//��Ȧ����ɫ
    circle(0, 0, 180 * SSAA_times);
    setlinecolor(0x9EB7CD);//��Ȧ����ɫ
    setlinestyle(PS_SOLID, 1);
    circle(0, 0, 276 * SSAA_times);
    circle(0, 0, 277 * SSAA_times);
    circle(0, 0, 278 * SSAA_times);
    setlinestyle(PS_NULL, 3); 
    setfillcolor(0x9CB7D2); //���ڲ�
    fillcircle(0, 0, 95 * SSAA_times);
    setlinecolor(BLACK);
    circle(0, 0, 95 * SSAA_times);
    setlinecolor(0x9EFAFB);
    circle(0, 0, 96 * SSAA_times);
    SetWorkingImage(NULL);
    int colorr = 0, colorg = 0, colorb = 0;
    COLORREF re;

    //���¶���ѭ����SSAA_IMG(����Ĭ�ϲ���Ϊ2���е�4������ȡ��ֵ���ص�ԭʼ����
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < width; j++)
        {
            SetWorkingImage(&ssaa_img);
            colorr = 0;
            colorg = 0;
            colorb = 0;
            for (int k = 0; k < SSAA_times; k++)
                for (int m = 0; m < SSAA_times; m++)
                {
                    colorr += GetRValue(getpixel(-width / 2 * SSAA_times + i * SSAA_times + k, -width / 2 * SSAA_times + j * SSAA_times + m));
                    colorg += GetGValue(getpixel(-width / 2 * SSAA_times + i * SSAA_times + k, -width / 2 * SSAA_times + j * SSAA_times + m));
                    colorb += GetBValue(getpixel(-width / 2 * SSAA_times + i * SSAA_times + k, -width / 2 * SSAA_times + j * SSAA_times + m));
                }
            colorr /= (SSAA_times * SSAA_times);
            colorg /= (SSAA_times * SSAA_times);
            colorb /= (SSAA_times * SSAA_times);
            re = RGB(colorr, colorg, colorb);
            SetWorkingImage(NULL);
            putpixel(i, j, re);
        }
    }
}