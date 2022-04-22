#include"X_zip.h"

/*******************************************
* ����:ͳ���ļ��и��ֽڵĳ���Ƶ��
* ����: table :256���ֽڶ�Ӧ��Ƶ�ʱ�
*       map_char2node: ʵ���ַ�������һһ��Ӧ��unordered_map��������
*		str: �洢�ļ��Ļ�����
* ***********************************************/
void Count_frequency(node* table, unordered_map<char, node>& map_char2node, string& str)
{
	unsigned int i = 0;
	for (int j = 0; j < 256; j++)
		table[j].data = char(j);
	while (i < str.size())
	{
		unsigned char ch = str[i];
		table[int(ch)].fre++;
		table[int(ch)].tag = 0;
		i++;
	}
	for (int j = 0; j < 256; j++)
		if (table[j].fre != 0)
			map_char2node[char(j)] = table[j];
}

/*******************************************
* ����:ͨ����ѹ���ļ��е�ÿ���ֽڶ�Ӧ�Ĺ���������ѹ���ļ�
* ����:outfile:�ļ���������������
*	   map_char2str:ʵ���ַ������Ӧ�����������һһ��Ӧ��unordered_map��������
*	   str:�洢�ļ��Ļ�����
* *********************************************/
void Compression(ofstream & outfile,unordered_map<char,string> &map_char2str,string& str)
{
	string codeblock;
	unsigned int blocktag = 0;
	unsigned int i = 0;
	i = 0;
	while (i < str.size())
	{
		char ch = str[i];

		codeblock += map_char2str[ch];
		blocktag += unsigned int(map_char2str[ch].size());
		if (codeblock.size() > BLOCK_SIZE - 21)
		{
			bitset<BLOCK_SIZE> compressed_block(codeblock);
			outfile.write((char*)&blocktag, sizeof(short int));
			outfile.write((char*)&compressed_block, sizeof(compressed_block));
			blocktag = 0;
			codeblock.clear();
		}
		i++;
	}
	if (codeblock.size() > 0)
	{
		bitset<BLOCK_SIZE>compressed_block(codeblock);
		outfile.write((char*)&blocktag, sizeof(short int));
		outfile.write((char*)&compressed_block, sizeof(compressed_block));
	}
}


/**********************************************
* ����:�����ѽ��ɵĹ�����������ÿ���ֽڶ�Ӧ�ı���
* ����: map_char2node:ʵ���ַ�������һһ��Ӧ��unordered_map��������
*		map_char2str:ʵ���ַ������Ӧ�����������һһ��Ӧ��unordered_map��������
*		root:�������������
* ************************************************/
void GenerateHuffmanCoding(unordered_map<char, node>& map_char2node, unordered_map<char, string>&map_char2str,node*root)
{

	for (unordered_map<char, node>::iterator it = map_char2node.begin(); it != map_char2node.end(); it++)
	{
		char ch = it->first;
		string code;
		if (map_char2str.find(ch) != map_char2str.end())
			code = map_char2str[ch];
		else
		{
			node* leaf = &map_char2node[ch];
			string code;
			node* track = leaf;
			while (track != root)
			{
				if (track->position == 0)
					code.insert(code.begin(), '0');
				else
					code.insert(code.begin(), '1');
				track = track->parent;
			}
			map_char2str[ch] = code;
		}
	}
}