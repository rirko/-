//�̺߳���

#pragma once

#include <stdio.h>//��׼�������
#include <stdlib.h>//��׼��
#include <conio.h>//���̽���
#include <math.h>//��ѧ
#include <Windows.h>//ϵͳ
#include <string.h>//�ַ���
//#include <time.h>
#include <graphics.h>
#include <easyx.h>

#include"STG_io.h"
#include"STG_define.h"
#include"STG_global.h"

//

//�жϰ��°����ĺ���
void keyboard()
{
	if ((GetAsyncKeyState(0x5a) & 0x8000))kb_z = 1;//z��
	if ((GetAsyncKeyState(0x58) & 0x8000))kb_x = 1;//x��

	if ((GetAsyncKeyState(VK_SHIFT) & 0x8000))kb_shift = 1;//shift��
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000))kb_space = 1;//space��
	if ((GetAsyncKeyState(VK_UP) & 0x8000))kb_up = 1;//�ϼ�
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000))kb_down = 1;//�¼�
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000))kb_left = 1;//���
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))kb_right = 1;//�Ҽ�

	if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000))ms_right = 1;//����Ҽ�
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))ms_left = 1;//������

	/*char input;//����һ��char�ͱ����洢���°�����ֵ

	if (_kbhit())//����а�������
	{
		input = _getch();//��ȡ���µİ���
		if (input == 72)
			//�������ϼ�
		if (input == 80)
			//�������¼�
		if (input == 75)
			//���������
		if (input == 77)
			//�������Ҽ�
	}*/
}

//�������
void setmouse() {
	MOUSEMSG msg;
	if (MouseHit()) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_MOUSEMOVE)
		{
			mouse.x = msg.x;
			mouse.y = msg.y;
			putimage(msg.x, msg.y, &mouse.img[1], SRCAND);
			putimage(msg.x, msg.y, &mouse.img[0], SRCPAINT);
			FlushMouseMsgBuffer();
		}

	}
	
}
//�ͷŰ����ĺ���
void keyboard_release()
{//���̺�������
	kb_up = kb_down = kb_left = kb_right = kb_shift = 

	kb_w = kb_s = kb_a = kb_d = kb_z = 
	
	kb_x = ms_left = ms_right = kb_space=0;

}
//��ȫ֡�ʿհ׺���--------------------------------------------------------------------------------------		��ȫ֡�ʿհ׺���
void blanktime() 
{
	static double temp;
	QueryPerformanceCounter(&tickEndTime);//��ȡ֡�����δ�
	lasttime = (((double)tickEndTime.QuadPart - (double)tickBeginTime.QuadPart) / (double)cpuFreq.QuadPart)*1000;
	sleeptime = (double)(1000.0 / fps) - lasttime;
	if (sleeptime > 0 && sleeptime < 1000) Sleep(sleeptime);
	QueryPerformanceCounter(&tickBeginTime);//��ȡ֡��ʼ�δ�
	TRUE_FPS = 1.0/(((double)tickBeginTime.QuadPart - temp) / (double)cpuFreq.QuadPart);
	temp = tickBeginTime.QuadPart;
	total_flame++;
}




//���ٶ�Ӱ���µ�λ��------------------------------------------------------------------------------------		���ٶ�Ӱ���µ�λ��
void Vmove()
{
	int i;
	for (i = 0; i <= objno; i++) {
		//if (object[i].isused == 0)
			//break;

		object[i].x = object[i].x + object[i].velocity * cos((object[i].Vangle / 180) * PI);
		object[i].y = object[i].y + object[i].velocity * sin((object[i].Vangle / 180) * PI);
	}for (i = 0; i <= bulno; i++) {

		bullet[i].x = bullet[i].x + bullet[i].velocity * cos((bullet[i].Vangle / 180) * PI);
		bullet[i].y = bullet[i].y + bullet[i].velocity * sin((bullet[i].Vangle / 180) * PI);
	}
}

