#include<iostream>
#include<graphics.h>
#include"clock.h"

/********************************************
* ���ܣ���centerΪ���ĵ������Σ��߳�Ϊ2*size)�����˽��о��������
* ����:
    kernel�������
    origin:ָ��ԭͼ��ָ��
/***********************************************/
void conv(Point center, const double kernel[3][3], int size, IMAGE* origin)
{
    IMAGE* buffer = new IMAGE(size, size);  //�����ݴ�������Ļ���
    getimage(buffer, center.x - size, center.y - size, 2 * size, 2 * size);
    SetWorkingImage(origin);

    double colorr = 0, colorg = 0, colorb = 0;
    COLORREF re;

    //������һ������ѭ�������������ǶԾ�����ģ�����center!)��ѭ��
    //���������Ƕ�3*3�����ѭ��
    for (int i = center.x + 1 - size; i < center.x + size - 1; i++)
        //���ھ����������С��Ե�ʣ������趨һ�·�Χ
        for (int j = center.y + 1 - size; j < center.y + size - 1; j++)
        {
            SetWorkingImage(origin);
            colorr = 0, colorg = 0, colorb = 0;

            //���������ѭ��������һ��3*3���򣬵õ�һ����ɫ�����ǰ�������buffer���棬�������ͼ�ķ�ʽ�������ģ���õ�buffer
            for (int k = -1; k <= +1; k++)
                for (int m = -1; m <= 1; m++)
                {
                    colorr += double(GetRValue(getpixel(i + k, m + j))) * kernel[1 + k][1 + m];
                    colorg += double(GetGValue(getpixel(i + k, m + j))) * kernel[1 + k][1 + m];
                    colorb += double(GetBValue(getpixel(i + k, m + j))) * kernel[1 + k][1 + m];
                }
            re = RGB(int(colorr), int(colorg), int(colorb));
            SetWorkingImage(buffer);            //bufferֻ����Ҫ�����һС�飬ǧ��ע�������ϵ
            putpixel(i - (center.x - size), j - (center.y - size), re);
        }
    SetWorkingImage(origin);
    putimage(center.x - size, center.y - size, buffer);
    delete buffer;
}

/****************************************
* ���ܣ���ͼ�����½���Ӱ����˹ģ��
* ���� :ssaa_img:SSAA�㷨�еĸ����ͼ��
*       ssaa_times���Ŵ���
* **************************************/
void Guassian_blur(IMAGE* SSAA_img, int SSAA_times)
{
    const double conv_kernel[3][3] = { 0.0947416,0.118318,0.0947416,
                                       0.118318,0.147761,0.118318,
                                        0.0947416,0.118318,0.0947416 };   //3*3�ľ����

    SetWorkingImage(SSAA_img);             //��������������ΪSSAA_img
    Point workingpoint;
    for (int i = 0; i < 81; i++)
    {
        //����ÿ��תһ��С�Ƕȣ�����ӰԲ�ϵ�һ���㣨workingpoint)Ϊ���ģ�����һ�������������
        workingpoint = { 30 * SSAA_times + int(280 * SSAA_times * sin(4 * PI / 15 + i * PI / 90))
                    ,25 * SSAA_times + int(-280 * SSAA_times * cos(4 * PI / 15 + i * PI / 90)) };
        //��ʼ���
        if (i < 9 || i>72)
            conv(workingpoint, conv_kernel, 7, SSAA_img);
        else
            conv(workingpoint, conv_kernel, 15, SSAA_img);
    }
}