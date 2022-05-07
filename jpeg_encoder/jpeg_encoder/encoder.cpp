#include<iostream>
#include"encoder.h"
#include"PicReader.h"

/**********************************
����:��ɴ���һ��ͼƬ��ȫ����
����:pic_name:ͼ��·��
************************************/
void encoder::Pipeline(const char* pic_name)
{
	MakeFile(pic_name);
	PicReader imreader;
	imreader.readPic(pic_name);
	imreader.getData(pic, w, h);
	WriteHeader();

	RGB2YUV();
	DownSampling();

	short pre_DC_Y = 0;
	short pre_Dc_Cr = 0;
	short pre_Dc_Cb = 0;

	BYTE content = 0;
	int contentpos = 7;
	for (UINT i = 0; i < h / MCU_SIZE; i++) //�� ,�ߺͿ��˳���ܷ���
		for (UINT j = 0; j < w / MCU_SIZE; j++)
		{
			short MCU_Y[4][64] = { 0, };
			short MCU_Cr[64] = { 0, };
			short MCU_Cb[64] = { 0, };
			short Luminance_ZigZag[4][64] = { 0, };
			short Chrominancer_ZigZag[64] = { 0, };
			short Chrominanceb_ZigZag[64] = { 0, };

			DCT(i * MCU_SIZE, j * MCU_SIZE, MCU_Y);
			Quantization(MCU_Y);
			DCT(i * MCU_SIZE / 2, j * MCU_SIZE / 2, MCU_Cr, 0);
			Quantization(MCU_Cr);
			DCT(i * MCU_SIZE / 2, j * MCU_SIZE / 2, MCU_Cb, 1);

			Quantization(MCU_Cb);
			ZigZagReshape(MCU_Y, Luminance_ZigZag);
			ZigZagReshape(MCU_Cr, Chrominancer_ZigZag);
			ZigZagReshape(MCU_Cb, Chrominanceb_ZigZag);

			RestoreMCU(pre_DC_Y, pre_Dc_Cr, pre_Dc_Cb, Luminance_ZigZag, Chrominancer_ZigZag, Chrominanceb_ZigZag, content, contentpos);
		}

	char ch = static_cast<char>(0x00);
	if (contentpos != 7)  //˵������һ���ֽ�δд���ļ�
	{
		outfile.write((char*)&content, sizeof(char));
		if (content == 0xff) //���⴦��
			outfile.write((char*)&ch, sizeof(char));
	}
	outfile.write((char*)&END_MARKER, sizeof(short));
	return;
}


