//功能函数
#pragma once

#include <stdio.h>//标准输入输出
#include <stdlib.h>//标准库
#include <conio.h>//键盘交互
#include <math.h>//数学
#include <Windows.h>//系统
#include <string.h>//字符串
#include <graphics.h>
#include <easyx.h>

#include"STG_define.h"
#include"STG_global.h"


//物理引擎函数=============================================================================================

//改变速度
//（目标实体，目标速度，目标方向）
void velocity_obj(int i, double speed, double angle)
{
	object[i].velocity = speed;
	object[i].Vangle = angle;
}
void velocity_bul(int i, double speed, double angle)
{
	bullet[i].velocity = speed;
	bullet[i].Vangle = angle;
}

//获得加速度
//（目标实体，加速度，加速度方向）
void accelerate(Object str, double speed, double angle)
{
	str.velocity = sqrt(pow(str.velocity, 2) + pow(speed, 2) - 2 * str.velocity * speed * cos(str.Vangle - angle + PI));
	str.Vangle = str.Vangle + asin
	(
	(
		speed * sin(
			str.Vangle - angle + PI
			)
		) / str.velocity
		);
}

//界面显示相关函数=========================================================================================

//显示透明精灵
//（实体编号）
void transparent(int i)
{
	IMAGE I = *object[i].sprite.img[0];
	int tstrip = object[i].sprite.strip;
	int tframe = object[i].sprite.frame;
	int widt = I.getwidth() / tstrip;
	int heig = I.getheight();

	putimage(
		object[i].x - widt / 2,
		object[i].y - heig / 2,
		widt, heig,
		object[i].sprite.img[1],
		(tframe - 1) * widt, 0, SRCAND);// 显示蒙版
	putimage(
		object[i].x - widt / 2,
		object[i].y - heig / 2,
		widt, heig,
		object[i].sprite.img[0],
		(tframe - 1) * widt, 0, SRCPAINT);//显示图片
	
}void animesprite(int i, int x, int y)
{
		if (spr[i].clock == 0) {
			spr[i].clock = spr[i].speed;
			if (spr[i].frame != spr[i].strip)
				spr[i].frame++;
			else
				spr[i].frame = 1;
		}
	IMAGE I = *spr[i].img[0];
	int tstrip = spr[i].strip;
	int tframe = spr[i].frame;
	int widt = I.getwidth() / tstrip;
	int heig = I.getheight();

	putimage(
		x - widt / 2,
		y - heig / 2,
		widt, heig,
		spr[i].img[1],
		(tframe - 1) * widt, 0, SRCAND);// 显示蒙版
	putimage(
		x - widt / 2,
		y - heig / 2,
		widt, heig,
		spr[i].img[0],
		(tframe - 1) * widt, 0, SRCPAINT);//显示图片

	spr[i].clock--;
}

//程序中生成（激活）实体
//（激活的实体[绝对编号]）
void activate_object(Object object)
{
	object.isused = true;
	object.NO = objno;
	objno++;
}

//生成实体
//（贴图编号,初始速度,初始位置x,初始位置y,初始速度角度,碰撞检测，深度，帧数）
void create_object(int picture_number, double speed, int x, int y, double angle, int hitbox, int deep, int tstrip)
{
	objno++;
	int i = objno;
	object[i].isused = 1;
	object[i].sprite.img[1] = &picture[picture_number][1];
	object[i].sprite.img[0] = &picture[picture_number][0];
	object[i].x = x;
	object[i].y = y;
	object[i].velocity = speed;
	object[i].Vangle = angle;
	object[i].hitbox =hitbox;
	object[i].depht = deep;
	object[i].sprite.strip = tstrip;
	object[objno].NO = objno;
}//（形状类,初始速度,初始位置x,初始位置y,初始速度角度,碰撞半径，深度）

void create_bullet(int type, double speed, int x, int y, double angle, int hitbox, int deep ,COLORREF color,int group)
{
	bulno++;
	int i = bulno;
	bullet[i].isused = 1;
	bullet[i].type = type;
	bullet[i].x = x;
	bullet[i].y = y;
	bullet[i].velocity = speed;
	bullet[i].Vangle = angle;
	bullet[i].hitbox = hitbox;
	bullet[i].depht = deep;
	bullet[i].color = color;
	bullet[i].group = group;
	bullet[bulno].NO = bulno;
}

//破坏实体
//（破坏目标实体）
void destory(Object obj) {
	int i;
	for (i = obj.NO; i < objno; i++)
	{
		object[i] = object[i + 1];
		object[i].NO--;
	}
	object[--objno].isused = 0;
}
void destory(Bullet bul) {
	int i;
	for (i = bul.NO; i <= bulno; i++)
	{
		bullet[i] = bullet[i + 1];
		bullet[i].NO--;
	}
	bullet[bulno--].isused = 0;
}

//碰撞检测
//（待检测实体a，待检测子弹b）
int hit(Object a,Bullet b) 
{
	int distance = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
	int totalhitbox = a.hitbox + b.hitbox;
	if (totalhitbox <= distance) {
		return 0;
	}
	else {
		return 1;
	}
}

