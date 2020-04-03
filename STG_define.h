#pragma once
#include <stdio.h>//��׼�������
#include <stdlib.h>//��׼��
#include <conio.h>//���̽���
#include <math.h>//��ѧ
#include <Windows.h>//ϵͳ
#include <string.h>//�ַ���
#include <graphics.h>
#include <easyx.h>
//============================================================================================================
//������////������////������////������////������////������////������////������////������////������////������//
//============================================================================================================
#define PI 3.14159
#define HIGH 900
#define WIDTH 800

//���庯��

#define min(x, y) ((x) < (y) ? (x) : (y))//ȡ��Сֵ
#define max(x, y) ((x) > (y) ? (x) : (y))//ȡ���ֵ

//#define �ʲ��鷿 ����
//����ṹ��
typedef struct
{
	int speed = 1;//�����ٶ�
	int clock = speed;//֡��ʱ��
	float zoom = 1;//���ű���
	float angle = 0;//��ͼ�Ƕ�
	IMAGE* img[2];//��ͼ�����ֲ��Ӧ�ĵ�ַָ��
	int strip = 8;//��֡��
	int frame = 1;//��ǰ֡��
} Sprite;

//����ṹ��
typedef struct
{
	int NO = -1;
	int isused = 0;//ʵ�����ÿ���
	float x = 0.0;//����x����
	float y = 0.0;//����y����
	double velocity = 0.0;//�����ٶ�
	double Vangle = 0.0;//�����˶�����
	Sprite sprite;//��������Ӧ�ľ���
	int hitbox = 0;//��ײ����
	int depht = 5;//ʵ�����
	int clock[5] = { -1,-1,-1,-1,-1};//���
} Object;

//�ӵ��ṹ��
typedef struct
{
	int NO = -1;
	int isused = 0;//ʵ�����ÿ���
	float x = 0.0;//����x����
	float y = 0.0;//����y����
	double velocity = 0.0;//�����ٶ�
	double Vangle = 0.0;//�����˶�����
	int type = 0;//������ͣ�0Բ�Σ�1�����Σ�2ֱ���ͣ�3Բ���ͣ�4���Σ�5����
	int group = 0;
	int hitbox = 0;//��ײ����
	int depht = 5;//ʵ�����
	int clock[10] = { -1,-1,-1,-1,-1 };//���
	double tempdate = 0;//�����洢��ʱ����
	COLORREF color;
} Bullet;

//���ṹ��
typedef struct
{
	int x = 0,y = 0;
	IMAGE img[2];
} Mousepoint;

//����ʵ������
#define player object[0]//����Ҷ���Ϊ0��ʵ��