//��Ҳٿ��µ��Ի��ƶ�----------------------------------------------------------------------------------		��Ҳٿ��µ��Ի��ƶ�
void player_move() 
{
	if (!kb_x) {
		if (kb_up && kb_shift == 0)player.y = player.y - playerspeed_quick;
		if (kb_down && kb_shift == 0)player.y = player.y + playerspeed_quick;
		if (kb_left && kb_shift == 0)player.x = player.x - playerspeed_quick;
		if (kb_right && kb_shift == 0)player.x = player.x + playerspeed_quick;

		if (kb_up && kb_shift && mp > 20)player.y = player.y - playerspeed_slow;
		if (kb_down && kb_shift && mp > 20)player.y = player.y + playerspeed_slow;
		if (kb_left && kb_shift && mp > 20)player.x = player.x - playerspeed_slow;
		if (kb_right && kb_shift && mp > 20)player.x = player.x + playerspeed_slow;

		if (kb_up || kb_down || kb_left || kb_right)mp--;
	}
}


//��ͼλ�õ�ˢ��----------------------------------------------------------------------------------------		��ͼλ�õ�ˢ��
void imageFresh()
{
	int i,d;
	for (d = 1; d <= 5; d++) {

		for (i = 0; i < objno + 1; i++) {
			if (object[i].depht == d) 
			{
				if (object[i].sprite.clock == 0) {
					object[i].sprite.clock = object[i].sprite.speed;
					if (object[i].sprite.frame != object[i].sprite.strip)
						object[i].sprite.frame++;
					else
						object[i].sprite.frame = 1;
				}
				transparent(i);
				object[i].sprite.clock--;


			}
		}
		for (i = 0; i < bulno + 1; i++) {
			if (bullet[i].depht == d) 
			{
				setfillcolor(bullet[i].color);
				setlinecolor(bullet[i].color);
				if (bullet[i].type == -1) {
					if (bullet[i].hitbox==20) {
						setfillcolor(LIGHTGRAY);
						setlinecolor(LIGHTGRAY);
						POINT pts[8] = {
						{bullet[i].x + cos((bullet[i].Vangle - 90) / 180 * PI) * bullet[i].hitbox ,
						 bullet[i].y + sin((bullet[i].Vangle - 90) / 180 * PI) * bullet[i].hitbox} ,
						{bullet[i].x + 2 * cos(bullet[i].Vangle / 180 * PI) * bullet[i].hitbox ,
						 bullet[i].y + 2 * sin(bullet[i].Vangle / 180 * PI) * bullet[i].hitbox },
						{bullet[i].x + cos((bullet[i].Vangle + 90) / 180 * PI) * bullet[i].hitbox,
						 bullet[i].y + sin((bullet[i].Vangle + 90) / 180 * PI) * bullet[i].hitbox},
						{bullet[i].x - 4 * cos(bullet[i].Vangle / 180 * PI) * bullet[i].hitbox ,
						 bullet[i].y - 4 * sin(bullet[i].Vangle / 180 * PI) * bullet[i].hitbox} ,
						};
						solidpolygon(pts, 4);
					}
					else
					{
						setfillcolor(WHITE);
						setlinecolor(RED);
						fillrectangle(bullet[i].x - bullet[i].hitbox / 2, bullet[i].y - bullet[i].hitbox, bullet[i].x + bullet[i].hitbox / 2, bullet[i].y + bullet[i].hitbox);

					}
				}
				if (bullet[i].type == 0) {
					circle(bullet[i].x, bullet[i].y, bullet[i].hitbox + 3);
					solidcircle(bullet[i].x, bullet[i].y, bullet[i].hitbox);
				}
				if (bullet[i].type == 1) {
					solidrectangle(bullet[i].x - bullet[i].hitbox, bullet[i].y - bullet[i].hitbox, bullet[i].x + bullet[i].hitbox, bullet[i].y + bullet[i].hitbox);
				}
				if (bullet[i].type == 2) {
					moveto(bullet[i].x, bullet[i].y);
					linerel(-cos((bullet[i].Vangle/180)*PI) * bullet[i].velocity * 10, -sin((bullet[i].Vangle / 180) * PI) * bullet[i].velocity * 10);
					solidcircle(bullet[i].x, bullet[i].y, bullet[i].hitbox);
				}
				if (bullet[i].type == 3) {
					POINT pts[6] = {
						{bullet[i].x + cos((bullet[i].Vangle - 90) / 180 * PI) * (bullet[i].hitbox + 1) ,
						 bullet[i].y + sin((bullet[i].Vangle - 90) / 180 * PI) * (bullet[i].hitbox + 1)} ,
						{bullet[i].x + 2 * cos(bullet[i].Vangle / 180 * PI) * (bullet[i].hitbox + 1) ,
						 bullet[i].y + 2 * sin(bullet[i].Vangle / 180 * PI) * (bullet[i].hitbox + 1) },
						{bullet[i].x + cos((bullet[i].Vangle + 90) / 180 * PI) * (bullet[i].hitbox + 1),
						 bullet[i].y + sin((bullet[i].Vangle + 90) / 180 * PI) * (bullet[i].hitbox + 1)},
					};
					solidpolygon(pts, 3);
				}
				if (bullet[i].type == 4) {
					solidpie(bullet[i].x - bullet[i].hitbox * 2, bullet[i].y - bullet[i].hitbox * 2, bullet[i].x + bullet[i].hitbox * 2, bullet[i].y + bullet[i].hitbox * 2, -bullet[i].Vangle / 180 * PI - 1.5, -bullet[i].Vangle / 180 * PI + 1.5);
					solidcircle(bullet[i].x, bullet[i].y, bullet[i].hitbox);
				}
				if (bullet[i].type == 5) {
					POINT pts[8] = {
						{bullet[i].x + cos((bullet[i].Vangle - 90) / 180 * PI) * (bullet[i].hitbox + 1) ,
						 bullet[i].y + sin((bullet[i].Vangle - 90) / 180 * PI) * (bullet[i].hitbox + 1)} ,
						{bullet[i].x + 2*cos(bullet[i].Vangle / 180 * PI) * (bullet[i].hitbox + 1) ,
						 bullet[i].y + 2*sin(bullet[i].Vangle / 180 * PI) * (bullet[i].hitbox + 1) },
						{bullet[i].x + cos((bullet[i].Vangle + 90) / 180 * PI) * (bullet[i].hitbox + 1),
						 bullet[i].y + sin((bullet[i].Vangle + 90 )/ 180 * PI) * (bullet[i].hitbox + 1)},
						{bullet[i].x - 4 * cos(bullet[i].Vangle / 180 * PI) * (bullet[i].hitbox + 1) ,
						 bullet[i].y - 4 * sin(bullet[i].Vangle / 180 * PI) * (bullet[i].hitbox + 1)} ,
					};
					solidpolygon(pts, 4);
				}


			}
		}
	}
	
}

