
#include<graphics.h>
#include"Gluttonous_Snake.h"


int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	
	Game_Controller Controller; //���ʱ�򣬵�ͼ�Ŀռ�Ϳ��ٺ���
	while (true)
	{
		PlaySound(_T("audio/bgm1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  //������
		Controller.portray_firstpage();                                               //������ҳ
		int option = Controller.get_option();                                     //��ȡѡ��
		if (option == 3)                                //ѡ���˳���Ϸ
			break;

		if (option == 0)                                //ѡ������Ϸ
		{
			Controller.portray_rulespage();                
			int mode = Controller.get_mode();
			if (!(mode + 1))
				continue;
			Controller.set_mode(mode);
			Controller.set_score(0);
			PlaySound(NULL, NULL, SND_FILENAME );
			Controller.enter_game(); //����û�ʤ��/��/�����˳���������Ψһһ�����ڣ�����whileѭ���Ŀ�ͷ
		}
		else if (option == 2)                   //ѡ��鿴���а�
			Controller.portray_toolspage();
			
		else if(option==1)
			Controller.portray_toolspage(option);   //ѡ��鿴��ʷ��¼
	}
	closegraph();
	return 0;
}