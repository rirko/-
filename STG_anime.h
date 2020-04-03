#pragma once
#include <stdio.h>//标准输入输出
#include <stdlib.h>//标准库
#include <conio.h>//键盘交互
#include <math.h>//数学
#include <Windows.h>//系统
#include <string.h>//字符串
#include <atlstr.h>
#include <time.h>
#include <graphics.h>
#include <easyx.h>

#include"STG_io.h"
#include"STG_define.h"
#include"STG_global.h"
#include"STG_thread.h"

void startanime() {
	int i = 0;
	Sleep(1000);
	while (true)
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000))break;//空格跳过
		int ani = 0;
		anime(ani,0);


		if (i == 18) {
			Sleep(3000);
			loadimage(&TITLE[0], _T("image\\title\\title2.png"));

		}
		if (i == 39) {
			putimage(0, 0, &white);
			FlushBatchDraw();
			Sleep(1000);
			video[0].sprite.img[0] = &TITLE[1];
		}
		if (i == 58) {
			Sleep(3000);
			loadimage(&TITLE[1], _T("image\\title\\title4.png"));

		}
		if (i == 76) {
			putimage(0, 0, &white);
			FlushBatchDraw();
			Sleep(500);
			break;
		}
		FlushBatchDraw();
		blanktime();
		i++;

	}
	loadimage(&blood[0], _T("image\\title\\blood.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));
	i = 0;
	srand((unsigned)time(NULL));
	Sleep(100);
	while (true)
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000))break;//空格跳过
		int t = 3;
		while (t-- > 0) {
			int w = rand() % WIDTH - 200;
			int h = rand() % HIGH - 200;
			putimage(w, h, &blood[1], SRCAND);
			putimage(w, h, &blood[0], SRCPAINT);
		}

		if (i > 70 && i < 250) {
			settextstyle(30, 0, _T("问藏书房"));
			outtextxy(rand() % 2, 480+ rand() % 2, _T("“——当医生的大姐姐”"));
		}

		if (i > 120 && i < 250)
			outtextxy(rand() % 2, 510+ rand() % 2, _T("“——你的面具好可怕啊”"));
		if (i > 160 && i < 250)
			outtextxy(rand() % 2, 540+ rand() % 2, _T("“——为什么要戴这么可怕的面具呢？”"));
		if (i > 310 && i < 450)
			outtextxy(rand() % 2, 480+ rand() % 2, _T("......是啊"));
		if (i > 360 && i < 450)
			outtextxy(rand() % 2, 510+ rand() % 2, _T("因为，我希望"));
		if (i > 400 && i < 500)
			outtextxy(rand() % 2, 540+ rand() % 2, _T("往后，不会再有需要后人戴上这个面具的时刻"));
		if (i == 600)break;
		i++;
		FlushBatchDraw();
		blanktime();
	}
	i = 0;
	Sleep(100);
	loadimage(&blood[0], _T("image\\white.png"), 400, 400);
	while (true)
	{
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000))break;//空格跳过
		int t = 3;
		while (t-- > 0) {
			int w = rand() % WIDTH - 200;
			int h = rand() % HIGH - 200;
			putimage(w, h, &blood[0]);
		}

		if (i > 60) {
			settextstyle(300, 0, _T("黑体"));
			setbkmode(OPAQUE);
			settextcolor(WHITE);
			outtextxy(0, 0, _T("虚"));
			outtextxy(350, 0, _T("妄"));
		}	
		if (i > 70) {
			settextstyle(150, 150, _T("问藏书房"));
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			outtextxy(325, 375, _T("与"));
		}		
		if (i > 80) {
			settextstyle(300, 0, _T("黑体"));
			setbkmode(OPAQUE);
			settextcolor(WHITE);
			outtextxy(150, 600, _T("瘟"));
			outtextxy(500, 600, _T("疫"));
		}
		if (i > 90) {
			cleardevice();
			settextstyle(500, 0, _T("黑体"));
			settextcolor(WHITE);
			outtextxy(150, 200, _T("的"));
			FlushBatchDraw();
			break;
		}
		FlushBatchDraw();
		blanktime();
		i++;
	}

	Sleep(1000);
	i = 0;
	putimage(0, 0, &white);
	loadimage(&white, _T("image\\title\\cover.png"));
	loadimage(&blood[1], _T("image\\title\\blood_mask.png"));

	while (true)
	{
		int t = 3;
		while (t-- > 0) {
			int w = rand() % WIDTH - 200;
			int h = rand() % HIGH - 200;
			putimage(w, h, &blood[1], SRCAND);
			putimage(w, h, w, h, &white, 400, 400, SRCPAINT);
		}

		i++;
		if (i == 30)break;
		FlushBatchDraw();
		blanktime();
	}
	i = 0;
	while (true)
	{
		int t = 4;
		while (t-- > 0) {
			int w = rand() % WIDTH - 200;
			int h = rand() % HIGH - 200;
			putimage(w, h, &blood[1], SRCAND);
			putimage(w, h, 400, 400, &white, w, h, SRCPAINT);
		}

		FlushBatchDraw();
		blanktime();
		i++;
		if (i == 90)break;
	}
	putimage(0, 0, &white);
	FlushBatchDraw();
	loadimage(&start[0], _T("image\\title\\start1.png"));
	loadimage(&blood[1], _T("image\\black.png"),400,400);
	i = 0;
	while (true)
	{
		int t = 3;
		while (t-- > 0) {
			int w = (rand() % 500) - 200;
			int h = (rand() % 750) - 200;
			putimage(w, h, &blood[1], SRCAND);
			putimage(w, h, 400, 400, &start[0], w, h, SRCPAINT);
		}

		int w = (rand() % 500) - 200;
		int h = (rand() % 750) - 200;
		putimage(w, h, &blood[1], SRCAND);
		putimage(w, h, 400, 400, &crarcter_doctor[0], w - 70, h - 90, SRCPAINT);
		FlushBatchDraw();
		blanktime();
		i++;
		if (i == 15)break;
	}
	i = 0;
	while (true)
	{
		int t = 5;
		while (t-- > 0) {
			int w = rand() % WIDTH - 200;
			int h = rand() % HIGH - 200;
			putimage(w, h, &blood[1], SRCAND);
			putimage(w, h, w, h, &start[0], 400, 400, SRCPAINT);
		}

		i++;
		if (i == 10)break;
		FlushBatchDraw();
		blanktime();
	}
	putimage(0, 0, &start[0]);
	FlushBatchDraw();
}

