#include<iostream>
#include<graphics.h>
#include"clock.h"


void draw_koch_curve(Point& position)
{
	double R = SNOW_SIZE;
	int w = 60;    
	int cnums = 3;    //��ǰͼ���ж�������
	if (position.y > 310)
		position.y = rand() % 10 - 310;  //��ѩ������y�����������Ϊ��ʹ�䲻������
	
	Node *line_set=new Node[300];  //���滭˳����ÿ���ߣ�����3���Ȼ����������
	if (line_set == NULL)  // û����ɹ��ͷ���
		return;
	line_set[0].x1 = double(position.x); line_set[0].y1 = double((++position.y)); 
	line_set[0].x2 = double(position.x)-R/2; line_set[0].y2 = double((position.y)) + R / 2 * sqrt(3.0);
	line_set[1].x1 = double(position.x) - R/2; line_set[1].y1 = double((position.y)) + R / 2 * sqrt(3.0);
	line_set[1].x2 = double(position.x)+R/2; line_set[1].y2 = double((position.y)) + R / 2 * sqrt(3.0);
	line_set[2].x1 = double(position.x) + R/2; line_set[2].y1 = double((position.y)) + R / 2 * sqrt(3.0); 
	line_set[2].x2 = double(position.x); line_set[2].y2 = double((position.y));
	
	for (int t = 0; t <3; t++)//��3�η���  
	{
		R = R / 3.0;//�·��γ������������α߳�

		//ÿһ�η��ͣ�һ���߿��ѳ�3����j�������д������ӵ��±�
		int j = cnums;
		for (int i = 0; i < cnums; i++)  //�������ѭ���������codebus
		{
			// ��ȡ�߶η���
			double k = atan((line_set[i].y2 - line_set[i].y1) / (line_set[i].x2 - line_set[i].x1)) * 180 /PI;
			if ((line_set[i].x2 - line_set[i].x1) < 0)k += 180;

			// ��һ��������
			line_set[i].x2 = line_set[i].x1 + cos(double(k) / 180.0 * PI) * R;
			line_set[i].y2 = line_set[i].y1 + sin(double(k) / 180.0 * PI) * R;

			k += w;
			line_set[j].x1 = line_set[i].x2;
			line_set[j].y1 = line_set[i].y2;
			line_set[j].x2 = line_set[j].x1 + cos(double(k) / 180.0 * PI) * R;
			line_set[j].y2 = line_set[j].y1 + sin(double(k) / 180.0 * PI) * R;

			k -= 2.0 * w;
			line_set[j + 1].x1 = line_set[j].x2;
			line_set[j + 1].y1 = line_set[j].y2;
			line_set[j + 1].x2 = line_set[j + 1].x1 + cos(double(k) / 180.0 * PI) * R;
			line_set[j + 1].y2 = line_set[j + 1].y1 + sin(double(k) / 180.0 * PI) * R;

			k += w;
			line_set[j + 2].x1 = line_set[j + 1].x2;
			line_set[j + 2].y1 = line_set[j + 1].y2;
			line_set[j + 2].x2 = line_set[j + 2].x1 + cos(double(k) / 180.0 * PI) * R;
			line_set[j + 2].y2 = line_set[j + 2].y1 + sin(double(k) / 180.0 * PI) * R;

			j += 3;
		}
		cnums = j;
	}
	setfillcolor(WHITE);
	setlinestyle(BS_SOLID, 1);
	setlinecolor(WHITE);
	for (int i = 0; i < cnums; i++)
		line(int(line_set[i].x1),int(line_set[i].y1), 
			int(line_set[i].x2), int(line_set[i].y2));
	
	floodfill(position.x,(position.y) +10,WHITE);  //���ѩ��
	delete[]line_set;
	line_set = NULL;
}