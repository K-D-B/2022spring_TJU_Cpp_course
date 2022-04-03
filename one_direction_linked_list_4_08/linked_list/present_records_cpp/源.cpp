/*************************************
*Author: Kaixu Chen   Moondok
*Date: 2022-03-28 09:56:25
*LastEditTime: 2022-03-28 10:29:36
*Description:
 ***************************************/
#include<iostream>
#include<fstream>
using namespace std;

struct student {
    int no;                // ѧ��
    char name[20];         // ����
    int score;             // �ɼ�
    struct student* next;  // ��һ���
    /*! �������޸������ṹ !*/
};

int main()
{
    fstream infile;
    infile.open("D://student/student.txt", ios::in);
    if (infile.is_open() == 0)
    {
        cout << "fail to open the file!" << endl;
        return -1;
    }
    int n = 0;
    infile >> n;
    student* head = new (nothrow) student;
    head->next = NULL;

    student* track = head;  //working pointer
    for (int i = 0; i < n; i++)
    {
        student* newnode = new (nothrow) student;
        infile >> newnode->no >> newnode->name >> newnode->score;
        newnode->next = NULL;
        track->next = newnode;
        track = newnode;
    }

    //output
    cout << "����ѧ������Ϣ����:" << endl;
    track = head->next;
    student* track2 = track;
    while (track)
    {
        cout << "ѧ��:" << track->no << " ����:" << track->name << " �ɼ�:" << track->score << endl;
        track = track->next;
        delete track2;
        track2 = track;
    }
    delete head;  //ɾ��ͷָ��
    infile.close();
    return 0;
}