/****************************
����:ʵ��RGB��ͨ����YUV��ͨ��ת��
******************************/
void encoder::RGB2YUV()
{
	//���YUV���ű�
	Ymap = new(nothrow) char* [h];
	Crmap = new(nothrow) char* [h];
	Cbmap = new(nothrow) char* [h];
	if (Ymap == NULL||Crmap==NULL||Cbmap==NULL)
	{
		cerr << "Something Wrong Happens!" << endl;
		exit(EXIT_FAILURE);
	}
	for (UINT i = 0; i < h; i++)
	{
		Ymap[i] = new(nothrow) char[w];
		Crmap[i] = new(nothrow) char[w];
		Cbmap[i] = new(nothrow) char[w];
		if (Crmap[i] == NULL||Cbmap[i]==NULL||Ymap[i]==NULL)
		{
			cerr << "Something Wrong Happens!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	for (UINT i = 0; i < h; i++)
		for (UINT j = 0; j < w; j++)
		{
			Ymap[i][j] = (char)(pic[(i * w + j) * 4] * 0.299 + pic[(i * w + j) * 4 + 1] * 0.587 + pic[(i * w + j) * 4 + 2] * 0.114 - 128);
			Cbmap[i][j] = (char)(pic[(i * w + j) * 4] * (-0.1687) + pic[(i * w + j) * 4 + 1] * (-0.3313) + pic[(i * w + j) * 4 + 2] * 0.500);
			Crmap[i][j] = (char)(pic[(i * w + j) * 4] * (0.500) + pic[(i * w + j) * 4 + 1] * (-0.4187) - pic[(i * w + j) * 4 + 2] * 0.0813);
		}
}


/***************************
����:ʵ�ֶ�ɫ�ȷ����Ľ�������2x2->1)
****************************/
void encoder::DownSampling()
{
	Crmap_DownSamed = new (nothrow)char* [h / 2];
	if (Crmap_DownSamed == NULL)
	{
		cerr << "Something Wrong happens!" << endl;
		exit(EXIT_FAILURE);
	}
	Cbmap_DownSamed = new (nothrow)char* [h / 2];
	if (Cbmap_DownSamed == NULL)
	{
		cerr << "Something Wrong happens!" << endl;
		exit(EXIT_FAILURE);
	}
	for (UINT i = 0; i < h / 2; i++)
	{
		Crmap_DownSamed[i] = new(nothrow) char[w / 2];
		Cbmap_DownSamed[i] = new(nothrow) char[w / 2];
		if (Crmap_DownSamed[i] == NULL || Cbmap_DownSamed[i] == NULL)
		{
			cerr << "Something Wrong happens!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	for (UINT i = 0; i < h / 2; i++)
		for (UINT j = 0; j < w / 2; j++)
		{
			Crmap_DownSamed[i][j] = (Crmap[2 * i][2 * j] + Crmap[2 * i][2 * j + 1] + Crmap[2 * i + 1][2 * j] + Crmap[2 * i + 1][2 * j + 1]) / 4;
			Cbmap_DownSamed[i][j] = (Cbmap[2 * i][2 * j] + Cbmap[2 * i][2 * j + 1] + Cbmap[2 * i + 1][2 * j] + Cbmap[2 * i + 1][2 * j + 1]) / 4;
		}
}


/******************************************
����:ʵ�ֶ�һ��MCU�����ȷ�������ɢ���ұ任
����:base_x: ��16x16С����ԭʼͼ���ϵ�������
	 base_y: ��16x16С����ԭʼͼ���ϵĺ�����
	 MCU_Y:  �洢�任�������
*******************************************/
void encoder::DCT(const int base_x, const int base_y, short MCU_Y[4][64])//base_x,base_y��һ��MCU���Ͻǵ�����
{
	int block_x = base_x;
	int block_y = base_y;
	for (int k = 1; k < 5; k++)
	{
		for (int u = 0; u < BLOCK_SIZE; u++)
		{
			for (int v = 0; v < BLOCK_SIZE; v++)
			{
				double alphau = (u == 0) ? 1.0 / sqrt(8) : 0.5;
				double alphav = (v == 0) ? 1.0 / sqrt(8) : 0.5;
				double tmp = 0;
				for (int x = 0; x < BLOCK_SIZE; x++)
					for (int y = 0; y < BLOCK_SIZE; y++)
						tmp += short(Ymap[block_x + x][block_y + y] * cos((2.0 * x + 1) / 16 * u * PI) * cos((2.0 * y + 1) / 16 * v * PI));

				MCU_Y[k - 1][u * BLOCK_SIZE + v] = static_cast<short>(alphau * alphav * tmp);
			}

		}
		block_x = base_x + (k / 2) * BLOCK_SIZE;
		block_y = base_y + (k % 2) * BLOCK_SIZE;
	}
}


/******************************************
����:ʵ�ֶ�һ��MCU��һ��ɫ�ȷ�������ɢ���ұ任
����:base_x: ��16x16С����ԭʼͼ���ϵ�������
	 base_y: ��16x16С����ԭʼͼ���ϵĺ�����
	 MCU_C:  �洢�任�������
*******************************************/
void encoder::DCT(const int base_x, const int base_y, short MCU_C[64], const bool tag)
{
	for (int u = 0; u < BLOCK_SIZE; u++)
		for (int v = 0; v < BLOCK_SIZE; v++)
		{
			double alphau = (u == 0) ? 1 / sqrt(8.0) : 0.5;
			double alphav = (v == 0) ? 1 / sqrt(8.0) : 0.5;
			double tmp = 0;
			for (int x = 0; x < BLOCK_SIZE; x++)
				for (int y = 0; y < BLOCK_SIZE; y++)
				{
					if (tag == 0)
						tmp += (Cbmap_DownSamed[base_x + x][base_y + y] * cos((2.0 * x + 1) / 16.0 * u * PI) * cos((2.0 * y + 1) / 16.0 * v * PI));
					else if (tag == 1)
						tmp += (Crmap_DownSamed[base_x + x][base_y + y] * cos((2.0 * x + 1) / 16.0 * u * PI) * cos((2.0 * y + 1) / 16.0 * v * PI));
				}

			MCU_C[u * BLOCK_SIZE + v] = static_cast<short>(alphau * alphav * tmp);
		}
}


/******************************************
����:ʵ�ֶ�һ��MCU�����ȷ���������
����: MCU_Y:  ��ɢ���ұ任�����������
*******************************************/
void encoder::Quantization(short MCU_Y[4][64])
{
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 64; i++)
			MCU_Y[k][i] /= Luminance_Quant_Table[i];
}

/******************************************
����:ʵ�ֶ�һ��MCU��ɫ�ȷ���������
����: MCU_Y:  ��ɢ���ұ任�����������
*******************************************/
void encoder::Quantization(short MCU_C[64])
{
	for (int i = 0; i < 64; i++)
		MCU_C[i] /= Chrominance_Quant_Table[i];
}

/******************************************
����:ʵ�ֶ�һ��MCU�����ȷ�����ZigZag����
����: MCU_Y:  ��������������ݣ�
	  ZigZagSequence:������������������
*******************************************/
void encoder::ZigZagReshape(const short MCU_Y[4][64], short ZigZagSequence[4][64])
{
	for (int k = 0; k < 4; k++)
		for (int i = 0; i < 64; i++)
			ZigZagSequence[k][ZigZag_Table[i]] = MCU_Y[k][i];
}

/******************************************
����:ʵ�ֶ�һ��MCU��ɫ�ȷ�����ZigZag����
����: MCU_C:  �������ɫ�����ݣ�
	  ZigZagSequence:����������ɫ������
*******************************************/
void encoder::ZigZagReshape(const short MCU_C[64], short ZigZagSequence[64])
{
	for (int i = 0; i < 64; i++)
		ZigZagSequence[ZigZag_Table[i]] = MCU_C[i];
}

/***************************************
����:��ʼ����������
����:EstablishedLengthTable:�ٷ������ĳ����Ƽ���
	 EstablishedValueTable:�ٷ������Ķ�Ӧֵ
	 HT:������
******************************************/
void encoder::InitHuffmanTable(const BYTE* EstablishedLengthTable, const BYTE* EstablishedValueTable, unit* HT)
{
	int pos = 0;
	int value = 0;
	for (int i = 1; i <= HuffmanTreeHeight; i++)
	{
		for (int j = 0; j < EstablishedLengthTable[i - 1]; j++)
		{   //��������Ͱ�����±꼴��ֵ
			HT[EstablishedValueTable[pos]].length = i;
			HT[EstablishedValueTable[pos]].value = value;
			//�����value��ʵ�Ǳ��룬�±���Դֵ
			pos++;  //Դֵ��value���е�λ������
			value++;  //���볤����ȵ�ֵ��˳���1���ɣ���Canonical Huffman coding������
		}
		value = value << 1;  //ȥ����һ��������������ֳ��ȼ�1����Ӧ��int���ϣ��������ơ�
	}
}

/**************************************
����:���ļ���д��һ��MCU
����:pre_DC_Y:��һ��block��Y��ֱ������
	 pre_Dc_Cr:��һ��block��Cr��ֱ������
	 pre_Dc_Cb:��һ��block��Cb��ֱ������
	 MCU_Y: ��MCU���ĸ����ȷ���������
	 MCU_Cr:��MCU��Cr���ȷ���������
	 MCU_Cb:��MCU��Cb���ȷ���������
	 content:��д���ֽڵ�����
	 contentpos:��д���ֽڵ�ǰ����λ�õ�����
*******************************************/
void encoder::RestoreMCU(short& pre_DC_Y, short& pre_Dc_Cr, short& pre_Dc_Cb, const short MCU_Y[4][64], const short MCU_Cr[64], const short MCU_Cb[64], BYTE& content, int& contentpos)
{
	//����һ��MCU,��Ӧԭ������16x16�ķ�����4��8x8��Y������2����������Cr,Cb�������
	for (int k = 0; k < 4; k++)
		RestoreBlock(pre_DC_Y, MCU_Y[k], content, contentpos, 0);

	RestoreBlock(pre_Dc_Cr, MCU_Cr, content, contentpos, 1);
	RestoreBlock(pre_Dc_Cb, MCU_Cb, content, contentpos, 1);

}

/**************************************
����:���ļ���д��һ��block
����:pre_DC:��һ��block��ֱ������
	 MCU_: ��block��һ������������
	 content:��д���ֽڵ�����
	 contentpos:��д���ֽڵ�ǰ����λ�õ�����
	 tag�������ж����block�����Ȼ���ɫ�ȵı�־
*******************************************/
void encoder::RestoreBlock(short& pre_DC, const short MCU_[64], BYTE& content, int& contentpos,const bool tag)
{
	unit result[128];
	int pos = 0;
	int value = 0; //��Ϊʵ��ֵ���ڶ�AC������ʹ��
	short gap = MCU_[0] - pre_DC;
	pre_DC = MCU_[0];
	if (gap == 0)
		result[pos++] = (tag ? Chrominance_Dc_HT[gap] : Luminance_Dc_HT[gap]);
	//�����������벻��Ҫ��

	else
	{
		unit re = SpecialStandardEncoding(gap);
		result[pos++] = tag ? Chrominance_Dc_HT[re.length] : Luminance_Dc_HT[re.length];
		result[pos++] = re;
	}

	//�ٴ�AC����
	for (int i = 1; i < 64; i++)
	{
		int j = 0;   //һ����Ԫ���е�һ��Ԫ��:0�ĸ���
		for (j = 0; i + j < 64; j++)
			if (MCU_[i + j] != 0)
				break;

		//j��0
		//�������������ô�������:i+j==64->����EOB���ɣ� i+j<64��˵��ǰ����j/16��16��0��С���Լ�(j\%16)��0����һ����0ֵ
		if (i + j == 64)
		{
			result[pos++] = tag ? Chrominance_Ac_HT[EOB] : Luminance_Ac_HT[EOB];
			break;
		}
		else
		{
			for (int m = 0; m < j / 16; m++) //�ⶼ��16��0�Ŀ�
				result[pos++] = tag ? Chrominance_Ac_HT[0xF0] : Luminance_Ac_HT[0xF0];
			result[pos + 1] = SpecialStandardEncoding(MCU_[i + j]);
			value = result[pos + 1].length;
			value = value | ((j % 16) << 4);
			result[pos + 0] = tag ? Chrominance_Ac_HT[value] : Luminance_Ac_HT[value];
			pos = pos + 2;
			i += j;
		}
	}

	UINT cnt = pos;
	//��ʱһ��block�Ѿ�ȫ��ת�Ƶ���unit�У���ʱ��ʼд���ļ��ˣ�д��ĳ���Ϊpos
	UINT mask[] = { 1,2,4,8,16,32,64,128,256,512,1024,2048 ,4096,8192 }; //��Ĥ��������ȡ�ض�λ�ı���λ

	int lengthpos = 0;
	int realvalue = 0;
	const BYTE ch = 0x00;
	for (UINT i = 0; i < cnt; i++)
	{
		lengthpos = result[i].length;
		realvalue = result[i].value;
		for (int j = lengthpos - 1; j >= 0; j--)
		{
			int tmp = realvalue & mask[j];
			if (tmp != 0) //��һλ��1
				content |= mask[contentpos];
			contentpos--;
			if (contentpos < 0) //���ֽ�������
			{
				outfile.write((char*)&content, sizeof(char));
				//�����ֽ�λ
				if (content == 0xff) //���⴦��
					outfile.write((char*)&ch, sizeof(char));
				content = 0;
				contentpos = 7;
			}

		}
	}
}

/**************************************
����:ʵ�ֶ�һ��ֵ�����������(3->11  -3:00)
����:�������ֵ
************************************/
unit encoder::SpecialStandardEncoding(const short& value)
{
	short tem = value;
	unit re;

	int length = 1;
	while (tem != 1 && tem != -1)
	{
		tem /= 2;
		length++;
	}
	tem = value;//����
	re.value = (tem > 0) ? tem : ((1 << length) + value - 1);  //����ȡ��
	re.length = length;
	return re;

}

/******************************
����:����һ�����ļ�
����:ԭʼ�ļ�·��
*******************************/
void encoder::MakeFile(const char* pic_name)
{
	char name[100] = { '\0' };
	int i = 0;
	for (i = 0;; i++)
	{
		if (pic_name[i] == '.')
			break;
		name[i] = pic_name[i];
	}
	//Ϊ�˲�дdefine no warnings
	name[i++] = '.';
	name[i++] = 'j';
	name[i++] = 'p';
	name[i++] = 'e';
	name[i++] = 'g';

	outfile.open(name, ios::out | ios::binary);
	if (outfile.is_open() == 0)
	{
		cerr << "Fail to compress!" << endl;
		exit(EXIT_FAILURE);
	}
}

/**************************************
����:�ڴ�����jpeg�ļ���ʼ��д��һЩ��ͷ
***************************************/
void encoder::WriteHeader()
{
	outfile.write((char*)&SOI_MARKER, sizeof(short));

	outfile.write((char*)&APPO_MARKER, sizeof(short));
	outfile.write((char*)&APP0_SEGMENT_LENGTH, sizeof(short));
	outfile.write("JFIF", sizeof(char) * 5);
	outfile << static_cast<char>(1);
	outfile << static_cast<char>(1);
	outfile << static_cast<char>(0);
	outfile.write((char*)&DENSITY, sizeof(short));
	outfile.write((char*)&DENSITY, sizeof(short));
	outfile << static_cast<char>(0);
	outfile << static_cast<char>(0);

	outfile.write((char*)&DQT_MARKER, sizeof(short));
	outfile.write((char*)&DQT_SEGMENT_LENGTH, sizeof(short));
	outfile << static_cast<char>(0);
	outfile.write((char*)Luminance_QT, sizeof(char) * 64);
	outfile << static_cast<char>(1);
	outfile.write((char*)Chrominance_QT, sizeof(char) * 64);

	outfile.write((char*)&SOFO_MARKER, sizeof(short));
	outfile.write((char*)&SOFO_SEGMENT_LENGTH, sizeof(short));
	outfile << static_cast<char>(8);
	//д��ͼƬ����
	short tmp = turnover(h);
	outfile.write((char*)&tmp, sizeof(short));
	tmp = turnover(w);
	outfile.write((char*)&tmp, sizeof(short));
	outfile << static_cast<char>(3);

	outfile << static_cast<char>(1);  //Y
	outfile << static_cast<char>(0x22);  //���������
	outfile << static_cast<char>(0);

	outfile << static_cast<char>(2);
	outfile << static_cast<char>(0x11);
	outfile << static_cast<char>(1);

	outfile << static_cast<char>(3);
	outfile << static_cast<char>(0x11);
	outfile << static_cast<char>(1);

	//DHT
	outfile.write((char*)&DHT_MARKER, sizeof(short));
	outfile.write((char*)&DHT_LENGTH, sizeof(short));
	outfile << static_cast<char>(0);

	outfile.write((char*)LuminanceDC_HT_Length, sizeof(LuminanceDC_HT_Length));
	outfile.write((char*)LuminanceDC_HT_Value, sizeof(LuminanceDC_HT_Value));

	outfile << static_cast<char>(0x10);
	outfile.write((char*)LuminanceAC_HT_Length, sizeof(LuminanceAC_HT_Length));
	outfile.write((char*)LuminanceAC_HT_Value, sizeof(LuminanceAC_HT_Value));

	outfile << static_cast<char>(0x01);
	outfile.write((char*)ChrominanceDC_HT_Length, sizeof(ChrominanceDC_HT_Length));
	outfile.write((char*)ChrominanceDC_HT_Value, sizeof(ChrominanceDC_HT_Value));
	outfile << static_cast<char>(0x11);
	outfile.write((char*)ChrominanceAC_HT_Length, sizeof(ChrominanceAC_HT_Length));
	outfile.write((char*)ChrominanceAC_HT_Value, sizeof(ChrominanceAC_HT_Value));


	outfile.write((char*)&SOS_MARKER, sizeof(short));
	outfile.write((char*)&SOS_LENGTH, sizeof(short));
	outfile << static_cast<char>(3);

	outfile << static_cast<char>(1);
	outfile << static_cast<char>(0);
	outfile << static_cast<char>(2);
	outfile << static_cast<char>(0x11);

	outfile << static_cast<char>(3);
	outfile << static_cast<char>(0x11);

	outfile << static_cast<char>(0);
	outfile << static_cast<char>(0x3f);
	outfile << static_cast<char>(0);

}

/*****************************
����:�����ֽ����ݸߵ�λ�ֽ�ת��
����:��ת������
*********************************/
short encoder::turnover(short n)
{
	n = ((n << 8) & short(0xFF00)) | ((n >> 8) & short(0x00FF));
	return n;
}

/********************************
����:��ZigZag�ķ�ʽ������������Ӷ������ļ�ͷ
********************************/
void encoder::InitQuantTable()
{
	for (int i = 0; i < 64; i++)
	{
		Luminance_QT[ZigZag_Table[i]] = Luminance_Quant_Table[i];
		Chrominance_QT[ZigZag_Table[i]] = Chrominance_Quant_Table[i];
	}
}

encoder::encoder(UINT width, UINT height) : w(width), h(height)
{
	InitHuffmanTable(LuminanceDC_HT_Length, LuminanceDC_HT_Value, Luminance_Dc_HT);
	InitHuffmanTable(LuminanceAC_HT_Length, LuminanceAC_HT_Value, Luminance_Ac_HT);
	InitHuffmanTable(ChrominanceDC_HT_Length, ChrominanceDC_HT_Value, Chrominance_Dc_HT);
	InitHuffmanTable(ChrominanceAC_HT_Length, ChrominanceAC_HT_Value, Chrominance_Ac_HT);
	InitQuantTable();
};

encoder::~encoder()
{
	delete pic;
	for (unsigned int i = 0; i < h; i++)
	{
		delete[]Ymap[i];
		delete[]Crmap[i];
		delete[]Cbmap[i];
		if (i < h / 2)
		{
			delete[]Crmap_DownSamed[i];
			delete[]Cbmap_DownSamed[i];
		}
	}
	delete[] Ymap;
	delete[] Crmap;
	delete[] Cbmap;
	delete[] Crmap_DownSamed;
	delete[] Cbmap_DownSamed;
	if (outfile.is_open())
		outfile.close();
	cout << "Done!" << endl;
}