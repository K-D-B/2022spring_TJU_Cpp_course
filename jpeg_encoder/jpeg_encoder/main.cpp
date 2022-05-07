#include<iostream>
#include"encoder.h"
#include"PicReader.h"

int main(int argc, char* argv[])
{
	if (GetCommand(argc, argv))
		HandleCommand(argv);
	return 0;
}


/***************************************
����:��ȡ�û����������������ָ����ж���Ϸ���
����:argc:�������в�������
	 argv:�������в����б�
����ֵ:�����������Ϸ���
*************************************/
bool GetCommand(int argc, char* argv[])
{
	bool re = false;
	if (argc != 3)
	{
		cerr << "The number of parameters is wrong!" << endl;
		re = false;
	}

	else if (!strcmp("-read", argv[1]) || !(strcmp("-compress", argv[1])))
	{
		fstream infile;
		infile.open(argv[2], ios::in);
		if (infile.is_open() == 0)
		{
			cerr << "Fail to open target file " << argv[2] << " !" << endl;
			re = false;
		}
		else
		{
			infile.close();//�����ܴ򿪣�֤�����ڣ����ÿ�ܼ��ɣ����Թص�����ļ�
			re = true;

		}
	}
	else
		cerr << "the Command is not in the command list!\nCommand List:\n -compress\n -read" << endl;
	return re;
}


/***********************************
����:�����û����������
����: argv:���������û����������
***************************************/
void HandleCommand(char* argv[])
{
	if (!strcmp("-compress", argv[1]))
	{
		encoder jpeg_encoder;
		jpeg_encoder.Pipeline(argv[2]);
	}
	else if (!strcmp("-read", argv[1]))
	{
		PicReader reader;
		BYTE* data = nullptr;
		UINT x, y;
		reader.readPic(argv[2]);
		reader.getData(data, x, y);
		reader.showPic(data, x, y);
	}
}