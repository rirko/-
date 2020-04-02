#pragma once
#include <stdio.h>//标准输入输出
#include <stdlib.h>//标准库
#include <conio.h>//键盘交互
#include <math.h>//数学
#include <Windows.h>//系统
#include <string.h>//字符串
#include <graphics.h>
#include <easyx.h>
//============================================================================================================
//定义区////定义区////定义区////定义区////定义区////定义区////定义区////定义区////定义区////定义区////定义区//
//============================================================================================================
#define pi 3.14159
#define HIGH 900
#define WIDTH 800

//定义函数

#define min(x,y) (x)<(y)?(x):(y)//取最小值
#define max(x,y) (x)>(y)?(x):(y)//取最大值

//#define 问藏书房 黑体
//精灵结构体
#define Sprite struct sprite 
Sprite
{
	int speed = 1;//动画速度
	int clock = speed;//帧计时器
	float zoom = 1;//缩放倍率
	float angle = 0;//贴图角度
	IMAGE* img[2];//贴图与遮罩层对应的地址指针
	int strip = 8;//总帧数
	int frame = 1;//当前帧数
};

//物体结构体
#define Object struct object
Object
{
	int NO = -1;
	int isused = 0;//实体启用开关
	float x = 0.0;//物体x坐标
	float y = 0.0;//物体y坐标
	double velocity = 0.0;//物体速度
	double Vangel = 0.0;//物体运动方向
	Sprite sprite;//物体所对应的精灵
	int hitbox = 0;//碰撞盒子
	int depht = 5;//实体深度
	int clock[5] = { -1,-1,-1,-1,-1};//旗标
};
//子弹结构体
#define Bullet struct bullet
Bullet
{
	int NO = -1;
	int isused = 0;//实体启用开关
	float x = 0.0;//物体x坐标
	float y = 0.0;//物体y坐标
	double velocity = 0.0;//物体速度
	double Vangel = 0.0;//物体运动方向
	int type = 0;//外观类型：0圆形，1正方形，2直线型，3圆弧型，4扇形，5菱形
	int group = 0;
	int hitbox = 0;//碰撞盒子
	int depht = 5;//实体深度
	int clock[10] = { -1,-1,-1,-1,-1 };//旗标
	double tempdate = 0;//用来存储零时数据
	COLORREF color;
};
//鼠标结构体
#define Mousepoint struct mousepoint
Mousepoint
{
	int x = 0,y = 0;
	IMAGE img[2];
};

//定义实体名称
#define player object[0]//将玩家定义为0号实体


