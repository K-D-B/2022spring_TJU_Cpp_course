#define _CRT_SECURE_NO_WARNINGS
#include"Gluttonous_Snake.h"
#include<graphics.h>
#include<conio.h>
unsigned char** map = NULL;

//���캯��
Game_Controller::Game_Controller()
{
	map = new(std::nothrow) unsigned char* [MAP_WIDTH + 1];  //��1����Ϊ���봦�������±�任
	if (map == NULL)
		exit(EXIT_FAILURE);
	for (int i = 0; i <= MAP_WIDTH; i++)
	{
		map[i] = new(std::nothrow) unsigned char[MAP_HEIGHT + 1];
		if (map[i] == NULL)
			exit(EXIT_FAILURE);
	}

	username = new char[10];
	strcpy(username, "moondok");
	std::fstream ranks_file;
	ranks_file.open("ranks.log", std::ios::in | std::ios::out | std::ios::_Nocreate);
	if (ranks_file.is_open() == 0)
	{
		best_score = 0;
		ranks_file.open("ranks.log", std::ios::out);
		for (int i = 0; i < 3; i++)//����ģʽ�����а�
		{
			ranks_file << 0 << '\n';
			for (int i = 0; i < 3; i++) //ȡǰ����
				ranks_file << "                                                  " << '\n';
		}
		ranks_file.close();
	}

	std::fstream records_file;
	records_file.open("records.log", std::ios::in | std::ios::out | std::ios::_Nocreate);
	if (records_file.is_open() == 0)
	{
		records_file.open("records.log", std::ios::out);
		for (int i = 0; i < 3; i++)//����ģʽ�ļ�¼
		{
			records_file << 0 << '\n';
			for (int i = 0; i < 3; i++) //ȡ�������
				records_file << "                                                  " << '\n';
		}
		records_file.close();
	}

}

//������ҳ
void Game_Controller::portray_firstpage()const
{
	initgraph(SCREEN_WIDTH,SCREEN_HEIGHT);
	setbkmode(OPAQUE);

	loadimage(NULL, _T("image/bg.png"));
	
	setorigin(600,400); //����ԭ��

	setbkmode(TRANSPARENT);

	LOGFONT font_config;
	font_config.lfHeight = 35;

	font_config.lfWidth = 15;
	font_config.lfWeight = 400;
	font_config.lfItalic = false;
	font_config.lfUnderline = false;
	font_config.lfCharSet = ANSI_CHARSET;
	font_config.lfStrikeOut = false;
	font_config.lfQuality = ANTIALIASED_QUALITY;
	font_config.lfEscapement = 0;
	font_config.lfOrientation = 0;
	font_config.lfPitchAndFamily =2 ;

	settextstyle(&font_config);

	setfillcolor(BROWN); //����Ϸ
	solidroundrect(-100, -20, 100, 30, 20, 20);
	const wchar_t s1[] = L"����Ϸ";
	settextcolor(WHITE);
	outtextxy(-50, -15, s1);

	solidroundrect(-100, 60, 100, 110, 20, 20);
	const wchar_t s2[] = L"��ʷ��Ϸ";
	outtextxy(-67, 65, s2);

	solidroundrect(-100, 140, 100, 190, 20, 20);
	const wchar_t s3[] = L"���а�";
	outtextxy(-50, 145, s3);

	solidroundrect(-100, 220, 100, 270, 20, 20);//�˳�
	const wchar_t s4[] = L"�˳���Ϸ";
	outtextxy(-67, 225, s4);
}

