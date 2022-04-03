#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include<string>
#include "Matrix.h"
using namespace cv;
using namespace std;

/*******************************
*���ܣ�����ʱ��䷽��������ֵ
* ������mat���͵�ͼ��
* ����ֵ����ֵ���Ҷ�ֵ��
********************************/
int OSTU(Mat & image)
{
	int nrows = image.rows;
	int ncols = image.cols;
	int hisgram[256] = { 0, };
	if(image.channels()!=1)
		cvtColor(image, image, CV_BGR2GRAY);

	//�����ֱ��ͼ
	for (int i = 0; i < nrows; i++)
		for (int j = 0; j < ncols; j++)
			hisgram[int(image.at<uchar>(i, j))]++;

	double mg = 0;//ȫ�־�ֵ
	int total_pixel_number = nrows * ncols;
	for (int i = 0; i < 256; i++)
		mg += hisgram[i] * i;
	mg /= total_pixel_number;

	//��ʼ��ȡ��ֵ
	int threshold = 0;
	double maxvar = 0;
	double current_val = 0;
	double accumulated_real_num=0;
	double p1 = 0, p2 = 0;  //�����ֵĸ���
	double m1 = 0, m2 = 0;   //�����ֵľ�ֵ
	int accumulated_pixel_number = 0;
	for (int k = 0; k < 256; k++)  //�Կ��ܵ���ֵ���б���
	{
		accumulated_pixel_number += hisgram[k];
		accumulated_real_num += k * hisgram[k];
		p1 =1.0* accumulated_pixel_number / total_pixel_number;
		p2 = 1.0 - p1;
		m1 = accumulated_real_num / accumulated_pixel_number;
		m2 = 1.0*(mg * total_pixel_number - accumulated_real_num) 
			/ (total_pixel_number - accumulated_pixel_number);

		
		current_val = p1 * p2 * pow(m1 - m2, 2);
	
		if (current_val > maxvar)
		{
			maxvar = current_val;
			threshold = k;
		}
	}
	
	return threshold;
}

/******************************
*���ܣ�չʾOSTU�㷨��ʵ��
******************************/
void OSTU_demo()
{
	const char* content = "OSTU��ֵ��";
	present_title(content);
	
	const char* photos[5] = { "images/demolena.jpg","images/brain.jpg","images/ship.jpg","images/snowball.jpg","images/polyhedrosis.jpg" };
	for (int i = 0; i < 5; i++)
	{
		Mat image = imread(photos[i]);
		imshow("origin", image);
		waitKey();
		int _threshold = OSTU(image);
		if (i == 0)
			threshold(image, image, _threshold, 255, THRESH_BINARY);
		else
			threshold(image, image, _threshold, 255, THRESH_TOZERO);
		imshow("new", image);
		waitKey();
			
	}
	cvDestroyAllWindows();
	wait_for_enter();
	
}