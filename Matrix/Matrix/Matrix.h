#pragma once
#define MAXSIZE 100

//��һ�����ܽ������ȡ�Ƿ񷵻����˵���ָ��
int return_menu();

//��һ���س�
void wait_for_enter();

//��ӡ�˵�
char present_menu();

//����һ����/��ֵ
int input_size(int flag);

//���һ��nrows��,ncols�еľ���
void output_matrix(int* matrix, int nrows, int ncols);

//����һ��nrows��,ncols�еľ���
void input_matrix(int* matrix, int nrows, int ncols,bool is_conv=false);

//ʵ�־���ӷ����������������
int* inner_plus(int* matrix1, int* matrix2, int nrows, int ncols);

//����������/������˻�������ʽ
void output_plus_hadam(int* matrix1, int* matrix2, int* result, int nrows, int ncols, const char choice);

//ʵ�־������˹��ܣ���mainֱ�ӵ���
void nummulti();

//ʵ�־������ˣ��������������
int* inner_nummulti(int* matrix1, int nrows, int ncols, int multiplier);

//��������ʱ�ĳ���
int input_multiplier();

//��ӡÿ�����ܿ�ʼǰ�ı���
void present_title(const char* content);

//ʵ�ֹ�����˻������������������
int* inner_hadamulti(int* matrix1, int* matrix2, int nrows, int ncols);

//ʵ�־���ת�ã���main����
void matritrans();

//ʵ�־���ת�ã��������������
int* inner_trans(int* matrix, int nrows, int ncols);

//ʵ�־���˷�����main����
void matrimulti();

//ʵ�־���˷����������������
int* inner_matrimulti(int* left_matrix, int* right_matrix, int nrows, int npivot, int ncols);

//�������˷�����ʽ
void output_matrix_multi(int* matrix1, int* matrix2, int* result, int nrows, int npivot, int ncols);

//ʵ�־������
void conv();

//ʵ�ֶ�lena�ľ��
void conv_application();

//ʵ�־�����ܣ����������������
int* inner_conv(int* matrix, int* conv_kernel, int nrows, int ncols, bool is_normalize = false);

//ʵ��OTSU�㷨
void OSTU_demo();