//ʵ�������йصĺ���=======================================================================================	ʵ�������йصĺ���

//��ʼ������ʵ��----------------------------------------------------------------------------------------		��ʼ������ʵ��
void startup_activate_object() {
	int i;//����ʼ������Ҫ�����ʵ��ļ��������Ϊ1
	for (i = 0; i < objno + 1; i++) {
		object[i].isused = 1;
	}
}


//ʵ���뿪�����Զ��ƻ�
void auto_destory() 
{
	int i;
	for (i = 2; i <= objno; i++) {
		if (object[i].x<0 || object[i].x > WIDTH || object[i].y<0 || object[i].y > HIGH) 
			object[i].clock[0] = fps;
		if (object[i].clock[0] == 0)
			destory(object[i]);
	}
	for (i = 0; i <= bulno; i++) {
		if (bullet[i].x<-100|| bullet[i].x > (WIDTH+100)
			|| bullet[i].y<-100 || (bullet[i].y > HIGH+100)
			)
		{
			destory(bullet[i]);
		}
	}
}

void Clock()
{
	int i,t;
	if (shootclock > -1)shootclock--;
	if (hpclock > -1)hpclock--;
	if(cutclock>-1)cutclock--;
	if (cutrush > -1)cutrush--;
	for (i = 0; i < objno + 1; i++) {
		if (object[i].isused == 0)break;
		for (t = 0; t < 5; t++) {
			if (object[i].clock[t] == -1)continue;
			object[i].clock[t]--;
		}
	}
	for (i = 0; i < bulno + 1; i++) {
		if (bullet [i] .isused == 0)break;
		for (t = 0; t < 10; t++) {
			if (bullet[i].clock[t] == -1)
				continue;
			bullet[i].clock[t]--;
		}
	}

}

