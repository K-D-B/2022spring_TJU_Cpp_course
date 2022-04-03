#pragma once
/****************���γ�����������**************/
#define width 640  //������ȣ����ȣ�
#define SNOW_N 40   //�ж���ѩ��
#define PI 3.1415926535897  //Բ����
#define tickR 265  //�����Ͽ̶ȵĳ�ֱ��
#define tickr 255   //�����Ͽ̶ȵĶ�ֱ��
#define SNOW_SIZE 30  //ѩ����С
#define SECOND_HAND_LENGTH 190  //���볤��
#define MINUTE_HAND_LENGTH 140   //���볤��
#define HOUR_HAND_LENGTH   100    //ʱ�볤��
#define SHADOW_RADIUS      280 //��ӰԲ�εİ뾶
#define SHADOW_X      30           //��ӰԲ��Բ�ĺ�����
#define SHADOW_Y      25             //��ӰԲ��Բ��������
#define BALL_RADIUS   12  //����С��İ뾶
/*******************************/


/************��ɫ�궨������*********/
#define COLOR_INNER_ROUND 0x9CB7D2
//��Ȧ������Ȧ���ڶ��н��䣬ÿȦ��3����ɫ,�������ⶨ��3����ɫ
#define COLOR_OUTER_ROUND1 0x88D7BB
#define COLOR_OUTER_ROUND2 0x89B9E3
#define COLOR_OUTER_ROUND3 0x819CB7
#define COLOR_MID_ROUND1 0x9EFAFB
#define COLOR_MID_ROUND2 0x88D2FC
#define COLOR_MID_ROUND3 0x8CCBFD
#define ticks_SDF_color 0x4D4D4D  //��ǳɫ�̶���SDFʱ�õ����ߵ���ɫ
#define BACKGROUND_COLOR 0XCCFF66  //��������ɫ
#define SHADOW_COLOR 0x87868B     //��Ӱ��ɫ
#define BALL_OUTER_COLOR  0x8BECFF   //����С������Ե��ɫ
#define BALL_INNER_COLOR  0xFFFFFF //����С���������ɫ
/***********************/



/***********�ṹ�嶨������**************/
struct Node //һ��node����ƺ�ѩ�����������ε�һ����
{
    double x1, y1;				
    double x2, y2;				
    double R;							// ����
};
struct Point   //��ṹ�壬��������
{
    int x;
    int y;
};
/*******************************/


/***************������������*********************/
//����������ʱ�����ֵĺ���
void output_font();

void setticks();//����12��ʱ��̶���

void draw_koch_curve(Point& position);//�����ƺ�ѩ��

//��������ɫ��ϣ����ڻ�������ɫ
COLORREF mixcolor(COLORREF color1, COLORREF color2, double ratio);  

//���ֱ�߽���SDF�㷨�����
void lineSDF(Point A, Point B, int line_width, COLORREF linecolor, double params[], int scale );

//���ڱ���Բ��ͨ��SSAA�����
void SSAA(int SSAA_times);

//��SSAA_img�е�һ��С��������ģ�������أ���Guassian_blur��������
void conv(Point center, const double kernel[3][3], int size, IMAGE* origin);

//���������½ǵ���Ӱ��Ե����˹ģ��
void Guassian_blur(IMAGE* SSAA_img, int SSAA_times);

//������ת��Ϊwchar�͵Ĵ�
void int_to_wchar(int n, WCHAR* s);

//�����û�������
int get_choice();

//ʵʱ���Ƴ�ָ���ѩ��
void pointer(Point* SNOW);

//�Ի�������һ���̶ȵĳ�ʼ��
void init(int n);
/***************************************************/
