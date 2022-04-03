#include <conio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include<string>
#include "Matrix.h"
using namespace cv;
using namespace std;

/******************************
* ���ܣ�ʵ�־�������Ӧ�ã�lena)
***********************************/
void conv_application()
{
    Mat image =
         imread("images/demolena.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    imshow("Image-original", image);
    waitKey();

    cvtColor(image, image, CV_BGR2GRAY);  //ת��Ϊ�Ҷ�
   
    int nrows = image.rows;
    int ncols = image.cols;
    
    int* matrix = new(nothrow) int[(nrows+2) * (ncols+2)];
    if (matrix == NULL)
    {
        cout << "�ڴ����ʧ��" << endl;
        return;
    }
    memset(matrix, 0, sizeof(int) * (nrows + 2) * (ncols + 2));
    for (int i = 1; i <= nrows; i++)
    {
        for (int j = 1; j <= ncols; j++)
            matrix[i * (ncols+2) + j] = image.at<uchar>(i-1, j-1);
        cout << endl;
    }
    int conv_kernels[6][9] =
    {
        {1,1,1,1,1,1,1,1,1,},{-1,-2,-1,0,0,0,1,2,1},{-1,0,1,-2,0,2,-1,0,1}
        ,{-1,-1,-1,-1,9,-1,-1,-1,-1},{-1,-1,0,-1,0,1,0,1,1,},{1,2,1,2,4,2,1,2,1} 
    };
    int* buffer = NULL;

    const char* titles[6] = { "�����B1","�����B2" ,"�����B3" ,"�����B4" ,"�����B5" ,"�����B6" };
    Mat dealed_image(nrows, ncols, CV_8UC1);
    for (int k = 0; k<6; k++)
    {
        Mat dealed_image(nrows, ncols, CV_8UC1);
        buffer = inner_conv(matrix, conv_kernels[k], nrows, ncols, true);
        for (int i = 0; i < nrows; i++)
            for (int j = 0; j < ncols; j++)
                dealed_image.at<uchar>(i, j) = buffer[i * ncols + j];
        imshow(titles[k], dealed_image);
        waitKey();

    }
    delete[]matrix;
    delete[] buffer;
    matrix = buffer = NULL;
    
    wait_for_enter();
}