void hitcheck() {
	int i = 0, t = 1;
	for (i = 0; i <= bulno; i++) {
		if (bullet[i].type == -1) {
			for (t = 1; t <= objno; t++) {
				if (hit(object[t], bullet[i])) {
					destory(bullet[i]);
					score = score + 10;
					if (skillnumber[4] && hp == maxhp)score = score + skillnumber[4] * 2;
					if (skillnumber[7]&&hp<maxhp&&hpup<maxhp)hpup++;
					leveltime = leveltime - atk;
				}
			}
		}
		else
		{
			if (hit(player, bullet[i])) {
				destory(bullet[i]);
				if (cutclock == 60) {
					for (int j = 0; j < 20; j++) {
						if ((GetAsyncKeyState(0x5a) & 0x8000)) {
							dmgrate = 0.3;
							break;
						}
						blanktime();
					}
				}
				hp = hp - DMG*dmgrate;
				hpup = hp + (float)DMG * hpuprate*dmgrate;
				score -= 1000;
				setbkcolor(RED);
				cleardevice();
				if (cutrush < 2) {
					player.y = player.y + 30;
					for (int t = 0; t <= bulno; )
						destory(bullet[t]);
				}
				else
					mp = maxmp;
				FlushBatchDraw();
				hpclock = 180;
			}
		}
		
	}

}

void showscore() {
	static int i = 0;
	static int t = 0;
	static int j = 0;
	settextstyle(60, 0, _T("�ʲ��鷿"));
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	TCHAR s[20];
	swprintf_s(s, _T("%05d"),hp);
	outtextxy(i * 10, 200, _T("ʣ������ֵ��"));
	if (i < 20)i++;
	if (i == 20) {
		outtextxy(420, 200, s);
		settextcolor(WHITE);
		outtextxy( t * 10, 250, _T("�ؿ�ʱ�䣺"));
		if(t<20)t++;
		if (t == 20) {
			//lasttime = time(NULL) - nowtime;
			swprintf_s(s, _T("%05d"), (int)lasttime);
			outtextxy(420, 250, s);
			outtextxy(j * 10, 300, _T("������"));
			if (j == 20) {
				swprintf_s(s, _T("%05d"), score);
				outtextxy(420, 300, s);
				FlushBatchDraw();
				Sleep(500);
				outtextxy(200, 350, _T("�ܷ�����"));
				swprintf_s(s, _T("%05d"), score=score+(hp+(360-(int)lasttime)*1000))*hard;
				outtextxy(420, 350, s);
				FlushBatchDraw();
				Sleep(500);
				settextcolor(WHITE);
				setbkmode(OPAQUE);
				setbkcolor(RED);
				outtextxy(140, 500, _T("OPERATION COMPLETED"));
				FlushBatchDraw();
				i = 0;
				j = 0;
				t = 0; 
				for (int i = 0; i < 300; i++) {
					if ((GetAsyncKeyState(VK_SPACE) & 0x8000))break;
					blanktime();
				}leveljumpout = 1;
			}
			if (j < 20)j++;
		}
	}
}

void datawindow() {

	settextstyle(20, 0, _T("����"));
	settextcolor(WHITE);
	setbkmode(OPAQUE);
	TCHAR s[20];
	swprintf_s(s, _T("%lf"), TRUE_FPS);
	outtextxy(700, 0, s);
	swprintf_s(s, _T("%d"), lt);
	outtextxy(700, 20, s);
	swprintf_s(s, _T("%d"), bulno);
	outtextxy(700, 40, s);
}