void startgame() {
	static int i = 0;
	while (true)
	{
		int t = 0;
		if (MouseHit()) {
			mousemsg = GetMouseMsg();
			if (i == 0 && mousemsg.x > 0.3325 * windowwidth && mousemsg.y > 0.85 * windowhigh
					   && mousemsg.x < 0.679 * windowwidth && mousemsg.y < 0.96 * windowhigh) {
				loadimage(&start[0], _T("image\\title\\start2.png"));
				for (i = 0; i < 30; i++) {

					int t_ = 3;
					while (t_-- > 0) {
						int w = (rand() % 500) - 200;
						int h = (rand() % 750) - 200;
						putimage(w, h, &blood[1], SRCAND);
						putimage(w, h, 400, 400, &start[0], w, h, SRCPAINT);
					}

					int w = (rand() % 500) - 200;
					int h = (rand() % 750) - 200;
					putimage(w, h, &blood[1], SRCAND);
					putimage(w, h, 400, 400, &crarcter_doctor[0], w - 70, h - 90, SRCPAINT);
					FlushBatchDraw();
				}
				i = 1;
			}
			if (i == 1 && (mousemsg.x < 0.3325*windowwidth || mousemsg.y < 0.85*windowhigh
						|| mousemsg.x > 0.679*windowwidth || mousemsg.y > 0.96*windowhigh)) {
				loadimage(&start[0], _T("image\\title\\start1.png"));
				for (i = 0; i < 30; i++) {

					int t_ = 3;
					while (t_-- > 0) {
						int w = (rand() % 500) - 200;
						int h = (rand() % 750) - 200;
						putimage(w, h, &blood[1], SRCAND);
						putimage(w, h, 400, 400, &start[0], w, h, SRCPAINT);
					}

					int w = (rand() % 500) - 200;
					int h = (rand() % 750) - 200;
					putimage(w, h, &blood[1], SRCAND);
					putimage(w, h, 400, 400, &crarcter_doctor[0], w - 70, h - 90, SRCPAINT);
					FlushBatchDraw();
				}
				i = 0;
			}
			if (mousemsg.uMsg == WM_LBUTTONDOWN && i == 1) {
				while (true)
				{
					int t_ = 3;
					while (t_-- > 0) {
						int w = rand() % WIDTH;
						int h = rand() % HIGH;
						line(w, 0, w, 900);
					}

					t++;
					FlushBatchDraw();
					if (t == 400) {
						break;
					}
				}

			}

		}

		if (t == 400)break;
		putimage(0, 0, &start[0]);
		anime_line(DARKGRAY);
		FlushBatchDraw();
		FlushMouseMsgBuffer();
		blanktime();
	}
} 
