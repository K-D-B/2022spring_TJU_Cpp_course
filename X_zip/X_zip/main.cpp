#include<iostream>
#include<time.h>
#include<sstream>
#include"X_zip.h"
using namespace std;

//�������������ڶ���������ָ��(ѹ��/��ѹ),�������������ļ������ĸ���Ŀ������ļ�
int main(int argc,char * argv[])
{
	cout << "X_zipper Version --0.1  Author: Kaixu Chen" << endl;

	//�ж���������
	if (argc != 4)
	{
		cerr << "Please make sure the number of parameters is correct!" << endl;
		return -1;
	}

	//�ж��ڶ��������ǲ��ǽ�ѹ����ѹ������
	if (strcmp(argv[1], "zip") && strcmp(argv[1], "unzip"))
	{
		cerr << "Unknown parameters!\nCommand List:\nzip\t unzip" << endl;
		return -1;
	}

	//���Դ�Ŀ���ļ�(��ѹ��/��ѹ��
	ifstream infile;
	infile.open(argv[2], ios::binary);
	if (infile.is_open() == 0)
	{
		cout << "Fail to open the input file!" << endl;
		return -1;
	}
	clock_t finish; 

	if (strcmp(argv[1], "zip") == 0)
		Zip_file(infile, argv[3]);
	else if (strcmp(argv[1], "unzip") == 0)
		Unzip_file(infile,argv[3]);

	finish = clock();
	cout << "Execution time: "<<double(finish) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}

//ѹ��ѡ���Ӧ�ĺ���
void Zip_file(ifstream& infile,const char * output_name)
{
	ofstream outfile;
	outfile.open(output_name, ios::out);
	if (outfile.is_open() == 0)
	{
		cerr << "Fail to create the output file!" << endl;
		exit(1);
	}
	else
	{
		unordered_map<char, node> map_char2node;
		priority_queue<node,vector<node>,greater<node>> frequency_queue;
		
		/*****��ʼ��ȡ�ļ���������*****/
		string buffer;
		ostringstream  tmp;
		tmp << infile.rdbuf();
		string  str = tmp.str();
		cout << "The file has been read in." << endl;
		/*****��ʼ��ȡ�ļ����*****/


		/*****��ʼͳ��Ƶ��******/
		node table[256];
		Count_frequency(table, map_char2node, str);
		cout << "The frequency of characters has been counted." << endl;
		for (unordered_map<char, node>::iterator its = map_char2node.begin(); its != map_char2node.end(); its++)
		{
			frequency_queue.push(its->second);
		}
		/*****ͳ��Ƶ�����******/


		/****��ʼ������****/
		node* root = BuildTree(map_char2node,frequency_queue); //���ɹ�������
		unordered_map<char, string> map_char2str;
		GenerateHuffmanCoding(map_char2node, map_char2str, root);  //����ÿ���ֽڶ�Ӧ����
		cout << "The Huffman tree has been established." << endl;
		/*****���������������****/

		/******��ʼѹ��*****/
		ofstream outfile;
		outfile.open(output_name, ios::binary);  //��Ŀ���ļ�
		if (outfile.is_open() == 0)
		{
			cout << "fail to create new file!" << endl;
			exit(1);
		}
		PreOrderReserveTree(outfile, root);//�ѽ����õĹ�����������Ŀ���ļ�
		cout << "The Huffman tree has been restored in object file." << endl;
		Compression(outfile, map_char2str, str);
		/*****ѹ�����*****/

		PostOrderDeleteTree(root); //���ٹ�������
		root = NULL;
		outfile.close(); //�ر�Ŀ���ļ�
		infile.close();   //�ر������ļ�
		cout << "zipped!" << endl;
	}
}

//��ѹѡ���Ӧ�ĺ���
void Unzip_file(ifstream& infile, const char* output_name)
{
	ofstream outfile;
	outfile.open(output_name, ios::binary);
	if (outfile.is_open() == 0)
	{
		cerr << "fail to create the output file!" << endl;
		return;
	}
	else
	{
		node* root = NULL;
		//��������ļ���ͷ��Huffman��������
		PreOrderReadTree(infile, root);
		cout << "The Huffman tree has been read in." << endl;

		node* track = root;
		if (!track)
			return;
		while (infile.peek() != EOF)
		{
			unsigned int len = 0;
			infile.read((char*)&len, sizeof(short int)); //��ȡ֮���һ��block��Ϣ
			bitset<BLOCK_SIZE>block;
			infile.read((char*)&block, sizeof(block));
			string code = block.to_string().c_str();
			char ch='0';
			unsigned int i = BLOCK_SIZE - len;
			for (; i < BLOCK_SIZE; i++)
			{
				ch = code[i];
				if (ch == '0')
					track = track->lchild;
				else
					track = track->rchild;
				if(track->tag==0)   //������˵����Ҷ��㣡
				{
					char ch2 = track->data;
					outfile.write(&ch2, sizeof(char));
					track = root;
				}
			}
		}
		PostOrderDeleteTree(root);
		root = NULL;
	}
	infile.close();
	outfile.close();
	cout << "unzipped!" << endl;
}