void chooseskill() {//1�������ظ���������2��ͻ���������ޣ�3��������ǿ�����⣬4�����ˣ�5��Թ�ޣ�6����ʬ��������7�����������
	FlushMouseMsgBuffer();
	TCHAR s[20];
	fps = 60;
	int i = 0;

	setbkcolor(BLACK);
	cleardevice();
	FlushBatchDraw();

	int sk[3] = { rand() % 9,rand() % 9, rand() % 9 };
	for (; sk[0] == sk[1]; sk[1] = rand() % 8);
	for (; sk[0] == sk[2] || sk[1] == sk[2]; sk[2] = rand() % 8);

	setbkcolor(LIGHTGRAY);
	settextcolor(WHITE);
	settextstyle(40, 0, _T("�ʲ��鷿"));
	for (i = 0; i < 3; i++) {
		setbkcolor(LIGHTGRAY);
		switch (sk[i])
		{
		case 1:
			outtextxy(200, 350 + i * 100, _T("[����ı���]"));
			break;
		case 2:
			setbkcolor(LIGHTBLUE);
			outtextxy(200, 350 + i * 100, _T("[��ӡ�ı���]"));
			break;
		case 3:
			setbkcolor(LIGHTBLUE);
			outtextxy(200, 350 + i * 100, _T("[��ӡ�ı���]"));
			break;
		case 4:
			outtextxy(200, 350 + i * 100, _T("[����ı���]"));
			break;
		case 5:
			outtextxy(200, 350 + i * 100, _T("[����ı���]"));
			break;
		case 6:
			setbkcolor(LIGHTRED);
			outtextxy(200, 350 + i * 100, _T("[��ӡ�ı���]"));
			break;
		case 7:
			setbkcolor(LIGHTRED);
			outtextxy(200, 350 + i * 100, _T("[��ӡ�ı���]"));
			break;
		case 8:
			setbkcolor(LIGHTBLUE);
			outtextxy(200, 350 + i * 100, _T("[��ӡ�ı���]"));
			break;
		default:
			setbkcolor(BROWN);
			outtextxy(200, 350 + i * 100, _T("[����ı���]"));
			break;
		}
		FlushBatchDraw();
		Sleep(500);
	}
	FlushBatchDraw();
	Sleep(500);
	while (true)
	{
		setbkcolor(BLACK);
		settextcolor(WHITE);
		if (MouseHit()) mousemsg = GetMouseMsg();
		if (mousemsg.y > 0.9 * windowhigh) {
			setbkcolor(WHITE);
			settextcolor(BLACK); 
			if (mousemsg.uMsg == WM_LBUTTONDOWN) {
				setfillcolor(BLACK);
				for (int j = 0; j < 800; j += 20) {
					solidrectangle(0, 820, j, 900);
					FlushBatchDraw();
					Sleep(10);
				}
				break;
			}
		}
		settextstyle(80, 0, _T("�ʲ��鷿"));
		outtextxy(0, 820, _T("������������[�� ��]������������"));
		FlushBatchDraw();
	}
	settextstyle(40, 0, _T("�ʲ��鷿"));
	setbkcolor(BLACK);
	cleardevice();
	FlushBatchDraw();
	while (true)
	{
		int jumpout = 0;
		static int t;
		setbkcolor(BLACK);
		cleardevice();
		if (MouseHit()) mousemsg = GetMouseMsg();
		for (i = 0; i < 3; i++) {
			if ((mousemsg.y > ((350+i*100) * ((float)windowhigh/900))) && (mousemsg.y < ((390 + i * 100) * ((float)windowhigh / 900)))) {
				setfillcolor(WHITE);
				solidrectangle(0, (350 + i * 100), 800, (389 + i * 100));
				settextcolor(WHITE);
				setbkmode(TRANSPARENT);
				switch (sk[i])
				{
				case 1:
					outtextxy(0, 650, _T("����ܵ��˺���������ظ���ֵ"));
					swprintf_s(s, _T("%d"), skillnumber[1]);
					if (!skillnumber[1])outtextxy(0, 750, _T("[δ���]"));
					if (skillnumber[1]) {
						outtextxy(0, 750, _T("[�ѻ�ã��ɵ���]"));
						outtextxy(0, 800, _T("��ǰ�ȼ���"));
						outtextxy(120, 800, s);

					}
					if (mousemsg.uMsg == WM_LBUTTONDOWN) {
						skillnumber[1]++;
						hpuprate += 0.125;
					}
					break;
				case 2:
					outtextxy(0, 650, _T("΢�������������������ֵ"));
					swprintf_s(s, _T("%d"), skillnumber[2]);
					if (!skillnumber[2])outtextxy(0, 750, _T("[δ���]"));
					if (skillnumber[2]) {
						outtextxy(0, 750, _T("[�ѻ�ã��ɵ���]"));
						outtextxy(0, 800, _T("��ǰ�ȼ���"));
						outtextxy(120, 800, s);

					}
					if (mousemsg.uMsg == WM_LBUTTONDOWN) {
						skillnumber[2]++;
						maxmp += 75;
					}
					break;
				case 3:
					outtextxy(0, 650, _T("΢�������������������ֵ"));
					swprintf_s(s, _T("%d"), skillnumber[3]);
					if (!skillnumber[3])outtextxy(0, 750, _T("[δ���]"));
					if (skillnumber[3]) {
						outtextxy(0, 750, _T("[�ѻ�ã��ɵ���]"));
						outtextxy(0, 800, _T("��ǰ�ȼ���"));
						outtextxy(120, 800, s);
					}
					if (mousemsg.uMsg == WM_LBUTTONDOWN) {
						skillnumber[3]++;
						maxhp += 75;
					}
					break;
				case 4:
					outtextxy(0, 650, _T("������ֵΪ��ʱ��������õķ���΢������"));
					swprintf_s(s, _T("%d"), skillnumber[4]);
					if (!skillnumber[4])outtextxy(0, 750, _T("[δ���]"));
					if (skillnumber[4]) {
						outtextxy(0, 750, _T("[�ѻ�ã��ɵ���]"));
						outtextxy(0, 800, _T("��ǰ�ȼ���"));
						outtextxy(120, 800, s);
					}
					if (mousemsg.uMsg == WM_LBUTTONDOWN)skillnumber[4]++;
					break;
				case 5:
					outtextxy(0, 650, _T("�������������д��ں�ɫ����ʱ���ӵ�����Ƶ�ʴ������"));
					if (!skillnumber[5])outtextxy(0, 750, _T("[δ���]"));
					if (skillnumber[5]) {
						outtextxy(0, 750, _T("[�ѻ�ã����ɵ���]"));
					}
					if (mousemsg.uMsg == WM_LBUTTONDOWN)skillnumber[5]++;
					break;
				case 6:
					outtextxy(0, 650, _T("����ֵ������΢���ظ�"));
					if (!skillnumber[6])outtextxy(0, 750, _T("[δ���]"));
					if (skillnumber[6]) {
						outtextxy(0, 750, _T("[�ѻ�ã����ɵ���]"));
					}
					if (mousemsg.uMsg == WM_LBUTTONDOWN)skillnumber[6]++;
					break;
				case 7:
					outtextxy(0, 650, _T("�������е��˺�΢����������ֵ"));
					if (!skillnumber[7])outtextxy(0, 750, _T("[δ���]"));
					if (skillnumber[7]) {
						outtextxy(0, 750, _T("[�ѻ�ã����ɵ���]"));
					}
					if (mousemsg.uMsg == WM_LBUTTONDOWN)skillnumber[7]++;
					break;
				case 8:
					outtextxy(0, 650, _T("΢����С�ж����С"));
					swprintf_s(s, _T("%d"), skillnumber[8]);
					if (!skillnumber[8])outtextxy(0, 750, _T("[δ���]"));
					if (skillnumber[8]) {
						outtextxy(0, 750, _T("[�ѻ�ã��ɵ���]"));
						outtextxy(0, 800, _T("��ǰ�ȼ���"));
						outtextxy(120, 800, s);
					}
					if (mousemsg.uMsg == WM_LBUTTONDOWN)skillnumber[8]++;
					break;
				default:
					outtextxy(0, 650, _T("��΢�������ܵ����˺�"));
					swprintf_s(s, _T("%d"), skillnumber[0]);
					if (!skillnumber[0])outtextxy(0, 750, _T("[δ���]"));
					if (skillnumber[0]) {
						outtextxy(0, 750, _T("[�ѻ�ã��ɵ���]"));
						outtextxy(0, 800, _T("��ǰ�ȼ���"));
						outtextxy(120, 800, s);
					}
					if (mousemsg.uMsg == WM_LBUTTONDOWN) {
						dmgrate -= 0.05;
						skillnumber[0]++;
					}
					break;
				}
				if (mousemsg.uMsg == WM_LBUTTONDOWN) {
					setfillcolor(BLACK);
					for (int j = 0; j < 800; j+=20) {
						solidrectangle(0, (350 + i * 100), j, (389 + i * 100));
						FlushBatchDraw();
						Sleep(10);
					}
					jumpout = 1;
				}
			}
			setbkmode(OPAQUE);
			switch (sk[i])
			{
			case 1:
				setbkcolor(GREEN);
				settextcolor(WHITE);
				outtextxy(200, 350 + i * 100, _T("[������]"));
				break;
			case 2:
				setbkcolor(YELLOW);
				settextcolor(BROWN);
				outtextxy(200, 350 + i * 100, _T("[ǿ����]"));
				break;
			case 3:
				setbkcolor(GREEN);
				settextcolor(WHITE);
				outtextxy(200, 350 + i * 100, _T("[������]"));
				break;
			case 4:
				setbkcolor(RED);
				settextcolor(WHITE);
				outtextxy(200, 350 + i * 100, _T("[������]"));
				break;
			case 5:
				setbkcolor(RED);
				settextcolor(WHITE);
				outtextxy(200, 350 + i * 100, _T("[������]"));
				break;
			case 6:
				setbkcolor(DARKGRAY);
				settextcolor(WHITE);
				outtextxy(200, 350 + i * 100, _T("[��ʬ������]"));
				break;
			case 7:
				setbkcolor(WHITE);
				settextcolor(BLACK);
				outtextxy(200, 350 + i * 100, _T("[��������]"));
				break;
			case 8:
				setbkcolor(BLUE);
				settextcolor(WHITE);
				outtextxy(200, 350 + i * 100, _T("[�ر�����]"));
				break;
			default:
				setbkcolor(DARKGRAY);
				settextcolor(BLACK);
				outtextxy(200, 350 + i * 100, _T("[ʧЧ�ļ���]"));
				break;
			}
		}
		setlinecolor(WHITE);
		circle(800, 900, t * 60);
		t++;
		FlushBatchDraw();
		FlushMouseMsgBuffer();
		if (jumpout) {
			t = 0;
			break;
		}
		blanktime();
	}
	setbkcolor(BLACK);
	cleardevice();
	FlushBatchDraw();
	Sleep(1000);
}

