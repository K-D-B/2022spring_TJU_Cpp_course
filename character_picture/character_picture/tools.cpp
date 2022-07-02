#include"PicReader.h"
#include"FastPrinter.h"
#include<fstream>
#pragma comment(lib, "winmm.lib")

void CopePicture(const char* picname)
{
	//��ȡ��ɫͼƬ
	PicReader reader;
	reader.readPic(picname);
	unsigned int width = 0, height = 0;
	Array colored_pic;
	reader.getData(colored_pic, width, height);

	//ת��Ϊ�洢���ַ���ARRAY����
	Array gray_pic;
	int compress_ratio = (width >= 256 && height >= 256) ? 2 : 1;
	RGB2ASCII( colored_pic,gray_pic, width, height,compress_ratio);

	//չʾͼƬ
	unsigned int newwidth = width / compress_ratio + width % compress_ratio;
	unsigned int newheight = height / ASPECT_RATIO / compress_ratio + height % (ASPECT_RATIO * compress_ratio);
	ShowPic(gray_pic,newwidth, newheight);
	
}

/************************************
* ����:����ͨ��ͼƬת��Ϊ�ַ���
* ����: a:�����Ų�ͼ��Array����
*		b:�������ַ���Array����
*		width:��ͼ���
*		height:��ͼ�߶�
*		compress_ratio:ѹ����
* ****************************************/
void RGB2ASCII(const Array& a, Array& b, const unsigned int width, const unsigned int height,const int compress_ratio)
{
	
	unsigned int newwidth = width / compress_ratio + width % compress_ratio;
	unsigned int newheight = height / ASPECT_RATIO / compress_ratio + height % (ASPECT_RATIO * compress_ratio);

	b.data = new int[newwidth*  newheight];
	b.axisNum = 2;
	b.shape[0] = newheight;
	b.shape[1] = newwidth;

	b.shape_num[0] = newwidth;
	b.shape_num[1] = 1;

	for (unsigned int i = 0; i < width/compress_ratio; i++)
		for (unsigned int j = 0; j < height / ASPECT_RATIO/compress_ratio; j++)
		{
			unsigned int sum = 0;
			for (int m = 0; m < ASPECT_RATIO * compress_ratio; m++)
				for (int n = 0; n < compress_ratio; n++)
					sum += RGB2Gray(a[ASPECT_RATIO * compress_ratio * j + m][compress_ratio * i + n][0],
						a[ASPECT_RATIO * compress_ratio * j + m][compress_ratio * i + n][1],
						a[ASPECT_RATIO * compress_ratio * j + m][compress_ratio * i + n][2]);

			sum /= compress_ratio*compress_ratio*ASPECT_RATIO;
			b[j][i] =// sum;
				asciiStrength[sum / 18];
			
		}
	
	if (height % (ASPECT_RATIO*compress_ratio)!=0)
	{
		for (unsigned int k = 0; k < height%(ASPECT_RATIO * compress_ratio); k++)
		{ 
			for (unsigned int i = 0; i < width/compress_ratio; i++)
			{
				unsigned int post_base = height / (ASPECT_RATIO * compress_ratio);
				unsigned int pre_base = post_base * (ASPECT_RATIO * compress_ratio);

				unsigned int sum;
				for (int j = 0; j < compress_ratio; j++)
					sum += RGB2Gray(a[pre_base + k][compress_ratio * i+j][0], a[pre_base + k][compress_ratio * i+j][1], a[pre_base + k][compress_ratio * i+j][2]);

				sum /= compress_ratio;
				b[post_base + k][i] = //sum;
					asciiStrength[sum/ 18];
			}
		}
	}

	if (width % compress_ratio)
	{
		for (unsigned int i = 0; i < height / ASPECT_RATIO / compress_ratio; i++)
		{

			unsigned int sum = 0;
			for (int j = 0; j < ASPECT_RATIO * compress_ratio; j++)
				sum += RGB2Gray(a[ASPECT_RATIO * compress_ratio * i + j][width - 1][0],
								a[ASPECT_RATIO * compress_ratio * i + j][width - 1][1],
								a[ASPECT_RATIO * compress_ratio * i + j][width - 1][2]);
				
			sum /= (ASPECT_RATIO * compress_ratio);
			
			b[i][width / compress_ratio] = //sum;
				asciiStrength[sum / 18];
		}
	}

	if ((height % (ASPECT_RATIO * compress_ratio) != 0) && (width % compress_ratio))
	{
		for (unsigned int k = 0; k < height % (ASPECT_RATIO * compress_ratio); k++)
			b[height / (ASPECT_RATIO * compress_ratio) + k][width / compress_ratio] =
				RGB2Gray(a[height / (ASPECT_RATIO * compress_ratio) * (ASPECT_RATIO * compress_ratio) + k][width - 1][0],
						 a[height / (ASPECT_RATIO * compress_ratio) * (ASPECT_RATIO * compress_ratio) + k][width - 1][1],
						 a[height / (ASPECT_RATIO * compress_ratio) * (ASPECT_RATIO * compress_ratio) + k][width - 1][2]);
				
	}

	/*ֱ��ͼ���⻯*/
	/**
	int hisgram[256] = { 0, };
	for (int i = 0; i < newwidth; i++)
		for (int j = 0; j < newheight; j++)
			hisgram[b[j][i]]++;
	
	//����ֲ�����
	int LUT[256] = { 0, };
	int s = hisgram[0];
	for (int i = 1; i <= 255; i++)
	{
		s += hisgram[i];
		LUT[i] = 1.0 * s / (newheight * newwidth) * 255;
	}
	
	
	for (int i = 0; i < newwidth; i++)
	{
		if (i == 121)
			cout << "here";
		for (int j = 0; j < newheight; j++)
		{
			b.data[j * newwidth + i] = LUT[b.data[j * newwidth + i]];
			b.data[j * newwidth + i] = asciiStrength[b.data[j * newwidth + i] / 18];
			
			//b[j][i] = asciiStrength[b[j][i] / 18];
		}
		cout << i << endl;
	}

	cout << "h" << endl;*/
}