//��ȡ��Ҵ���ҳͨ���������ȡ����Ϣ���������а�����Ϸ����ʷ��¼���˳���Ϸ����
int Game_Controller::get_option()
{
	ExMessage m;
	const wchar_t s1[] = L"����Ϸ";
	const wchar_t s2[] = L"��ʷ��Ϸ";
	const wchar_t s3[] = L"���а�";
	const wchar_t s4[] = L"�˳���Ϸ";
	int option = -1;
	while (1)
	{
		getmessage(&m, EM_MOUSE);//��������ֻ��Ҫ����¼�
		if (m.x > -100 + 600 && m.x<100 + 600 && m.y>-20 + 400 && m.y < 30 + 400)
		{
			setfillcolor(0x25c1ff);
			solidroundrect(-100, -20, 100, 30, 20, 20);
			settextcolor(WHITE);
			outtextxy(-50, -15, s1);
			while (m.x > -100 + 600 && m.x<100 + 600 && m.y>-20 + 400 && m.y < 30 + 400)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN)
					return (option = 0);
				if (!(m.x > -100 + 600 && m.x<100 + 600 && m.y>-20 + 400 && m.y < 30 + 400))
				{
					setfillcolor(BROWN); 
					solidroundrect(-100, -20, 100, 30, 20, 20);
					outtextxy(-50, -15, s1);
					break;
				}
			}
		}
		else if (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>60 + SCREEN_HEIGHT / 2 && m.y < 110 + SCREEN_HEIGHT / 2)
		{
			setfillcolor(0x25c1ff);
			solidroundrect(-100, 60, 100, 110, 20, 20);
			outtextxy(-67, 65, s2);
			while (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>60 + SCREEN_HEIGHT / 2 && m.y < 110 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == (WM_LBUTTONDOWN))
					return (option = 1);
				if (!(m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>60 + SCREEN_HEIGHT / 2 && m.y < 110 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(BROWN); //����Ϸ
					solidroundrect(-100, 60, 100, 110, 20, 20);
					outtextxy(-67, 65, s1);
					break;
				}
					
			}
			setfillcolor(BROWN);
			solidroundrect(-100, 60, 100, 110, 20, 20);
			outtextxy(-67, 65, s2);
		}
		else if (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>140 + SCREEN_HEIGHT / 2 && m.y < 190 + SCREEN_HEIGHT / 2)
		{
			setfillcolor(0x25c1ff);
			solidroundrect(-100, 140, 100, 190, 20, 20);
			outtextxy(-50, 145, s3);
			while (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>140 + SCREEN_HEIGHT / 2 && m.y < 190 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == (WM_LBUTTONDOWN))
					return (option = 2);
				if (!(m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>140 + SCREEN_HEIGHT / 2 && m.y < 190 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(BROWN); //����Ϸ
					solidroundrect(-100, 140, 100, 190, 20, 20);
					outtextxy(-50,145, s3);
					break;
				}
			}
			setfillcolor(BROWN);
			solidroundrect(-100, 140, 100, 190, 20, 20);
			outtextxy(-50, 145, s3);
		}
		else if (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>220 + SCREEN_HEIGHT / 2 && m.y < 270 + SCREEN_HEIGHT / 2)
		{
			setfillcolor(0x25c1ff);
			solidroundrect(-100, 220, 100, 270, 20, 20);
			outtextxy(-67,225, s4);
			while (m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>220 + SCREEN_HEIGHT / 2 && m.y < 270 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == (WM_LBUTTONDOWN))
					return (option = 3);
				if (!(m.x > -100 + SCREEN_WIDTH / 2 && m.x < 100 + SCREEN_WIDTH / 2 && m.y>220 + SCREEN_HEIGHT / 2 && m.y < 270 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(BROWN); //����Ϸ
					solidroundrect(-100, 220, 100, 270, 20, 20);
					outtextxy(-67, 225, s4);
					break;
				}
			}
			setfillcolor(BROWN);
			solidroundrect(-100, 220, 100, 270, 20, 20);
			outtextxy(-67, 225, s4);
		}
	}
}

