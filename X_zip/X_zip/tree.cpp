#include<iostream>
#include"X_zip.h"
using namespace std;

/***********************************************************************
����:�����ַ��ͽ��Ķ�Ӧ��ϵ �Լ� �����ַ�Ƶ�ʶԽ�������������ȶ��н�����������
����:map_char2node:ʵ���ַ�������һһ��Ӧ��unordered_map��������
	 frequency_queue:�����ַ�Ƶ�ʶԽ����������ȶ���
����ֵ:�����������ڵ�
****************************************************************************/
node* BuildTree(unordered_map<char, node>& map_char2node, priority_queue<node, vector<node>, greater<node>>& frequency_queue)
{
	//��ʼ������
	node* root = NULL; //huffman�������
	while (true)
	{
		node* leftnode = new(nothrow) node;
		if (leftnode == NULL)
		{
			cout << "Something wrong happened!" << endl;
			exit(1);
		}
		leftnode->data = frequency_queue.top().data;
		leftnode->fre = frequency_queue.top().fre;
		leftnode->lchild = frequency_queue.top().lchild;
		leftnode->rchild = frequency_queue.top().rchild;
		leftnode->tag = frequency_queue.top().tag;
		frequency_queue.pop();
		if (leftnode->tag != 0)  //newnode1����Ҷ���
		{
			if (leftnode->lchild)
			{
				leftnode->lchild->parent = leftnode;
				if (leftnode->lchild->tag == 0)
					map_char2node[leftnode->lchild->data] = *leftnode->lchild;
			}
			if (leftnode->rchild)
			{
				leftnode->rchild->parent = leftnode;
				if (leftnode->rchild->tag == 0)
					map_char2node[leftnode->rchild->data] = *leftnode->rchild;
			}
		}
		if (frequency_queue.empty() == true)
		{
			root = leftnode;  //˵���ҵ��������
			break;
		}
		node* rightnode = new (nothrow) node;
		if (rightnode == NULL)
		{
			cout << "Something wrong happened!" << endl;
			exit(1);
		}
		rightnode->data = frequency_queue.top().data;
		rightnode->fre = frequency_queue.top().fre;
		rightnode->lchild = frequency_queue.top().lchild;
		rightnode->rchild = frequency_queue.top().rchild;

		rightnode->tag = frequency_queue.top().tag;
		frequency_queue.pop();
		if (rightnode->tag != 0)  //newnode1����Ҷ���
		{
			if (rightnode->lchild)
			{
				rightnode->lchild->parent = rightnode;
				if (rightnode->lchild->tag == 0)
					map_char2node[rightnode->lchild->data] = *rightnode->lchild;
			}
			if (rightnode->rchild)
			{
				rightnode->rchild->parent = rightnode;
				if (rightnode->rchild->tag == 0)
					map_char2node[rightnode->rchild->data] = *rightnode->rchild;
			}
		}
		leftnode->position = 0;
		rightnode->position = 1;
		node* merged_node = new node; //����ĵ�ַ����ͬ��pop�����Ķ����ĵ�ַ������
		merged_node->fre = leftnode->fre + rightnode->fre;
		merged_node->lchild = leftnode;
		merged_node->rchild = rightnode;
		frequency_queue.push(*merged_node);
		delete merged_node; //���ü�ɾ��
	}
	return root;
}

/*************************************
* ����:ͨ����������ĵݹ鷽������һ�ö�����
* ����:�����������
* ***********************************/
void PostOrderDeleteTree(node* root) //�ݹ�������
{
	if (root == NULL)
		return;
	PostOrderDeleteTree(root->lchild);
	PostOrderDeleteTree(root->rchild);
	delete root;
}


/******************************************
����:ѹ���ļ�ʱͨ�����������������������Ŀ���ļ���
����: outfile: �ļ����������
      root:����Ĺ������������
*******************************************/
void PreOrderReserveTree(ofstream& outfile, node* root)
{
	outfile.write((char*)&root->tag, sizeof(bool));
	if (root->tag == 0)
		outfile.write(&root->data, sizeof(char));
	else
	{
		char ch_nofind = '#';
		char ch_find = '*';
		if (!root->lchild)
			outfile.write(&ch_nofind, sizeof(char));
		else
			outfile.write(&ch_find, sizeof(char));
		if (!root->rchild)
			outfile.write(&ch_nofind, sizeof(char));
		else
			outfile.write(&ch_find, sizeof(char));

		if (root->lchild)
			PreOrderReserveTree(outfile, root->lchild);
		if (root->rchild)
			PreOrderReserveTree(outfile, root->rchild);
	}
}

/******************************************
����:��ѹ�ļ�ʱͨ����������������������������
����: outfile: �ļ�����������
	  root:����Ĺ�����������������
*******************************************/
void PreOrderReadTree(ifstream& infile, node*& root)
{
	bool tag;
	infile.read((char*)&tag, sizeof(bool));
	root = new(nothrow) node;
	if (root == NULL)
	{
		cerr << "Something wrong happened!" << endl;
		exit(1);
	}
	root->tag = tag;
	if (tag == 0)
	{
		char content;
		infile.read(&content, sizeof(char));
		root->data = content;
		return;
	}
	else
	{
		char lefttag, righttag;
		infile.read(&lefttag, sizeof(char));
		infile.read(&righttag, sizeof(char));
		if (lefttag == '*')
			PreOrderReadTree(infile, root->lchild);
		if (righttag == '*')
			PreOrderReadTree(infile, root->rchild);
	}
}


