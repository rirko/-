//全局变量
#pragma once
#include <stdio.h>//标准输入输出
#include <stdlib.h>//标准库
#include <conio.h>//键盘交互
#include <math.h>//数学
#include <Windows.h>//系统
#include <string.h>//字符串
#include <time.h>
#include <graphics.h>
#include <easyx.h>

#include"STG_io.h"
#include"STG_define.h"

//有关滴答计时器的变量
LARGE_INTEGER cpuFreq;//cpu频率
LARGE_INTEGER tickBeginTime;//滴答开始时间
LARGE_INTEGER tickEndTime;//滴答结束时间
int fps = 30;//游戏帧率
double sleeptime;
double TRUE_FPS;
int total_flame = 0;
double lasttime;


//全局变量1
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
int lt;//关卡时间
int leveljumpout;
int time_used = 0; 
time_t nowtime = 0;
int qte = 0;//qte计时器
int qterand[2] = {0};//qte随机
Object vedio[10];

Object object[100];//初始化总物体个数
int objno = 0;//object number缩写，表示程序中除player外的实体数
Sprite spr[10];

Bullet bullet[1000];//初始化总物体个数
int bulno = -1;

IMAGE TITLE[2];//开始界面
IMAGE white;//白色矩形

IMAGE picture[50][2];//初始化载入图片上限（[0]为原图，[1]为遮罩）
IMAGE player_picture[2];//玩家贴图
IMAGE judgecircle[2];// 低速圈贴图
IMAGE start[2];
IMAGE blood[2];

IMAGE crarcter_doctor[2];//主角立绘
IMAGE crarcter_assistant[2];//助手立绘
IMAGE crarcter_kami[2];//神立绘

IMAGE back[6];//背景

float playerspeed_quick = 15, playerspeed_slow = 3;//自机的移动速度变量

//全局变量 键鼠操作
short	kb_up = 0,		kb_down = 0,	kb_left = 0,	kb_right = 0,	kb_w = 0,		
		kb_s = 0,		kb_a = 0,		kb_d = 0,		kb_shift = 0,	kb_z = 0, 
		kb_x = 0,		ms_left = 0,	ms_right = 0,	kb_space=0;

Mousepoint mouse;

MOUSEMSG mousemsg;