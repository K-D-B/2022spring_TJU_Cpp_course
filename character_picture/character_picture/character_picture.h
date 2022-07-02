#pragma once
#ifndef __ARRAY_H__
#define __ARRAY_H__
#define MAX_AXIS_NUM 16
#define ASPECT_RATIO 2
#include <iostream>
#include<iomanip>
#include<stdlib.h>
#include<climits>


using namespace std;

class Array;
ostream& operator<< (ostream& o, const Array& a);

//��������Ҫ�Ĳ������ڸ��ƹ���͸�ֵʵ�ֲ�ͬ��ע�⣡ ���ƹ�����ǳ����
class Array
{
public:

    //���캯��
    Array()
    {};

    template <typename... Args>
    Array(Args... args)
    {
        // ��ȡ��������С��ת��Ϊsize_t����
        auto num = sizeof...(args);
        size_t list[] = { args... };
        axisNum = num;

        if (num >= 0)
        {
            unsigned int base = 1;
            for (int i = num - 1; i >= 0; i--)
            {
                shape[i] = list[i];
                shape_num[i] = base;
                base *= shape[i];
            }
        }
        unsigned int size = static_cast<unsigned int>(double(shape[0]) * double(shape_num[0]));
        data = new int[size];
    }

    //���ƹ��캯����ǳ������
    Array(const Array& a) :axisNum(a.axisNum), nowAxis(a.nowAxis), index(a.index),data(a.data)
    {
        for (int i = 0; i < MAX_AXIS_NUM; i++)
        {
            this->shape[i] = a.shape[i];
            this->shape_num[i] = a.shape_num[i];
            this->flag = 1;
        }
    }

    //at����
    template <typename... Args>
    Array at(Args... args)
    {
        // ��ȡ��������С��ת��Ϊsize_t����
        auto num = sizeof...(args);
        size_t list[] = { args... };
        unsigned int newindex = 0;

        Array tmp(*this);
     
        for (unsigned int i = 0; i < num; i++)
            newindex += shape_num[tmp.nowAxis++] * list[i];
        tmp.index = newindex;
        return tmp;
    }

    //reshape����
    template <typename... Args>
    void reshape(Args... args)
    {
        // ��ȡ��������С��ת��Ϊsize_t����
        auto num = sizeof...(args);
        size_t list[] = { args... };
        unsigned int sum = 1;
        for (unsigned int i = 0; i < num; i++)
            sum *= list[i];

        if (sum == this->shape_num[0] * this->shape[0])
        {
            unsigned int base = 1;
            for (int i = num - 1; i >= 0; i--)
            {
                shape[i] = list[i];
                shape_num[i] = base;
                base *= shape[i];
            }
            axisNum = num;
        }
        else
        {
            cerr << "the assigned shape is illegal!" << endl;
            exit(EXIT_FAILURE);
        }

    }

    //��������ָ��
    int* get_content() { return data; }

    //����ĳһ���ض�ֵ
    void set(int value)
    {
        data[index] = value;
    }

    //C��ʽ��ȡĳһ���ض���ֵ
    Array operator[](int index)const
    {
        // �������޸��Ӿ����nowAxis��ֵ�Լ������б�Ҫ��ֵ���Է���һ���Ӿ���
        Array tmp(*this);
        //tmp *this;
        tmp.index += tmp.shape_num[nowAxis] * index;
        tmp.nowAxis++;
        return tmp;
    }

    //��ֵ����������أ���set�Ĺ�����ͬ
    Array& operator=(int data)
    {
        this->data[index] = data;
        return *this;
    }

    //��ֵ����������أ�ע�����ﲻ��ǳ������
    Array& operator=(const Array& a)//��ֵ������
    {
        for (int i = 0; i < MAX_AXIS_NUM; i++)
        {
            this->shape[i] = a.shape[i];
            this->shape_num[i] = a.shape_num[i];
        }
       if (data)
            delete data;
       
        unsigned int size = static_cast<unsigned int>(double(shape[0]) * double(shape_num[0]));
        data = new int[size];
        memcpy_s(this->data, size*4, a.data, size*4);
        index = a.index;
        nowAxis = a.nowAxis;
        axisNum = a.axisNum;
        //data = a.data;
        return (*this);
    }

    //�ӷ�����
    Array operator+ (const Array& a)
    {
        Array tmp;
        tmp = a;
        tmp.flag = 0;
        bool tag = 1;
        if (a.axisNum - a.nowAxis == this->axisNum - this->nowAxis)
        {
            for (unsigned int i = 0; i < a.axisNum - a.nowAxis; i++)
                if (this->shape[i + this->nowAxis] != a.shape[i + a.nowAxis])
                {
                    tag = 0;
                    break;
                }
        }
        else
            tag = 0;
        if(!tag)
        {
            cerr << " the shape is incompatible!" << endl;
            exit(EXIT_FAILURE);
        }
        //�����������˵�����ǰ�������ϸ�
        for (unsigned int i = 0; i < a.shape_num[ a.nowAxis]*a.shape[a.nowAxis]; i++)
        {
            tmp.data[tmp.index + i] += this->data[this->index + i];
        }
        return tmp;
    }
    
