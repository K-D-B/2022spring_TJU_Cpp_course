#pragma once
#include<fstream>
#include<unordered_map>
#include<queue>
#include<vector>
#include<bitset>
using namespace std;
#define BLOCK_SIZE 4096  //��4096�������ֽ�ѹ����һ�����壬���㲹0
struct node
{
	bool position = 0;  //�����жϵ�ǰ������丸�ڵ�����ӻ����Һ��ӣ�Ĭ������
	bool tag = 1;    //�����ж��Ƿ�ΪҶ��㣬Ĭ�ϲ���
	char data = '\0';  //�ֽ�����
	long long int fre = 0;  //����Ƶ��
	node* lchild = NULL;  //����
	node* rchild = NULL;   //�Һ���
	node* parent = NULL;  //���ڵ�
	bool operator >(const node& a)const //���������
	{
		return this->fre> a.fre;
	}
};

//ѹ���ļ�
void Zip_file(ifstream& infile, const char* output_name);

//��ѹ�ļ�
void Unzip_file(ifstream& infile, const char* output_name);

//ͨ����������ĵݹ鷽������һ�ö�����
void PostOrderDeleteTree(node* root);

//ѹ���ļ�ʱͨ�����������������������Ŀ���ļ���
void PreOrderReserveTree(ofstream& outfile, node* root);

//��ѹ�ļ�ʱͨ����������������������������
void PreOrderReadTree(ifstream& infile, node*& root);

//�����ַ��ͽ��Ķ�Ӧ��ϵ �Լ� �����ַ�Ƶ�ʶԽ�������������ȶ��н�����������
node* BuildTree(unordered_map<char, node>& map_char2node, priority_queue<node, vector<node>, greater<node>>& frequency_queue);

//ͳ���ļ��и��ֽڵĳ���Ƶ��
void Count_frequency(node* table, unordered_map<char, node>& map_char2node, string& str);

//ͨ����ѹ���ļ��е�ÿ���ֽڶ�Ӧ�Ĺ���������ѹ���ļ�
void Compression(ofstream& outfile, unordered_map<char, string>& map_char2str, string& str);

//�����ѽ��ɵĹ�����������ÿ���ֽڶ�Ӧ�ı���
void GenerateHuffmanCoding(unordered_map<char, node>& map_char2node, unordered_map<char, string>& map_char2str, node* root);