#pragma once
#ifndef __GLUTTONOUS_SNAKE__  //����ʽ����
#define __GLUTTONOUS_SNAKE__


//�����ȼ���ģʽ
#define ENTRY_MODE 0
#define JUNIOR_MODE 1
#define SENIOR_MODE 2

//��Ļ����
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
//�ߵ�״̬
#define DEAD 0
#define ALIVE 1

#define EXIT -1

//��ͼ�ϸ��ֱ�ǵ�����
#define SNAKE_BODY 1
#define SNAKE_HEAD 3
#define OBSTACLE 2
#define FOOD_BURGER 4
#define FOOD_CHICKEN 5
#define FOOD_FRUIT 6
#define FOOD_NUM 10

//��ͼ�ĳ���
#define MAP_WIDTH 45
#define MAP_HEIGHT 40

//�ĸ�����
#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3

#define ROUND_ANGLE 20  //Բ�Ǿ��εĻ��ȽǶ�
#define BUTTON_CLICK 1  //��ť�����
#define NO_BUTTON_CLICK 0 //��ťδ�����

#include<fstream>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<iostream>
#include<ctime>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


//4��class
class Snake;
class Food;
class Obstable;
class Game_Controller;

//����ṹ��
struct coordinate
{
	int x;
	int y;
};

//�ߵ�һ�Σ�һ�����ӣ�
struct segment
{
	int x=0; int y=0; 
	segment* next=NULL;
	segment* former = NULL;
};


//�ߵ���
class Snake
{
private:
	int length = 0; //����
	segment* body = NULL; //��������
	int state = DEAD;
	segment* head=NULL;  //��ͷָ��
	segment* tail=NULL;  //��βָ��
	int current_direction = WEST;  //��ǰ�н�����
	friend Game_Controller;

public:
	void init();  //��ʼ��
	bool is_dead();  //�ж��Ƿ�����
	void append_head();  //������ͷ
	void delete_tail();   //ɾȥ��β��
	void change_direction(const int new_direction); //���ķ���
	void adjust_length();  //��������
	void destroy();   //�ݻ���
	~Snake();
};


//ǽ��
class Obstacle
{
private:
	friend  Game_Controller;

public:

	void init(); //��ʼ��
	void append();  //�������

};

//ʳ����
class Food
{
private:
	int num_burger = 0;  //��������
	int num_chicken = 0;  //ը������
	int num_fruit = 0;  //ʳ������
	friend Game_Controller;
public:
	int get_num_burger() const
	{
		return num_burger;
	}
	int get_num_chicken() const
	{
		return num_chicken;
	}
	int get_num_fruit() const
	{
		return num_fruit;
	}
	void init(const int mode);  //��ʼ��ʳ��

	void append();  //����������չΪʳ��
};

//��Ϸ��������
class Game_Controller 
{
private:
	int mode=-1;  //��ǰ����ôģʽ
	int hp=-1;   //��ǰ����ֵ
	UINT best_score=0;  //��ǰ��ߵ÷�
	UINT score = 0;   //��ǰ�÷�
	char *username = NULL;  //��ǰ�û���

public:
	Game_Controller();
	void portray_firstpage()const;  //����ҳ// ��Ƕһ�������Ĺ��ܣ�����ѡ���������Ϸ/��ʷ��Ϸ
	void portray_rulespage()const;  //��ʾ����ҳֱ���û������˳�
	void portray_exitpage()const;    //���˳�ҳ��
	void portray_toolspage(const int option=2) const;  //�����а�/��ʷ��¼ҳ��

	int get_option();      
	void enter_game();  //����һ����Ϸ
	int get_mode();      //��ȡ��Ϸģʽ
	void set_mode(const int m);   //������Ϸģʽ
	void set_score(const int s);  //���õ÷�
	void set_hp(const int h);   //��������ֵ

	void init_settings();    //��ʼ����ͼ
	void portray_gamepage(Snake& snake,Obstacle&,Food & food);   //����Ϸҳ��
	void single_round(Snake& snake, Obstacle&, Food& food);  //������Ϸ�߼�
	void update_scoreboard(const Food& food);             //ʵʱ�޸ļƷְ�UI
	void update_record(const int option=2) const;        //�����ļ�

	void set_username();   //�����û�����
	~Game_Controller();
};

//����ת���ַ���
void  int2str(const int n, wchar_t* s);

//��ȡ������¼�
bool get_button_click(const int x, const int y, const int width, const int height, const COLORREF former_color, const COLORREF latter_color, ExMessage& m, const wchar_t* message,const bool mode=0,COLORREF textcolor=WHITE);
#endif // !__GLUTTONOUS_SNAKE__