    Array operator+ (const int a)
    {
        Array tmp;
        tmp = *this;
        tmp.flag = 0;
        for (unsigned int i = 0; i <this->shape_num[this->nowAxis] * this->shape[this->nowAxis]; i++)
        {
            tmp.data[tmp.index + i] += a;
        }
        return tmp;
    }

    //��������
    Array operator- (const Array& a)
    {
        Array tmp;
        tmp = a;
        tmp.flag = 0;
        bool tag = 1;
        if (a.axisNum - a.nowAxis == this->axisNum - this->nowAxis)
            for (unsigned int i = 0; i < a.axisNum - a.nowAxis; i++)
                if (this->shape[i + this->nowAxis] != a.shape[i + a.nowAxis])
                {
                    tag = 0;
                    break;
                }
                else
                    tag = 0;
        if (!tag)
        {
            cerr << " the shape is incompatible!" << endl;
            exit(EXIT_FAILURE);
        }
        for (unsigned int i = 0; i < a.shape_num[a.nowAxis] * a.shape[a.nowAxis]; i++)
        {
            tmp.data[tmp.index + i] -= this->data[this->index + i];
        }
        return tmp;
    }

    
    //�������أ��ͳ�����
    Array operator-(const int a)
    {
        Array tmp;
        tmp = *this;
        tmp.flag = 0;
        for (unsigned int i = 0; i < this->shape_num[this->nowAxis] * this->shape[this->nowAxis]; i++)
        {
            tmp.data[tmp.index + i] -= a;
        }
        return tmp;
    }

    //�˷�����
    Array operator*(const Array& a)
    {
        Array tmp;
        tmp = a;
        tmp.flag = 0;
        bool tag = 1;
        if (a.axisNum - a.nowAxis == this->axisNum - this->nowAxis)
            for (unsigned int i = 0; i < a.axisNum - a.nowAxis; i++)
                if (this->shape[i + this->nowAxis] != a.shape[i + a.nowAxis])
                {
                    tag = 0;
                    break;
                }
                else
                    tag = 0;
        if (!tag)
        {
            cerr << " the shape is incompatible!" << endl;
            exit(EXIT_FAILURE);
        }
        for (unsigned int i = 0; i < a.shape_num[a.nowAxis] * a.shape[a.nowAxis]; i++)
        {
            tmp.data[tmp.index + i] *= this->data[this->index + i];
        }
        return tmp;
    }

    //�˷����أ��ͳ�����
    Array operator*(const int a)
    {
        Array tmp;
        tmp = *this;
        tmp.flag = 0;
        for (unsigned int i = 0; i < this->shape_num[this->nowAxis] * this->shape[this->nowAxis]; i++)
        {
            tmp.data[tmp.index + i] *= a;
        }
        return tmp;
    }

    //��������
    Array operator/(const Array& a)
    {
        Array tmp;
        tmp = a;
        tmp.flag = 0;
        bool tag = 1;
        if (a.axisNum - a.nowAxis == this->axisNum - this->nowAxis)
            for (unsigned int i = 0; i < a.axisNum - a.nowAxis; i++)
                if (this->shape[i + this->nowAxis] != a.shape[i + a.nowAxis])
                {
                    tag = 0;
                    break;
                }
                else
                    tag = 0;
        if (!tag)
        {
            cerr << " the shape is incompatible!" << endl;
            exit(EXIT_FAILURE);
        }
        for (unsigned int i = 0; i < a.shape_num[a.nowAxis] * a.shape[a.nowAxis]; i++)
        {
            if (this->data[this->index + i] != 0)
                tmp.data[tmp.index + i] *= this->data[this->index + i];
            else
                tmp.data[tmp.index + i] = INT_MAX;
        }
        return tmp;
    }

    //�������أ��ͳ�����
    Array operator/(const int a)
    {
        if (a == 0)
        {
            cerr << "0 cannot be used as a divisor" << endl;
            exit(EXIT_FAILURE);
        }
        Array tmp;
        tmp = *this;
        tmp.flag = 0;
        for (unsigned int i = 0; i < this->shape_num[this->nowAxis] * this->shape[this->nowAxis]; i++)
        {
            tmp.data[tmp.index + i] /= a;
        }
        return tmp;
    }



    operator int()
    {
        return data[index];
    }
    ~Array()
    {
        if (!nowAxis && data&&flag)
            delete[] data;
    }

private:
    friend ostream& operator<< (ostream& o, const Array& a);
    friend class PicReader;
    friend void RGB2ASCII(const Array& a, Array& b, const unsigned int width, const unsigned int height, const int compress_ratio);
    int* data = NULL;
    int index = 0;
    unsigned int shape[16] = { 0, };
    unsigned int shape_num[16] = { 0, };
    unsigned int axisNum = -1;
    unsigned int nowAxis = 0;
    bool flag = 1;
};



const char asciiStrength[] = { 'M', 'N', 'H', 'Q', '$', 'O', 'C', '?',
                        '7', '>', '!', ':', '-', ';', '.' };

void RGB2ASCII(const Array& a, Array& b, const unsigned int width, const unsigned int height, const int compress_ratio);

void ShowPic(const Array& a, const unsigned int width, const unsigned int height);

void CopePicture(const char* picname);

unsigned int  RGB2Gray(const unsigned char R, const unsigned char G, const unsigned char B);

void playvedio();
#endif