/************************************
* ����:չʾһ���ַ���
* ����: a:�����ַ���Array����
*		width:�ַ������
*		height:�ַ����߶�
* ****************************************/
void ShowPic(const Array& a,const unsigned int width,const unsigned int height)
{
	FastPrinter printer(width, height, 5);
	char* buffer = new char[width * height];
	unsigned char *frontColorBuffer = new unsigned char[width * height * 3];
	unsigned char* backColorBuffer = new unsigned char[width * height * 3];
	for (unsigned int i = 0; i < height ; i++)
		for(unsigned int j=0;j<width;j++)
		{
			buffer[i*width+j] = static_cast<char>(a[i][j]);
			frontColorBuffer[3 * (i *width + j)] = frontColorBuffer[3 * (i * width + j) + 1] = frontColorBuffer[3 * (i * width + j) + 2] = 0;
			backColorBuffer[3 * (i * width + j)] = backColorBuffer[3 * (i * width + j) + 1] = backColorBuffer[3 * (i * width+ j) + 2] = 255;

		}
	
	for (int i = 0; i <= 1400; i++)
	{
		printer.setData(buffer, frontColorBuffer, backColorBuffer);
		printer.draw(1);
	}
	delete[] buffer;
	delete[] frontColorBuffer;
	delete[] backColorBuffer;
}

/************************************
* ����:����ͨ��ת��Ϊ�Ҷ�
* ����: R,G,B��ͨ����ǿ��
* ****************************************/
unsigned int  RGB2Gray(const unsigned char R, const unsigned char G, const unsigned char B)
{
	unsigned int  sum =( R*299+G*587+B*114+500)/1000;
	return sum;

}


void playvedio()
{
	char** characters = new char* [1541];
	unsigned char** backcolors = new unsigned char* [1541];
	unsigned char** frontcolors = new unsigned char* [1541];
	for (int i = 0; i < 1541; i++)
	{
		characters[i] = new  char[427 * 120];
		frontcolors[i] = new unsigned char[427 * 120 * 3];
		 memset(frontcolors[i], 0, 427 * 120 * 3);
		backcolors[i] = new unsigned char[427 * 120 * 3];
		memset(backcolors[i], 255, 427 * 120 * 3);
	}
	//cout << "�ռ俪�ٺ���" << std::endl;
	fstream in("t.txt", ios::in | ios::binary);
	for (int i = 0; i < 1541; i++)
		in.read((char*)characters[i], 427 * 120);
	//cout << "�ļ�����ȥ��" << std::endl;
	FastPrinter printer(427, 120, 3);

	
	PlaySound(L"music.wav", NULL, SND_FILENAME | SND_ASYNC);
	for (int i = 0; i < 1541; i++)
	{
		for (int j = 0; j < 5+(i%5==0); j++)
		{
			
			printer.setData(characters[i], frontcolors[i], backcolors[i]);
			printer.draw(1);
		}
		
	}

	for (int i = 0; i < 15; i++)
	{
		delete[]characters[i];
		delete[]frontcolors[i];
		delete[]backcolors[i];
	}

	delete[] characters;
	delete[]frontcolors;
	delete[]backcolors;
	in.close();
}