//动画（动画编号，是否透明）
void anime(int i, int j) {
	putimage(0, 0, &white);
	if (video[i].sprite.clock == 0) {
		video[i].sprite.clock = video[0].sprite.speed;
		if (video[i].sprite.frame != video[0].sprite.strip)
			video[i].sprite.frame++;
		else
			video[i].sprite.frame = 1;
	}
	IMAGE I = *video[i].sprite.img[0];
	int tstrip = video[i].sprite.strip;
	int tframe = video[i].sprite.frame;
	int widt = I.getwidth() / tstrip;
	int heig = I.getheight();
	if (j == 0) {
		putimage(
			video[i].x - widt / 2,
			video[i].y - heig / 2,
			widt, heig,
			video[i].sprite.img[0],
			(tframe - 1) * widt, 0);//显示图片

	}
	if (j == 1) {
		putimage(
			video[i].x - widt / 2,
			video[i].y - heig / 2,
			widt, heig,
			video[i].sprite.img[1],
			(tframe - 1) * widt, 0,SRCAND);//显示蒙版
		putimage(
			video[i].x - widt / 2,
			video[i].y - heig / 2,
			widt, heig,
			video[i].sprite.img[0],
			(tframe - 1) * widt, 0, SRCPAINT);//显示图片
	}
	
	video[i].sprite.clock--;
}


void anime_line(COLORREF col) {
	setlinecolor(col);
	int t = 6;
	while (t-- > 0) {
		int w = rand() % WIDTH;
		int h = rand() % HIGH;
		line(w, 0, w, 900);
	}
}

void dialogue(IMAGE I[2], LPCTSTR str) {
	void blanktime();
	static int i;
	i = 0;
	int num = CString(str).GetLength();
	num = num / 8;
	settextstyle(30, 0, _T("问藏书房"));
	settextcolor(BLACK);
	setbkmode(OPAQUE);
	while (true)
	{
		cleardevice();
		anime_line(BLACK);
		int w = rand() % 100;
		int h = rand() % 200 + 100;
		int W = rand() % 373;
		int H = rand() % 700;
		putimage(w, h, 200, 200, &I[1], W, H, SRCAND);
		putimage(w, h, 200, 200, &I[0], W, H, SRCPAINT);
		w = rand() % WIDTH - 200;
		h = rand() % HIGH - 200;
		putimage(w, h, 200, 200, &I[1], W, H, SRCAND);
		putimage(w, h, 200, 200, &I[0], W, H, SRCPAINT);
		i++;
		if (i == 30)break;
		FlushBatchDraw();
		blanktime();
	}
	i = 0;
	while (true)
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && i < fps * num)i = fps * num;//空格跳过
		cleardevice();
		outtextxy(300 - i, 480, str);//"助手：“医生！卡兰德克塔娜医生！今天又有患有瘟疫的病人来找你了！”"
		putimage(0, 200 + i, &I[1], SRCAND);
		putimage(0, 200 + i, &I[0], SRCPAINT);
		if (i > fps * num) {
			anime_line(BLACK);
			i = i + 100;
		}
		i++;
		FlushBatchDraw();
		if (i > 900)break;
		blanktime();
	}

}

void dialogue(LPCTSTR str) {
	void blanktime();
	static int i;
	int num = CString(str).GetLength();
	num = num / 8;
	i = 0;
	settextstyle(30, 0, _T("问藏书房"));
	settextcolor(BLACK);
	setbkmode(OPAQUE);
	while (true)
	{
		cleardevice();
		anime_line(BLACK);
		i++;
		if (i == 30)break;
		FlushBatchDraw();
		blanktime();
	}
	i = 0;
	while (true)
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && i < fps * num)i = fps * num;//空格跳过
		cleardevice();
		outtextxy(300 - i, 480, str);//"助手：“医生！卡兰德克塔娜医生！今天又有患有瘟疫的病人来找你了！”"
		if (i > fps * num) {
			anime_line(BLACK);
			i = i + 100;
		}
		i++;
		FlushBatchDraw();
		if (i > 900)break;
		blanktime();
	}

}
void dialogue_white(LPCTSTR str) {
	void blanktime();
	static int i;
	int num = CString(str).GetLength();
	num = num / 8;
	i = 0;
	settextstyle(30, 0, _T("问藏书房"));
	settextcolor(WHITE);
	setbkmode(OPAQUE);
	while (true)
	{
		cleardevice();
		anime_line(DARKGRAY);
		i++;
		if (i == 30)break;
		FlushBatchDraw();
		blanktime();
	}
	i = 0;
	while (true)
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && i < fps * num)i = fps * num;//空格跳过
		cleardevice();
		outtextxy(300 - i, 480, str);//"助手：“医生！卡兰德克塔娜医生！今天又有患有瘟疫的病人来找你了！”"
		if (i > fps * num) {
			anime_line(DARKGRAY);
			i = i + 100;
		}
		i++;
		FlushBatchDraw();
		if (i > 900)break;
		blanktime();
	}

}

void backanime(IMAGE bg) 
{
	static int i = 0;
	int widt = bg.getwidth();
	int heig = bg.getheight();
	putimage(object[0].x / 3, i + object[0].y / 3, &bg);
	putimage(object[0].x / 3-widt, i + object[0].y / 3, &bg);
	putimage(object[0].x / 3, i-heig + object[0].y / 3, &bg);
	putimage(object[0].x / 3-widt, i-heig + object[0].y / 3, &bg);
	putimage(object[0].x / 3, i -2* heig + object[0].y / 3, &bg);
	putimage(object[0].x / 3 - widt, i -2* heig + object[0].y / 3, &bg);
	i++;
	if (i == heig)i = 0;
}

int clockcheck(int group, int clocknumber) {
	int i;
	for (i = 0; i <= bulno; i++) {
		if (bullet[i].group == group) 
			if(bullet[i].clock[clocknumber]==0){
				return 1;
				break;
		}
	}
	return 0;
}

void setclock(int group, int clocknumber, int clocktime,int temp) {
	int i;
	for (i = 0; i <= bulno; i++) 
		if (bullet[i].group == group) {
			bullet[i].tempdate = temp;
			bullet[i].clock[clocknumber] = clocktime;
		}
}