//���ƹ���ҳ
void Game_Controller::portray_rulespage() const
{

	setfillcolor(0x238E6B);
	solidrectangle(-600, -400, 600, -250);


	RECT rect = { -100,-370,100,-280 };
	const wchar_t rule_page_title[] = L"����ҳ";
	//outtextxy(-500, -350, rule_page_title);

	settextstyle(60, 0, _T("����"));
	drawtext(rule_page_title, &rect, DT_VCENTER | DT_SINGLELINE|DT_CENTER);


	setfillcolor(0x00EEEE);
	solidrectangle(-600, -251, 600, -34);

	setfillcolor(0x00CDCD);
	solidrectangle(-600, -33, 600, 183);

	setfillcolor(0x00FFFF);
	solidrectangle(-600, 184, 600, 400);

	//��һ��ģʽ�Ĺ���

	const wchar_t* rules[3] =
	{
		L"���Ʒ����������С�ߵ�ǰ������,ʹ�߳Ե���������λ���ϵ�ʳ�ÿ�γɹ��Ե�ʳ���С���峤������һ�㣬�÷����ӡ�ʳ��Թ����ٴ������������С��ײ���߽������ͷ��������ײʱ���߽��ҵ�����Ϸ������",
		L"�߹ҵ��󣬴�ʱ��ʬ��ı���ʾ��ɫ��ɱ߽磬����������µ�ʳ����ߣ���Ϸ������ֱ��ʣ��ռ䲻���������µ��ߺ�ʳ��Ϊֹ��",
		L"�߹ҵ��󣬴�ʱ��ʬ��ı���ʾ��ɫ���ʳ�����������µ�ʳ����ߣ���Ϸ������ֱ��ײǽ����>5����ʣ��ռ䲻���������µ��ߺ�ʳ��Ϊֹ"
	};

	const wchar_t* versions[3] =
	{
		L"���Ű�",L"���װ�",L"�߼���"
	};

	const COLORREF rule_page_colors[3] =
	{
		0x00EEEE,0x00CDCD,0x00FFFF
	};


	const wchar_t enter_game_button[] = L"��ʼ����";
	//����ѭ��������ӡ����ģʽ�Ĺ���
	
	for (int i = 0; i < 3; i++)
	{
		settextcolor(BLACK);
		setfillcolor(rule_page_colors[i]);  //������
		solidrectangle(-600, -251 + 218 * i, 600, -34 + 217 * i);

		rect = { -550,-225+217*i,-450,-190+217*i };
		settextstyle(27, 0, _T("����"), 0, 0, 1000, false, false, false);
		drawtext(versions[i], &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

		rect = { -450,-220 + 217 * i,200,-20 + 217 * i };
		settextstyle(25, 0, _T("����"), 0, 0, 600, false, false, false);
		drawtext(rules[i], &rect, DT_LEFT | DT_WORDBREAK);


		setfillcolor(0x00ADCD);  //0xD7FF�ǰ���ȥ����ɫ
		solidroundrect(400, -251 + 218 * i + (217 - 170), 550, -34 + 217 * i - 120,20,20);
		rect = { 400, -251 + 218 * i + (217 - 170) ,550, -34 + 217 * i - 120 };
		settextcolor(WHITE);
		settextstyle(25, 0, _T("����"), 0, 0, 600, false, false, false);
		drawtext(_T("��ʼ����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	}
	//�������½ǵķ��ذ�ť
	setfillcolor(0x238E6B);
	solidroundrect(490, 345, 590, 390,20,20);
	rect = { 490, 345, 590, 390 };
	settextstyle(25, 0, _T("����"), 0, 0, 600, false, false, false);
	settextcolor(WHITE);
	drawtext(_T("����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	
}

//�õ���Ϸģʽ���������ף����ź͸߼�
int Game_Controller::get_mode()
{
	ExMessage m;
	RECT rect;
	while (true)
	{
		getmessage(&m,EM_MOUSE);
		for (int i = 0; i < 3; i++)
		{
			bool tag = m.x > 400+SCREEN_WIDTH/2 && m.x<550 + SCREEN_WIDTH / 2 && m.y>-251 + 218 * i + (217 - 170)+SCREEN_HEIGHT / 2 && m.y < -34 + 217 * i - 120 + SCREEN_HEIGHT / 2;
			if (tag)
			{
				setfillcolor(0xD7FF);
				solidroundrect(400, -251 + 218 * i + (217 - 170), 550, -34 + 217 * i - 120, 20, 20);
				rect = { 400, -251 + 218 * i + (217 - 170) ,550, -34 + 217 * i - 120 };
				settextcolor(WHITE);
				settextstyle(25, 0, _T("����"), 0, 0, 600, false, false, false);
				drawtext(_T("��ʼ����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				while (m.x > 400 + SCREEN_WIDTH / 2 && m.x<550 + SCREEN_WIDTH / 2 && m.y>-251 + 218 * i + (217 - 170) + SCREEN_HEIGHT / 2 && m.y < -34 + 217 * i - 120 + SCREEN_HEIGHT / 2)
				{
					getmessage(&m, EM_MOUSE);
					if (m.message == WM_LBUTTONDOWN)
						return i;
					if (!(m.x > 400 + SCREEN_WIDTH / 2 && m.x<550 + SCREEN_WIDTH / 2 && m.y>-251 + 218 * i + SCREEN_HEIGHT / 2 + (217 - 170) && m.y < -34 + 217 * i - 120 + SCREEN_HEIGHT / 2))
					{
						setfillcolor(0x00ADCD);
						solidroundrect(400, -251 + 218 * i + (217 - 170), 550, -34 + 217 * i - 120, 20, 20);
						drawtext(_T("��ʼ����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
						break;
					}
				}
				break;
				
			}
		}
		if (m.x >490+SCREEN_WIDTH/2 && m.x<590+SCREEN_WIDTH/2 && m.y>345+SCREEN_HEIGHT/2&& m.y <390+SCREEN_HEIGHT/2 )
		{
			setfillcolor(0x32CD9A);
			solidroundrect(490, 345, 590, 390, 20, 20);
			rect = { 490,345,590,390 };
			settextstyle(25, 0, _T("����"), 0, 0, 600, false, false, false);
			settextcolor(WHITE);
			drawtext(_T("����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

			while (m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN)
					return EXIT;
				if (!(m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(0x238E6B);
					solidroundrect(490, 345, 590, 390, 20, 20);
					drawtext(_T("����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
					break;
				}
			}

		}
	}
}

//�������ѡ���ģʽ��game_controller���еĳ�Ա��������
void Game_Controller::set_mode(const int m)
{
	
	std::fstream ranks_file("ranks.log", std::ios::in);
	
	ranks_file.seekg(int(double(159)*double(m)), std::ios::beg);
	int num_records = 0;
	ranks_file >> num_records;
	if (num_records == 0)
		best_score = 0;
	else
	{
		ranks_file.seekg(int(double(159) * double(m) + 3), std::ios::beg);
		ranks_file >> best_score;
	}
	ranks_file.close();
	

	mode = m;
	if (mode == 0)
		hp = 1;
	else if (mode == 2)
		hp = 5;
	else if (mode == 1)
		hp = 5;
}

//���óɼ�
void Game_Controller::set_score(const int s)
{
	score = s;
}

//��������ֵ
void Game_Controller::set_hp(const int h)
{
	hp = h;
}

//��ʼ��ȫ�ֵ�ͼ
void Game_Controller::init_settings()
{
	for (int i = 1; i <= MAP_WIDTH; i++)
		for (int j = 1; j <= MAP_HEIGHT; j++)
			map[i][j] = static_cast<unsigned char>(0);//Ϊ0�ʹ����ǿտյĵ���
}

//��ʽ����һ��ģʽ����Ϸ
void Game_Controller::enter_game()
{
	init_settings();
	Snake snake;
	Obstacle obstacle;
	Food food;
	snake.init();
	obstacle.init();
	food.init(mode);

	portray_gamepage(snake, obstacle, food);

	set_username();//�õ��û���
	portray_gamepage(snake, obstacle, food);
	(void)_getch();
	single_round(snake, obstacle, food); //��ʼ��Ϸ�߼�
}

//������Ϸҳ��
void Game_Controller::portray_gamepage(Snake& snake, Obstacle&, Food& food)
{
	setfillcolor(0x33cccc); //��Ϸ������౳��ɫ
	solidrectangle(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, -SCREEN_WIDTH / 2 + 295, SCREEN_HEIGHT / 2);//��Ϊ300
	setfillcolor(0x006666);
	solidrectangle(-SCREEN_WIDTH / 2 + 296, -SCREEN_HEIGHT / 2, -SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2);//����ͼ�������ʾ���ķֽ���

	RECT rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 30,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 30 + 70 };

	settextcolor(0x333333);
	settextstyle(28, 0, _T("����"),0,0,1000,false,false,false);
	switch (mode)
	{
		case 0:
			drawtext(L"���Ű�", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		case 1:
			drawtext(L"���װ�", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		case 2:
			drawtext(L"�߼���", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		default:
			break;
	}

	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 150,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 150 + 70 };
	drawtext(L"��ǰ�÷�:",& rect, DT_VCENTER | DT_LEFT);
	wchar_t score_str[21];
	int2str(score, score_str);
	rect.left += 130; rect.top -= 22;  //ԭ�����ұ߽�+80
	rect.right += 15; rect.bottom -= 22;
	drawtext(score_str, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	//*��ʼ�����ʷ��߷���
	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 200,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 150 + 120 };
	drawtext(L"��ߵ÷�:", &rect, DT_VCENTER | DT_LEFT);
	wchar_t best_score_str[21];
	int2str(best_score, best_score_str);
	rect.left += 130; rect.top -= 22;  //ԭ�����ұ߽�+80
	rect.right += 15; rect.bottom -= 22;
	drawtext(best_score_str, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);



	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 240,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 240 + 70 };
	drawtext(L"��ǰ����", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	IMAGE heart;
	loadimage(&heart, _T("image/heart.png"));
	for (int i = 0; i < hp; i++)
		putimage(-SCREEN_WIDTH / 2 +7+56*i, -SCREEN_HEIGHT / 2 + 240 + 60, &heart);



	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 360,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 360 + 70 };
	drawtext(L"��ǰʳ��ʣ��", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	IMAGE burger_icon;
	loadimage(&burger_icon, _T("image/burger_icon.png"));
	putimage(-SCREEN_WIDTH / 2 + 45, 25, &burger_icon);
	rect = { -SCREEN_WIDTH / 2 + 130,35, -SCREEN_WIDTH / 2 + 260,65 };

	wchar_t buffer[16];
	buffer[0] = 'x';
	buffer[1] = ' ';
	buffer[2] = '\0';

	wchar_t str[10];
	int2str(food.get_num_burger(), str);
	wcscat_s(buffer, 10, str);
	
	
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	IMAGE chicken_icon;
	loadimage(&chicken_icon, _T("image/chicken_icon.png"));
	putimage(-SCREEN_WIDTH / 2 + 45, 100, &chicken_icon);
	buffer[2] = '\0';
	rect.top += 80;
	rect.bottom += 80;
	int2str(food.get_num_chicken(), str);
	wcscat_s(buffer, 10, str);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	IMAGE fruit_icon;
	loadimage(&fruit_icon, _T("image/fruit_icon.png"));
	putimage(-SCREEN_WIDTH / 2 + 45, 175, &fruit_icon);
	rect.top += 80;
	rect.bottom += 80;
	buffer[2] = '\0';
	int2str(food.get_num_fruit(), str);
	wcscat_s(buffer, 10, str);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	//��ʱ��ߵļƷְ�����ϻ�����
	IMAGE wall_image;
	loadimage(&wall_image, _T("image/wall.png"));

	IMAGE burger_image;
	loadimage(&burger_image, _T("image/burger.png"));

	IMAGE chicken_image;
	loadimage(&chicken_image, _T("image/chicken.png"));

	IMAGE fruit_image;
	loadimage(&fruit_image, _T("image/fruit.png"));
	
	for(int i=1;i<=MAP_WIDTH;i++)
		for (int j = 1; j <= MAP_HEIGHT; j++)
		{
			int x = 20 * (i - 1) + 300 - SCREEN_WIDTH / 2, y = 20 * (j - 1) - SCREEN_HEIGHT / 2;
			if (map[i][j] == OBSTACLE)
				putimage(x,y, &wall_image);

			else if (map[i][j] > 3)
			{
				switch (map[i][j])
				{
					case FOOD_BURGER:
						putimage(x, y, &burger_image);
						break;
					case FOOD_CHICKEN:
						putimage(x, y, &chicken_image);
						break;
					case FOOD_FRUIT:
						putimage(x, y, &fruit_image);
						break;
				}
			}
			else
			{
				if (map[i][j] == 0)
					setfillcolor(0X8FF6FF);
				else if (map[i][j] == SNAKE_BODY)
					setfillcolor(BROWN);
				else if (map[i][j] == SNAKE_HEAD)
					setfillcolor(0X2f6b55);

				fillrectangle(x, y, x+20, y+20);
			}
		}

	//����Ҫ��һ�����ذ�ť
	setfillcolor(BROWN);
	solidroundrect(-SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT /2 -60, -SCREEN_WIDTH / 2 + 300 - 80, SCREEN_HEIGHT/2 - 15,20,20);
	rect = { -SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT/2 - 60, -SCREEN_WIDTH / 2 + 300 - 80, SCREEN_HEIGHT /2- 15 };
	settextcolor(WHITE);
	drawtext(_T("�˳�"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	
}

//���������Ϸ;��ѡ���˳���ʱ����ͣ��Ϸ���������µ��˳�ҳ��
void Game_Controller::portray_exitpage()const
{
	setfillcolor(0xDCF8FF);
	solidroundrect(-150,-75,150,75,ROUND_ANGLE,ROUND_ANGLE);
	RECT rect = {-150,-70,150,0};

	settextcolor(BROWN);
	drawtext(_T("ȷ���˳���"),&rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	rect = {-120,20,-30,60};
	setfillcolor(0xCDEBFF);
	solidroundrect(-120,20,-30,60,ROUND_ANGLE,ROUND_ANGLE);
	drawtext(_T("ȷ��"),&rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	rect = {30,20,120,60};
	solidroundrect(30,20,120,60,ROUND_ANGLE,ROUND_ANGLE);
	drawtext(_T("����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

}

//��ʽ����һ��ģʽ����Ϸ�߼�
void Game_Controller::single_round(Snake& snake, Obstacle&obstacle, Food& food)
{
	
	char ch='\0';
	ExMessage m;
	flushmessage();
	while (hp)
	{
		//�ж���������˳��¼������յ����ؼ����ٻص���������Ϸ�߼������յ��˳������˳���Ϸ�߼�
		peekmessage(&m, EM_MOUSE);
		bool tag = 1;
		if (get_button_click(-SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT / 2 - 60, 140, 45, BROWN, 0x0B78E5, m, L"�˳�",1))
		{
			portray_exitpage();
			while (true)
			{
				getmessage(&m, EM_MOUSE);
				if (get_button_click(-120, 20, 90, 40, 0xCDEBFF, 0xE6F0FA, m, L"ȷ��",0,BROWN))
				{
					tag = 0;
					break;
				}
				if (get_button_click(30, 20, 90, 40, 0xCDEBFF, 0xE6F0FA, m, L"����",0,BROWN))
				{
					portray_gamepage(snake, obstacle, food);
					break;
				}
			}
		}
		flushmessage();
		if (!tag)
			break;
		
		//�ж�������¼�
		if (_kbhit())
		{
			ch = _getch();

			if (ch == 'w' || ch == 'W')
		
				snake.change_direction(NORTH);
			else if (ch == 's' || ch == 'S')
				snake.change_direction(SOUTH);
			else if(ch=='a'||ch=='A')
				snake.change_direction(WEST);
			else if (ch == 'd' || ch == 'D')
				snake.change_direction(EAST);

		}
		
		//�߳��ȵ���
		snake.adjust_length();

		//�÷ָı�
		if (map[snake.head->x][snake.head->y] == FOOD_BURGER)
		{ 
			score += 2;
			food.num_burger--;
		}
		else if (map[snake.head->x][snake.head->y] == FOOD_CHICKEN)
		{
			score += 3;
			food.num_chicken--;
		}
		else if (map[snake.head->x][snake.head->y] == FOOD_FRUIT)
		{
			score += 4;
			food.num_fruit--;
		}

		//ʵʱ�޸���ѷ���
		best_score = score > best_score?score:best_score;

		//������ͷײǽ�����������ӣ����ݲ�ͬģʽ���д���
		if (snake.is_dead())
		{
			if (mode != JUNIOR_MODE)
				hp--;
			if (hp)
			{
				if (mode == JUNIOR_MODE)
					obstacle.append();
				else if (mode == SENIOR_MODE)
					food.append();
				snake.init();
			}
			snake.current_direction = WEST;
			portray_gamepage(snake, obstacle, food);

			(void)_getch();
		}
		else
		{
			if (food.get_num_burger() + food.get_num_chicken() + food.get_num_fruit() == 0)
			{
				food.init(mode);
				portray_gamepage(snake,obstacle,food);
			}
			else
				update_scoreboard(food);
		}
	}
	//�������˵����Ϸ�߼��Ѿ�Ҫ�����ˣ��������û��������������ˣ������Ǳ����ļ�
	Game_Controller::update_record();
	Game_Controller::update_record(1);

}

//ʵʱ����UI�ϵļƷְ�
void Game_Controller::update_scoreboard(const Food& food)
{
	setfillcolor(0x33cccc); //��Ϸ������౳��ɫ
	settextcolor(0x333333);
	//���ȸ��µ÷�
	RECT rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 150,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 150 + 70 };
	
	wchar_t score_str[21];
	int2str(score, score_str);
	rect.left += 130; rect.top -= 22;  //��ʱ�ȱ�
	rect.right += 15; rect.bottom -= 22;
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	//rect.right += 50;
	drawtext(score_str, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	rect = { -SCREEN_WIDTH / 2 + 20,-SCREEN_HEIGHT / 2 + 200,  -SCREEN_WIDTH / 2 + 295 - 20,-SCREEN_HEIGHT / 2 + 150 + 120 };

	wchar_t best_score_str[21];
	int2str(best_score, best_score_str);
	rect.left += 130; rect.top -= 22;  //��ʱ�ȱ�
	rect.right += 15; rect.bottom -= 22;
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	//rect.right += 50;
	drawtext(best_score_str, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);


	//Ȼ�����ʳ��
	rect = { -SCREEN_WIDTH / 2 + 130,35, -SCREEN_WIDTH / 2 + 260,65 };
	wchar_t buffer[16];
	buffer[0] = 'x';
	buffer[1] = ' ';
	buffer[2] = '\0';

	wchar_t str[10];
	int2str(food.get_num_burger(), str);
	wcscat_s(buffer, 10, str);
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	rect.top += 80;
	rect.bottom += 80;
	int2str(food.get_num_chicken(), str);
	buffer[2] = '\0';
	wcscat_s(buffer, 10, str);
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);

	rect.top += 80;
	rect.bottom += 80;
	int2str(food.get_num_fruit(), str);
	buffer[2] = '\0';
	wcscat_s(buffer, 10, str);
	solidrectangle(rect.left, rect.top, rect.right, rect.bottom);
	drawtext((buffer), &rect, DT_VCENTER | DT_LEFT);


}

//����option�Ĳ�ͬ�������а�ҳ�������ʷ��¼ҳ�棬���ҽ����յ����ؼ�ʱ�˳�
void Game_Controller::portray_toolspage(const int option)const
{
	settextcolor(BROWN);
	setfillcolor(0X6A6AFF);
	settextstyle(40, 0, _T("����"),0, 0, 1000, false, false, false);
	solidrectangle(-600, -400, 600, -400 + 134);
	RECT rect = { -200,-400 + 30,200,-400 + 104 };
	if (option == 2)
		drawtext(L"���а�", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	else
		drawtext(L"��ʷ��¼(ֻ��)", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);


	std::fstream ranks_file;
	if(option==2)
		ranks_file.open("ranks.log", std::ios::in|std::ios::_Nocreate);
	else
		ranks_file.open("records.log", std::ios::in | std::ios::_Nocreate);
	const wchar_t* mode_names[3] =
	{
		L"���Ű�:",L"���װ�:",L"�߼���:"
	};
	const COLORREF colors[3] = { 0xE1E4FF,0XF5F0FF,0XE1E4FF};


	for (int i = 0; i < 3; i++)
	{
		settextstyle(35, 0, _T("����"), 0, 0, 1000, false, false, false);
		setfillcolor(colors[i]);
		solidrectangle(-600, -400 + 134 + 222 * i, 600, -400 + 134 + 222 * (i + 1));
		rect = { -560, -400 + 134 + 222 * i + 10,-440, -400 + 134 + 222 * i + 50 };
		drawtext(mode_names[i], &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

		int num_records = 0;
		ranks_file.seekg(int(double(159) *double( i)), std::ios::beg);
		ranks_file >> num_records;

		settextstyle(30, 0, _T("������"), 0, 0, 800, false, false, false);
		if (num_records == 0)
		{
			rect = { -200, -400 + 134 + 222 * i + 50,200,-400 + 134 + 222 * i + 222 - 50, };
			
			drawtext(L"��������", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		}
		else
		{
			int _score;
			char name[20];
			int year, month, day;
			for (int j = 0; j < num_records; j++)
			{
				ranks_file >> _score;
				ranks_file >> name;
				ranks_file >> year >> month >> day;
				rect = { -435,-400 + 134 + 222 * i + 74 *j,-345,-400 + 134 + 222 * i + 74 * j + 74 };
				drawtext(L"�÷�:", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left =-350;
				rect.right = -110;
				wchar_t buffer[9];
				int2str(_score, buffer);
				drawtext(buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = -110;
				rect.right = 10;
				drawtext(L"�û���:", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 15;
				rect.right = 255;
				wchar_t name_buffer[20] = { '\0' };
				for (int k = 0; name[k]; k++)
					name_buffer[k] = name[k];
				drawtext(name_buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 270;
				rect.right = 390;
				int2str(year, buffer);
				drawtext(buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 390;
				rect.right = 420;
				drawtext(L"-",&rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 420;
				rect.right = 480;
				int2str(month, buffer);
				drawtext(buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 480;
				rect.right = 510;
				drawtext(L"-", &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

				rect.left = 510;
				rect.right = 570;
				int2str(day, buffer);
				drawtext(buffer, &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
				
			}
		}

	}
	//���ذ�ť
	setfillcolor(0x238E6B);
	solidroundrect(490, 345, 590, 390, 20, 20);
	rect = { 490, 345, 590, 390 };
	settextstyle(25, 0, _T("����"), 0, 0, 600, false, false, false);
	settextcolor(WHITE);
	drawtext(_T("����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	ExMessage m;
	
	bool tag = 1;
	while (true)
	{
		getmessage(&m, EM_MOUSE);
		if (m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2)
		{
			setfillcolor(0x32CD9A);
			solidroundrect(490, 345, 590, 390, 20, 20);
			rect = { 490,345,590,390 };
			settextstyle(25, 0, _T("����"), 0, 0, 600, false, false, false);
			settextcolor(WHITE);
			drawtext(_T("����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

			while (m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2)
			{
				getmessage(&m, EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN)
				{
					tag = 0;
					break;
				}
				if (!(m.x > 490 + SCREEN_WIDTH / 2 && m.x < 590 + SCREEN_WIDTH / 2 && m.y>345 + SCREEN_HEIGHT / 2 && m.y < 390 + SCREEN_HEIGHT / 2))
				{
					setfillcolor(0x238E6B);
					solidroundrect(490, 345, 590, 390, 20, 20);
					drawtext(_T("����"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
					break;
				}
			}
			if (!tag)
				break;
		}
	}
}

//����option�Ĳ�ͬ���¶�Ӧ�ļ�¼�ļ�
void Game_Controller::update_record(const int option)const
{
	std::fstream ranks_file;
	if(option==2)
		ranks_file.open("ranks.log", std::ios::in | std::ios::out, std::ios::_Nocreate);
	else
		ranks_file.open("records.log", std::ios::in | std::ios::out, std::ios::_Nocreate);

	ranks_file.seekg(int(double(159) *double( mode)), std::ios::beg);
	int num_ranks = 0, year, month, day;
	ranks_file >> num_ranks;
	if (num_ranks == 0)
	{
		ranks_file.seekg(int(double(159) * double(mode)), std::ios::beg);
		ranks_file << 1;
		ranks_file.seekg(int(double(159) * double(mode)+double(3)), std::ios::beg);
		ranks_file << score << " " << username << " ";
		time_t now = time(0);
		tm* ltm = localtime(&now);
		year = ltm->tm_year + 1900;
		month = ltm->tm_mon + 1;
		day = ltm->tm_mday;
		ranks_file << year<<" ";
		ranks_file << month<<" ";
		ranks_file << day<<" ";
	}

	else
	{
		UINT scores[3];
		//ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg);
		for (int i = 0; i < num_ranks; i++)
		{
			ranks_file.seekg(int(double(159) * double(mode) + 3), std::ios::beg);
			ranks_file.seekg(int(double(52) * double(i)), std::ios::cur);
			ranks_file >> scores[i];  //����¼������������ж�
		}

		int i = 0;
		for (i = 0; i < num_ranks; i++)
		{
			if (score > scores[i]||option==1)
			{
				int temy, temm, temd, temscore;
				char tempname[20];

				int pos;
				if (num_ranks == 3)
					pos = 1;
				else
					pos = num_ranks - 1;
				
				while (pos >= i)  //��������ƶ�һλ
				{
					ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg);
					ranks_file.seekg(int(double(52) * double(pos)), std::ios::cur);
					ranks_file >> temscore >> tempname >> temy >> temm >> temd;
					ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg); //Ѱ�ҵ���һ�У�����ɾ������
					ranks_file.seekg(int(double(52) * double(pos)+52), std::ios::cur);
					ranks_file << "                                                  "; //ɾ����ϣ���ʼ�ƶ�
					//
					ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg); 
					ranks_file.seekg(int(double(52) * double(pos) + 52), std::ios::cur);

					ranks_file <<temscore << " " << tempname << " ";
					ranks_file << temy << " ";
					ranks_file << temm << " ";
					ranks_file << temd << " ";
					pos--;

				}
				//�ں����Ķ��ƶ���Ϻ����ǽ���i��Ĩȥ�������¼�¼
				ranks_file.seekg(int(double(159) * double(mode)+3), std::ios::beg);
				ranks_file.seekg(int(double(52) * double(i)), std::ios::cur);
				ranks_file << "                                                  "; //ɾ����ϣ���ʼ�ƶ�
				ranks_file.seekg(int(double(159) * double(mode) + 3), std::ios::beg);
				ranks_file.seekg(int(double(52) * double(i) ), std::ios::cur);
				ranks_file << score << " " << username << " ";
				time_t now = time(0);
				tm* ltm = localtime(&now);
				year = ltm->tm_year + 1900;
				month = ltm->tm_mon + 1;
				day = ltm->tm_mday;
				ranks_file << year << " ";
				ranks_file << month << " ";
				ranks_file << day << " ";

				ranks_file.seekg(int(double(159) * double(mode)), std::ios::beg); //��������
				num_ranks += (num_ranks != 3);
				ranks_file << num_ranks;
				break;

			}
		}
		if (i == num_ranks && num_ranks < 3)
		{
			ranks_file.seekg(int(double(159) * double(mode) + 3), std::ios::beg);
			ranks_file.seekg(int(double(52) * double(i)), std::ios::cur);
			ranks_file << score << " " << username << " ";
			time_t now = time(0);
			tm* ltm = localtime(&now);
			year = ltm->tm_year + 1900;
			month = ltm->tm_mon + 1;
			day = ltm->tm_mday;
			ranks_file << year << " ";
			ranks_file << month << " ";
			ranks_file << day << " ";

			ranks_file.seekg(int(double(159) * double(mode)), std::ios::beg); //��������
			num_ranks += (num_ranks != 3);
			ranks_file << num_ranks ;
		}


		

	}
	ranks_file.close();

}

//��ȡ�Ϸ����û���
void Game_Controller::set_username()
{
	setfillcolor(0xCDEBFF);
	solidroundrect(-300, -200, 300, 200, ROUND_ANGLE, ROUND_ANGLE);

	RECT rect = { -270,-210,270,0 };
	settextcolor(BROWN);
	drawtext(_T("�������û���(1-7��Ӣ��)"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	setfillcolor(0xDCF8FF);
	solidroundrect(-200, 0, 200, 90, ROUND_ANGLE, ROUND_ANGLE);

	solidroundrect(-70, 120, 70, 190, ROUND_ANGLE, ROUND_ANGLE);
	rect = { -70,120,70,190 };
	drawtext(_T("ȷ��"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	wchar_t name[8] = { '\0' };
	int length = 0, pointer = 0;
	char ch;
	ExMessage m;
	
	rect = { -200, 0, 200, 90 };
	while (true)
	{
		settextcolor(BROWN);
		peekmessage(&m, EM_MOUSE);
		if (get_button_click(-70, 120, 140, 70, 0XDCF8FF, WHITE, m, _T("ȷ��"), true,BROWN))
		{
			if (length == 0)
			{
				settextcolor(BROWN);
				drawtext(_T("���Ϸ�"), &rect, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
				Sleep(1000);
				solidroundrect(-200, 0, 200, 90, ROUND_ANGLE, ROUND_ANGLE);

			}
			else
				break;
		};
		if (_kbhit())
		{
			ch = _getch();
			if ((ch >= 'a' && ch <= 'z') || (ch <= 'Z' && ch>='A') || ch == '_')
			{
				if (length < 7)
				{
					length++;
					name[pointer++] = ch;

					drawtext(name, &rect, DT_VCENTER  | DT_LEFT);
				}
				
			}
			else if (ch == '\b'&&length>0)
			{
				length--;
				name[--pointer] = '\0';
				setfillcolor(0xDCF8FF);
				solidroundrect(-200, 0, 200, 90, ROUND_ANGLE, ROUND_ANGLE);
				drawtext(name, &rect, DT_VCENTER | DT_LEFT);
			}
		}
	}
	for (int i = 0; i < 8; i++)
		username[i] = static_cast<char>(name[i]);


}

Game_Controller::~Game_Controller()
{
	if (map)
	{
		for (int i = 0; i <= MAP_WIDTH; i++)
			delete[] map[i];
		delete[] map;
	}
}