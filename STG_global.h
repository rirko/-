//ȫ�ֱ���
#pragma once
#include <stdio.h>//��׼�������
#include <stdlib.h>//��׼��
#include <conio.h>//���̽���
#include <math.h>//��ѧ
#include <Windows.h>//ϵͳ
#include <string.h>//�ַ���
#include <time.h>
#include <graphics.h>
#include <easyx.h>

#include"STG_io.h"
#include"STG_define.h"

//�йصδ��ʱ���ı���
LARGE_INTEGER cpuFreq;//cpuƵ��
LARGE_INTEGER tickBeginTime;//�δ�ʼʱ��
LARGE_INTEGER tickEndTime;//�δ����ʱ��
int fps = 30;//��Ϸ֡��
double sleeptime;
double TRUE_FPS;
int total_flame = 0;
double lasttime;


//ȫ�ֱ���1
int windowwidth = 0;
int windowhigh = 0;

int hard = 5;

int maxhp = 300;
int hp = maxhp;
int hpup = hp;
float hpuprate = 0.25;
int hpclock = 0;

int atk = 2;
int DMG = 200;
float dmgrate = 1;
float stddmgrate = dmgrate;

int maxmp = 300;
int mp = 0;
int standmpup = 3;
int mpup = 3;

int shootclock = 10;
int score = 0;

int skillnumber[9] = {0};
int cutclock = -1;
int cutrush = -1;

float leveltime = 0;
int lt;//�ؿ�ʱ��
int leveljumpout;
int time_used = 0; 
time_t nowtime = 0;
int qte = 0;//qte��ʱ��
int qterand[2] = {0};//qte���
Object video[10];

Object object[100];//��ʼ�����������
int objno = 0;//object number��д����ʾ�����г�player���ʵ����
Sprite spr[10];

Bullet bullet[1000];//��ʼ�����������
int bulno = -1;

IMAGE TITLE[2];//��ʼ����
IMAGE white;//��ɫ����

IMAGE picture[50][2];//��ʼ������ͼƬ���ޣ�[0]Ϊԭͼ��[1]Ϊ���֣�
IMAGE player_picture[2];//�����ͼ
IMAGE judgecircle[2];// ����Ȧ��ͼ
IMAGE start[2];
IMAGE blood[2];

IMAGE crarcter_doctor[2];//��������
IMAGE crarcter_assistant[2];//��������
IMAGE crarcter_kami[2];//������

IMAGE back[6];//����

float playerspeed_quick = 15, playerspeed_slow = 3;//�Ի����ƶ��ٶȱ���

//ȫ�ֱ��� �������
short	kb_up = 0,		kb_down = 0,	kb_left = 0,	kb_right = 0,	kb_w = 0,		
		kb_s = 0,		kb_a = 0,		kb_d = 0,		kb_shift = 0,	kb_z = 0, 
		kb_x = 0,		ms_left = 0,	ms_right = 0,	kb_space=0;

Mousepoint mouse;

MOUSEMSG mousemsg;