void pausetime() {
	FlushMouseMsgBuffer();
	TCHAR s[20];
	setfillcolor(BLACK);
	for (int j = 0; j < 41; j++) {
		solidrectangle(0, 820, 20 * j, 900);
		solidrectangle(0, 620, 5 * j, 820);
		FlushBatchDraw();
		Sleep(10);
	}
	settextstyle(30, 0, _T("�ʲ��鷿"));
	setfillcolor(WHITE);
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	for (int j = 0; j < 41; j++) {
		settextcolor(WHITE);
		setbkmode(1);
		setfillcolor(BLACK);
		solidrectangle(0, 620, 200, 820);
		swprintf_s(s, _T("%d"), hp);
		outtextxy(0, 625, _T(" ����ֵ��"));
		outtextxy(100, 625, s);
		swprintf_s(s, _T("%d"), mp);
		outtextxy(0, 665, _T(" ����ֵ��"));
		outtextxy(100, 665, s);
		int skill[6] = { -1,-1,-1,-1,-1,-1 };
		settextstyle(20, 0, _T("�ʲ��鷿"));
		setbkmode(2);
		for (int t = 0; t < 6; t++) {
			for (int k = 0; k < 10; k++) {
				if (skillnumber[k]) {
					int f = 0;
					for (int l = 0; l < t; l++)
						if (k == skill[l])
							f = 1;
					if (f == 1)continue;
					skill[t] = k;
					break;
				}

			}


			switch (skill[t])
			{
			case 1:
				setbkcolor(GREEN);
				settextcolor(WHITE);
				outtextxy(0, 700 + t * 20, _T("[�����ָ�������]"));
				swprintf_s(s, _T("%d"), skillnumber[1]);
				outtextxy(140, 700 + t * 20, s);
				break;
			case 2:
				setbkcolor(YELLOW);
				settextcolor(BROWN);
				outtextxy(0, 700 + t * 20, _T("[������ǿ]"));
				swprintf_s(s, _T("%d"), skillnumber[2]);
				outtextxy(140, 700 + t * 20, s);
				break;
			case 3:
				setbkcolor(GREEN);
				settextcolor(WHITE);
				outtextxy(0, 700 + t * 20, _T("[������ǿ]"));
				swprintf_s(s, _T("%d"), skillnumber[3]);
				outtextxy(140, 700 + t * 20, s);
				break;
			case 4:
				setbkcolor(RED);
				settextcolor(WHITE);
				outtextxy(0, 700 + t * 20, _T("[����]"));
				swprintf_s(s, _T("%d"), skillnumber[4]);
				outtextxy(140, 700 + t * 20, s);
				break;
			case 5:
				setbkcolor(RED);
				settextcolor(WHITE);
				outtextxy(0, 700 + t * 20, _T("[Թ��]"));
				break;
			case 6:
				setbkcolor(DARKGRAY);
				settextcolor(WHITE);
				outtextxy(0, 700 + t * 20, _T("[���ظ���]"));
				break;
			case 7:
				setbkcolor(WHITE);
				settextcolor(BLACK);
				outtextxy(0, 700 + t * 20, _T("[��������]"));
				break;
			case 8:
				setbkcolor(BLUE);
				settextcolor(WHITE);
				outtextxy(0, 700 + t * 20, _T("[�ر�����]"));
				swprintf_s(s, _T("%d"), skillnumber[8]);
				outtextxy(140, 700 + t * 20, s);
				break;
			case 0:
				setbkcolor(DARKGRAY);
				settextcolor(WHITE);
				outtextxy(0, 700 + t * 20, _T("[����ӻ���α��]"));
				swprintf_s(s, _T("%d"), skillnumber[0]);
				outtextxy(140, 700 + t * 20, s);
				break;

			default:
				break;
			}
			setfillcolor(WHITE);
			solidrectangle(5 * j, 620, 200, 820);
		}


		FlushBatchDraw();
		Sleep(10);
	}
	setfillcolor(BLACK);
	setbkmode(2);
	while (true)
	{
		mousemsg.uMsg = WM_LBUTTONUP;
		setbkcolor(BLACK);
		settextcolor(WHITE);
		if (MouseHit()) mousemsg = GetMouseMsg();
		if (mousemsg.y > 0.9 * windowhigh) {
			setbkcolor(WHITE);
			settextcolor(BLACK);
			if (mousemsg.uMsg == WM_LBUTTONDOWN) {
				for (int j = 0; j < 40; j++) {
					setfillcolor(BLACK);
					solidrectangle(0, 820, 20 * j, 900);
					setfillcolor(WHITE);
					solidrectangle(0, 620, 5 * j, 820);
					FlushBatchDraw();
					Sleep(10);
				}
				break;
			}
		}
		settextstyle(80, 0, _T("�ʲ��鷿"));
		outtextxy(0, 820, _T("������������[�� ��]������������"));
		FlushBatchDraw();
	}
}