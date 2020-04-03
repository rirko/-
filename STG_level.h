#pragma once
#include<easyx.h>
#include<graphics.h>
#include <time.h>
#include"STG_thread.h"
#include"STG_stage.h"
//startup��Ϸ��ʼ��//////////////////////////////////////////////////////////////////////////////////////////////startup��Ϸ��ʼ��
void startup()
{
	QueryPerformanceFrequency(&cpuFreq);//��ȡcpuƵ��

	startup_activate_object();//����ʵ��

	loadimage(&player_picture[0], _T("image\\player.png"));//�������ͼƬ
	loadimage(&player_picture[1], _T("image\\player_mask.png"));//��������ɰ�ͼƬ
	player.sprite.img[0] = &player_picture[0];
	player.sprite.img[1] = &player_picture[1];
	player.sprite.strip = 3;
	player.sprite.speed = 2;
	player.hitbox = 5 - skillnumber[8];
	player.depht = 3;
	player.x = 400;
	player.y = 700;

	loadimage(&judgecircle[0], _T("image\\circle.png"));//�����ж�ȦͼƬ
	loadimage(&judgecircle[1], _T("image\\circle_mask.png"));//�����ж�Ȧ�ɰ�ͼƬspr[0].img[1]
	spr[0].img[0] = &judgecircle[0];
	spr[0].img[1] = &judgecircle[1];
	spr[0].strip = 8;
	spr[0].speed = 2;

	loadimage(&picture[1][0], _T("image\\cross.png"));
	loadimage(&picture[1][1], _T("image\\cross_mask.png"));
	create_object(1, 0, 400, 200, 0, 60, 3, 8);
	mpup = 3;
	stddmgrate = dmgrate;
	BeginBatchDraw();//��ʼ�Կ�����
}

//��ʾ��//////////////////////////////////////////////////////////////////////////////////////////////////////////��ʾ��

void show()
{
	backanime(back[0]);
	//��ʾ����Ȧ������Ȧ
	if (kb_x || mp < maxmp * 0.3) {
		setlinecolor(WHITE);
		if (mp <= 0)setlinecolor(BLUE);
		float mparc = (mp / (float)maxmp) * PI * 2;
		for (int i = 0; i < 10; i++) {
			arc(player.x - 70 - i, player.y - 70 - i, player.x + 70 + i, player.y + 70 + i, 0.5 * PI, mparc + 0.5 * PI);
		}
	}
	if (kb_x || hp < maxhp * 0.6 || hp < hpup) {
		setlinecolor(LIGHTGREEN);
		if (hpup > hp)setlinecolor(RED);
		float hparc = (hp / (float)maxhp) * PI * 2;
		for (int i = 0; i < 10; i++) {
			arc(player.x - 80 - i, player.y - 80 - i, player.x + 80 + i, player.y + 80 + i, 0.5 * PI, hparc + 0.5 * PI);
		}
	}
	if (kb_shift == 1)	animesprite(0, player.x, player.y);//��ʾ��תȦ
	settextstyle(30, 0, _T("�ʲ��鷿"));//��ʾ�з�λ��
	setbkcolor(RED);
	setbkmode(OPAQUE);
	settextcolor(WHITE);
	outtextxy(object[1].x - 40, 870, _T("ENEMY"));
	imageFresh();//ˢ����ͼλ��
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	if (kb_x) {
		setlinecolor(YELLOW);
		circle(player.x, player.y, 100 - cutclock);
	}
	if (kb_shift == 1)	fillcircle(player.x, player.y, player.hitbox+1);//��ʾ�ж���


	setfillcolor(BLACK);//��ʾѪ����ui
	solidroundrect(60, 10, maxhp + 60, 20, 5, 5);
	solidrectangle(maxhp + 60, 13, maxhp + 95, 17);
	solidroundrect(60, 25, maxmp + 60, 35, 5, 5);
	solidrectangle(maxmp + 60, 28, maxmp + 95, 32);
	setfillcolor(RED);
	solidroundrect(60, 12, 60 + hpup, 18, 5, 5);
	if (hp < hpup && hpclock < 0) {
		setfillcolor(WHITE);
		solidroundrect(60, 12, 60 + hpup, 18, 5, 5);
	}
	setfillcolor(LIGHTGREEN);
	solidroundrect(60, 12, 60 + hp, 18, 5, 5);
	setfillcolor(YELLOW);
	solidroundrect(60, 27, 60 + mp, 33, 5, 5);
	setfillcolor(BLACK);
	solidcircle(30, 30, 30);
	setfillcolor(RED);
	solidpie(5, 5, 55, 55, PI / 2, PI / 2 - (1 - leveltime / 21600) * 2 * PI);
	setfillcolor(BLACK);
	solidcircle(30, 30, 15);



	if (qte > 0) {//qteȦ
		settextstyle(15, 0, _T("����"));
		settextcolor(YELLOW);
		setbkcolor(LIGHTMAGENTA);
		setbkmode(OPAQUE);
		if (lt % 2 == 1)outtextxy(player.x - 65, player.y + 60, _T("Intensify Chance"));
		setlinecolor(RED);
		for (int i = 0; i < 10; i++) {
			arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qte) * PI / 180, 1.5 * PI);
		}
		setlinecolor(GREEN);
		if (qte > qterand[0] && qte <= qterand[0] + 45)
			for (int i = 0; i < 10; i++)
				arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qte) * PI / 180, (270 - qterand[0]) * PI / 180);

		if (qte > qterand[0] && qte > qterand[0] + 45)
			for (int i = 0; i < 10; i++)
				arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qterand[0] - 45) * PI / 180, (270 - qterand[0]) * PI / 180);

		setlinecolor(YELLOW);
		if (qte > qterand[1] && qte <= qterand[1] + 45)
			for (int i = 0; i < 10; i++)
				arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qte) * PI / 180, (270 - qterand[1]) * PI / 180);

		if (qte > qterand[1] && qte > qterand[1] + 45)
			for (int i = 0; i < 10; i++)
				arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qterand[1] - 45) * PI / 180, (270 - qterand[1]) * PI / 180);

	}


	if (//��ʾbreak����
		(lt > 25 && lt < 30) ||
		(lt > 65 && lt < 70) ||
		(lt > 100 && lt < 105) ||
		(lt > 155 && lt < 160) ||
		(lt > 230 && lt < 245) ||
		(lt > 270 && lt < 280)) {
		settextstyle(20, 0, _T("����"));
		settextcolor(GREEN);
		setbkcolor(BLACK);
		setbkmode(OPAQUE);
		outtextxy(0, 60, _T("OPERATION BREAK"));
	};
	//datawindow();
	if (leveltime <= 0)showscore();
}
//����Ҳ����޹صĸ��� ֡ǰ///////////////////////////////////////////////////////////////////////////////////////����Ҳ����޹صĸ��� ֡ǰ
void updateWithoutInput_before()
{
	if (mp < maxmp)mp = mp + mpup;//�����������ظ�
	if (mp > maxmp)mp = maxmp;//�����������ظ�
	if (hp < hpup && hpclock < 0)hp++;

	if (cutrush>0) {
//		setlinecolor(LIGHTRED);
//		line(player.x, player.y + 60 - cutrush, player.x, player.y);
//		FlushBatchDraw();
		player.y -= 20;
		if (cutrush < 2)dmgrate = stddmgrate;
	}
	//static int i = 0;if (i == 0) { create_bullet(3 , 10, 400, 450, 90, 20, 4, RED); i = 10; }i--;
	Clock();

}
//����Ҳ����йصĸ���////////////////////////////////////////////////////////////////////////////////////////////����Ҳ����йصĸ���
void updateWithInput()
{
	keyboard();//����

	if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) || (GetAsyncKeyState(VK_LBUTTON) & 0x8000))pausetime();
	player_move();//����ƶ�����������
	if (kb_shift == 1 && mp > 10)mp = mp - 2;
	if (kb_space == 1 && player.x < 0) {
		player.x = WIDTH;
		mp = mp - 100;
	}
	if (kb_space == 1 && player.x > WIDTH) {
		player.x = 0;
		mp = mp - 100;
	}

	if (kb_z == 1 && shootclock < 0&&!kb_x) {//�����ӵ�
		mp = mp - 20;
		if (kb_shift) {
			int ang = atan((object[1].y - player.y) / (object[1].x - player.x)) * 180 / PI;
			if ((object[1].x - player.x) < 0)ang = ang + 180;
			create_bullet(-1, 40, player.x - 20, player.y, ang, 20, 2, WHITE, 0);
			create_bullet(-1, 40, player.x + 20, player.y, ang, 20, 2, WHITE, 0);
		}
		else {
			create_bullet(-1, 40, player.x + 30, player.y, 270, 10, 2, WHITE, 0);
			create_bullet(-1, 40, player.x - 30, player.y, 270, 10, 2, WHITE, 0);
			int ang = atan((object[1].y - player.y) / (object[1].x - player.x + 50)) * 180 / PI;
			if ((object[1].x - player.x + 50) < 0)ang = ang + 180;
			create_bullet(-1, 40, player.x - 50, player.y, ang, 20, 2, WHITE, 0);

			ang = atan((object[1].y - player.y) / (object[1].x - player.x - 50)) * 180 / PI;
			if ((object[1].x - player.x - 50) < 0)ang = ang + 180;
			create_bullet(-1, 40, player.x + 50, player.y, ang, 20, 2, WHITE, 0);
		}
		shootclock = 10;
		if (skillnumber[5] && hp < hpup)shootclock = 5;
	}

	if (qte > qterand[0] && qte < (qterand[0] + 45) && kb_space) {//qte����
		hpup = maxhp;
		qte = 0;
		score += 1000;
	}
	if (qte > qterand[1] && qte < (qterand[1] + 45) && kb_space) {
		mpup++;
		qte = 0;
		score += 1000;
	}
	if (qte > 0 && qte < 360 && kb_space) {
		qte = 0;
		score += 500;
	}

	if (kb_x) {
		//setlinecolor(YELLOW);
		//circle(player.x, player.y, 60 - cutclock);
		//FlushBatchDraw();
		if (cutclock < 60) {
			cutclock+=2;
		}
		if (kb_z && cutclock >= 60) {
			cutclock = 0;
			cutrush = 5;
			dmgrate = 0.1;
		}
	}
}

//����Ҳ����޹صĸ��� ֡��////////////////////////////////////////////////////////////////////////////////////////����Ҳ����޹صĸ��� ֡��
void updateWithoutInput_after()
{
	if (skillnumber[6]) {
		static int countdown = 15;
		if (countdown < 0 && hp < maxhp) {
			hp++;
			countdown = 15;
		}
		countdown--;
	}

	if (qte > 0)qte--;
	if (player.x < 0)player.x = 0;//��ֹ��ҳ���
	if (player.y < 0)player.y = 0;
	if (player.x > WIDTH)player.x = WIDTH;
	if (player.y > HIGH)player.y = HIGH;

	Vmove();//���ٶ�Ӱ���µ�λ��

	hitcheck();//��ײ���

	int i;//�ӵ�ʱ���ж�
	for (i = 0; i <= bulno; i++) {
		if (bullet[i].clock[1] == 0) {
			int ang = atan((player.y - bullet[i].y) / (player.x - bullet[i].x)) * 180 / PI;
			if ((player.x - bullet[i].x) < 0)ang = ang + 180;
			velocity_bul(i, bullet[i].velocity, ang);
		}
		if (bullet[i].clock[2] == 0) {
			velocity_bul(i, bullet[i].velocity + bullet[i].tempdate /*+2*/, bullet[i].Vangle + 90);
		}
		if (bullet[i].clock[3] == 0) {
			velocity_bul(i, bullet[i].velocity + bullet[i].tempdate /** 0.5*/, bullet[i].Vangle - 90);
		}
		if (bullet[i].clock[4] == 0) {
			velocity_bul(i, bullet[i].velocity + bullet[i].tempdate /** 0.5*/, bullet[i].Vangle + 90);
		}
		if (bullet[i].clock[5] == 0) {
			velocity_bul(i, bullet[i].velocity + bullet[i].tempdate/*+1*/, bullet[i].Vangle);
		}
	}

	auto_destory();//����ɾ����Ʒ

	FlushBatchDraw();//�Կ���������
	keyboard_release();//�ͷż��̱���
	blanktime();//��֡
}



//�رճ���
void endoff()
{

	EndBatchDraw();//��ֹ�Կ�����
}



void level1() {
	leveljumpout = 0;
	while (true)
	{
		if (leveljumpout == 1)break;
		loadimage(&back[0], _T("image\\background\\1.png"));//���ر���ͼƬ
		nowtime = time(NULL);
		int deadkill = 1;
		standmpup = 3;
		hp = maxhp;
		mp = maxmp;
		int i = 0;
		int t = 0;
		qte = 0;
		qterand[0] = rand() % 135;
		qterand[1] = 180 + rand() % 135;
		(float)lt;
		leveltime = 7200;
		fps = 60;
		startup();
		object[1].y = -100;
		while (true)
		{
			if (leveljumpout == 1)break;
			lt = 7200 / fps - leveltime / fps;
			if (leveltime == 7000) {
				setbkcolor(WHITE);
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���������侲�������ͺ�����һ���Ϳ�����"));
				dialogue(crarcter_doctor, _T("�����¿����ȣ����������׵ģ���˹����Ƥ��˹���ˣ�ֻ����εĻ����ǡ���"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�����ý��ţ����ҵ�Э���£����еĲ�ħ�����ع��ڹ�����"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹����ֻҪ������һ���Ի��߽��������Ϳ�����"));
				dialogue(crarcter_doctor, _T("�����¿����ȣ��ţ���֪����"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹����Ӧ�üǵã��á�����������������ڿռ��е�ͶӰ"));
			}
			if (leveltime == 6900) {
				settextcolor(BLACK);
				settextstyle(60, 50, _T("�ʲ��鷿"));
				setbkmode(TRANSPARENT);
				outtextxy(90, 450, _T("���·�����Ե���ͶӰλ��"));
				FlushBatchDraw();
				while (true)if (
					(GetAsyncKeyState(VK_UP) & 0x8000) ||
					(GetAsyncKeyState(VK_DOWN) & 0x8000) ||
					(GetAsyncKeyState(VK_LEFT) & 0x8000) ||
					(GetAsyncKeyState(VK_RIGHT) & 0x8000)
					)break;
			}
			if (leveltime == 6800) {
				setbkcolor(WHITE);
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���ܺã�����ȥ���Ѿ��һظо���"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�����ڿ�ʼ�Ի������ϵ����߽���ӳ�䣬׼��������"));
				dialogue(crarcter_doctor, _T("�����¿����ȣ�����Ӧ�ÿ�����"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���ã�ͶӰ��ʼ"));
			}
			if (lt > 6 && lt < 13)object[1].y++;
			if (leveltime == 6500) {
				setbkcolor(WHITE);
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹��ע�⣬�����߷�������ʱ"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�����ߵ�ͶӰҲ�����ڱ���Ĳ�������ɢ����Ļ״�Ĺ���"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���������л����ͻ��ߵ�������ȫ���Σ����ע����"));
			}
			if (lt > 13 && lt < 20) {
				if ((int)leveltime % 20 == 1) {
					create_bullet(5, 5, object[1].x, object[1].y, 30, 10, 5, BLACK, lt);
					create_bullet(5, 5, object[1].x, object[1].y, 150, 10, 5, BLACK, lt);
					setclock(lt, 1, 50,0);
				}
			}
			if (leveltime == 5900) {
				setbkcolor(WHITE);
				dialogue(crarcter_doctor, _T("�����¿����ȣ�Ψ�����"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���ܺ�"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���Է����ܻ���д��ܶȵĵ�Ļ����"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹����Ҫʱ�̲�Ҫ��������ֵ�����¡�shift�����뾫ϸģʽ"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�������������������������������ʱ����������"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�����¡�X�������Խ�����۲�����������������"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹����ע�⣬�۲��ʱ�򲻿����ƶ��͹���"));

			}
			if (lt > 25 && lt < 40) {
				if ((int)leveltime % 20 == 0) {
					for (float i = 0.5; i < 1; i += 0.2) {
						t = t + 17;
						create_bullet(0, i, object[1].x, object[1].y, t, 10, 5, WHITE, 0);
						create_bullet(0, i, object[1].x, object[1].y, t + 60, 10, 5, WHITE, 0);
						create_bullet(0, i, object[1].x, object[1].y, t + 120, 10, 5, WHITE, 0);
					}
				}
			}
			if (lt == 50) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (leveltime == 4140) {
				setbkcolor(WHITE);
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹����ǿ�����ᣡ����ס����Ҫ���"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹��ע��۲�Է���Χ���Ƕ�Բ��"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹����Բ���ߵ������λ��ʱ���¡��ո�������Ի����Ӧ��ǿ��"));
				if (hp == maxhp) {
					dialogue(crarcter_kami, _T("��˹����Ƥ��˹����Բ���ߵ���ɫ��λ��ʱ���¿ո�"));
					dialogue(crarcter_kami, _T("��˹����Ƥ��˹���㽫��á��������ٻظ�����ǿ����ֱ����һ��ǿ������"));
					dialogue(crarcter_kami, _T("��˹����Ƥ��˹����ɫ��λ���ǡ��ظ���������ֵ����ǿ��"));
					dialogue(crarcter_kami, _T("��˹����Ƥ��˹����������ȥ��û�б�Ҫ��Ц��"));
				}
				else {
					dialogue(crarcter_kami, _T("��˹����Ƥ��˹����Բ���ߵ���ɫ��λ��ʱ���¿ո�"));
					dialogue(crarcter_kami, _T("��˹����Ƥ��˹���㽫��á��ظ���������ֵ����ǿ�������Բ���֮ǰ����ʧ"));
					dialogue(crarcter_kami, _T("��˹����Ƥ��˹��˳��һ�ᣬ��ɫ��λ���ǡ��������ٻظ�����ǿ��"));
					dialogue(crarcter_kami, _T("��˹����Ƥ��˹��ѡ����һ��Ҫƾ���Լ�Ȩ��������"));
				}
				Sleep(200);

			}
			if (leveltime == 3600) {
				setbkcolor(WHITE);
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�����ո��������֮ǰ˵��������;��"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�������������ڿռ�ı�Ե���д���"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�������ڿռ������߻����ұ�ʱ������������Ҽ���ͬʱ���¿ո��"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���Ϳ��Դ�����һ�ߵı߽�"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹������ٴ���������������Ҫע��Ŷ"));
			}

			if (lt > 60 && lt < 75)
			{
				object[1].x = player.x;
				if ((int)leveltime % 10 == 0)create_bullet(1, 6, object[1].x, object[1].y, 90, 15, 5, YELLOW, 0);
			}
			if (leveltime == 2400) {
				object[1].x = 400;
				setbkcolor(WHITE);
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���ڶ�ܵ�ͬʱ������ҲҪ���з���"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�����¡�Z�������ٶ����߽����߽�"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�����ߵ��߽�ȻᷴӦ�����Ͻǵ�Բ����"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���������߱����߽⣬Բ���ĺ�ɫ���ֽ�������"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹������ɫ������ʧʱ��������ȫ�߽�"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹����Ȼ�����������߽���Ҫ����������"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹����ˣ�������������Ļ����Ͱ��Ķ㵯Ļ�ɣ�"));
			}
			if (leveltime > 2300)shootclock = 10;
			if (leveltime == 2300) {
				settextcolor(BLACK);
				settextstyle(60, 50, _T("�ʲ��鷿"));
				setbkmode(TRANSPARENT);
				outtextxy(110, 450, _T("���¡�Z�����Է����ӵ�"));
				FlushBatchDraw();
				while (true)if (
					(GetAsyncKeyState(0x5a) & 0x8000))break;
			}
			if (lt == 85) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 90 && lt < 120) {
				if ((int)leveltime % 40 == 0) {
					create_bullet(5, 3, object[1].x, object[1].y, 30, 5, 5, LIGHTRED, lt);
					create_bullet(5, 3, object[1].x, object[1].y, 150, 5, 5, LIGHTRED, lt);
					setclock(lt, 1, 50,0);
				}
				if ((int)leveltime % 40 == 10) {
					create_bullet(5, 3, object[1].x, object[1].y, 45, 5, 5, LIGHTRED, lt);
					create_bullet(5, 3, object[1].x, object[1].y, 135, 5, 5, LIGHTRED, lt);
					setclock(lt, 1, 50,0);
				}
				if ((int)leveltime % 40 == 20) {
					create_bullet(5, 3, object[1].x, object[1].y, 15, 5, 5, LIGHTRED, lt);
					create_bullet(5, 3, object[1].x, object[1].y, 165, 5, 5, LIGHTRED, lt);
					setclock(lt, 1, 50,0);
				}
				if ((int)leveltime % 40 == 30) {
					create_bullet(5, 3, object[1].x, object[1].y, 0, 5, 5, LIGHTRED, lt);
					create_bullet(5, 3, object[1].x, object[1].y, 180, 5, 5, LIGHTRED, lt);
					setclock(lt, 1, 50,0);
				}
				if (lt > 105) {

					if ((int)leveltime % 20 == 0) {
						for (float i = 0.5; i < 1; i += 0.2) {
							t = t + 17;
							create_bullet(0, i, object[1].x, object[1].y, t, 10, 5, WHITE, 0);
							create_bullet(0, i, object[1].x, object[1].y, t + 60, 10, 5, WHITE, 0);
							create_bullet(0, i, object[1].x, object[1].y, t + 120, 10, 5, WHITE, 0);
						}
					}
				}
			}

			if (hp <= 0 && deadkill) {
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹��Σ�գ���������������½������������ˣ�"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹����������һ������ʧ��� Ψһһ�� ��Ȼ��ᣡ"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���ڱ����е�һ˲�䰴�¡��ո�������㽫��һ������ֵ��״̬����"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�����ң���ᴦ�������ظ��ٶ��½����쳣״̬"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹�����ܱ��������ºã�������"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹��Ҫ��ʲôʱ�����¿ո����Ҫ����˵�Ļ�����"));
				dialogue(crarcter_kami, _T("��˹����Ƥ��˹���������ڣ�����"));
				for (int i = 0; i < 40; i++) {
					setlinecolor(BLACK);
					for (int t = 0; t < 45; t++)circle(player.x, player.y, 900 - (i * 45 + t));
					if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
						standmpup = 2;
						mpup = standmpup;
						hp = maxhp / 2;
						deadkill = 0;
						for (int i = 0; i <= bulno; )
							destory(bullet[i]);
						setlinecolor(WHITE);
						for (int i = 0; i < 20; i++) {
							for (int t = 0; t < 45; t++)circle(player.x, player.y, i * 45 + t);
							FlushBatchDraw();
							blanktime();
						}
						break;
					}
					FlushBatchDraw();
					blanktime();
				}
			}

			if (hp <= 0) {
				setlinecolor(BLACK);
				destory(object[1]);
				for (i = 0; i <= bulno; )
					destory(bullet[i]);
				for (i = 0; i < 900; i++) {
					circle(player.x, player.y, i);
					FlushBatchDraw();
				}
				dialogue_lost();
				break;
			}
			if (leveltime <= 0 && leveltime > -60) {
				setlinecolor(WHITE);
				for (i = 0; i < 900; i++) {
					circle(object[1].x, object[1].y, i);
					FlushBatchDraw();
					leveltime = -60;
				}
				destory(object[1]);
				for (i = 0; i <= bulno; )
					destory(bullet[i]);
				lasttime = time(NULL) - nowtime;
			}
			updateWithoutInput_before();
			updateWithInput();
			show();
			updateWithoutInput_after();
			leveltime--;

		}
	}
}

void level2() {
	leveljumpout = 0;
	while (true)
	{
		if (leveljumpout == 1)break;
		loadimage(&back[0], _T("image\\background\\2.png"));//���ر���ͼƬ
		nowtime = time(NULL);
		int deadkill = 1;
		standmpup = 3;
		hp = maxhp;
		mp = maxmp;
		int i = 0;
		int t = 0;
		qte = 0;
		qterand[0] = rand() % 135;
		qterand[1] = 180 + rand() % 135;
		(float)lt;
		leveltime = 21600;
		fps = 60;
		startup();
		object[1].y = -100;
		while (true)
		{
			if (leveljumpout == 1)break;
			lt = 21600 / fps - leveltime / fps;
			if (lt < 25) {
				if (object[1].y < 200)object[1].y++;
				if ((int)leveltime % 10 == 1) {
					t = t + 50;
					create_bullet(0, 3, object[1].x, object[1].y, t, 10, 5, WHITE, 0);
					create_bullet(0, 2, object[1].x, object[1].y, t + 120, 10, 5, WHITE, 0);
					create_bullet(0, 1, object[1].x, object[1].y, t + 240, 10, 5, WHITE, 0);
				}

				if ((int)leveltime % 240 == 1) {
					for (i = 0; i < 30; i++)
						create_bullet(5, 5, object[1].x, object[1].y, i * 12, 10, 5, RED, lt);
					setclock(lt, 1, 50,0);
				}
			}
			if (lt == 25) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 30 && lt < 65) {
				if ((int)leveltime % 90 == 1) {
					t = t + lt;
					for (i = 0; i < 30; i++)
						create_bullet(0, 1, object[1].x, object[1].y, i * 12 + t, 10, 5, YELLOW, 0);
				}
			}
			if (lt == 65) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 70 && lt < 100) {
				if ((int)leveltime % 10 == 1) {
					t = t + 50;
					create_bullet(0, 4, object[1].x - 100, object[1].y, t, 10, 5, WHITE, 0);
					create_bullet(0, 4, object[1].x - 100, object[1].y, t + 120, 10, 5, WHITE, 0);
					create_bullet(0, 4, object[1].x - 100, object[1].y, t + 240, 10, 5, WHITE, 0);
					create_bullet(0, 4, object[1].x + 100, object[1].y, -t - 180, 10, 5, WHITE, 0);
					create_bullet(0, 4, object[1].x + 100, object[1].y, -t - 300, 10, 5, WHITE, 0);
					create_bullet(0, 4, object[1].x + 100, object[1].y, -t - 420, 10, 5, WHITE, 0);
				}

				if ((int)leveltime % 240 == 1) {
					for (i = 0; i < 30; i++)
						create_bullet(5, 5, object[1].x, object[1].y, i * 12, 10, 5, RED, lt);
					setclock(lt, 1, 50,0);
				}
			}

			if (lt == 100) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 105 && lt < 155) {
				if ((int)leveltime % 10 == 1) {
					t = t + 50;
					create_bullet(0, 2, object[1].x - 100, object[1].y, t, 8, 5, WHITE, lt);
					create_bullet(0, 2, object[1].x - 100, object[1].y, t + 120, 8, 5, WHITE, lt);
					create_bullet(0, 2, object[1].x - 100, object[1].y, t + 240, 8, 5, WHITE, lt);
					create_bullet(0, 2, object[1].x + 100, object[1].y, -t - 180, 8, 5, BLACK, lt);
					create_bullet(0, 2, object[1].x + 100, object[1].y, -t - 300, 8, 5, BLACK, lt);
					create_bullet(0, 2, object[1].x + 100, object[1].y, -t - 420, 8, 5, BLACK, lt);
				}
				if (lt > 105 && lt < 110 && object[1].x>40)object[1].x = object[1].x - 2;
				if (lt > 110 && lt < 120 && object[1].x < 760)object[1].x = object[1].x + 2;
				if (lt > 120 && lt < 125 && object[1].x>40)object[1].x = object[1].x - 4;
				if (lt > 125 && lt < 130 && object[1].x < 760)object[1].x = object[1].x + 4;
				if (lt > 130 && lt < 135 && object[1].x > 40)object[1].x = object[1].x - 8;
				if (lt > 135 && lt < 140 && object[1].x < 760)object[1].x = object[1].x + 8;
				if (lt > 140 && object[1].x != 400)object[1].x = object[1].x--;
			}
			if (lt == 155) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 160 && lt < 165) {
				if (object[1].x < player.x)object[1].x = object[1].x + 5;
				if (object[1].x > player.x)object[1].x = object[1].x - 5;
				if (object[1].y < 900)object[1].y = object[1].y + 15;
			}
			if (lt > 165 && lt < 230) {
				object[1].y = 900;
				object[1].x = player.x;
				if ((int)leveltime % 20 == 1) {
					create_bullet(0, 2, object[1].x, object[1].y, 270, 5, 5, WHITE, 0);
					create_bullet(0, 2, object[1].x, object[1].y, 300, 5, 5, WHITE, 0);
					create_bullet(0, 2, object[1].x, object[1].y, 240, 5, 5, WHITE, 0);
				}
				if ((int)leveltime % 120 == 1) {
					for (i = 0; i < 20; i++)
						create_bullet(0, 3, object[1].x, 0, i * 18, 10, 5, YELLOW, lt);
					setclock(lt, 1, 100,0);
				}
			}
			if (lt == 230) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 230 && lt < 245) {
				if (object[1].x < 400)object[1].x = object[1].x++;
				if (object[1].x > 400)object[1].x = object[1].x--;
				if (object[1].y > 200)object[1].y = object[1].y--;
			}
			if (lt > 245 && lt < 270) {
				if ((int)leveltime % 90 == 1) {
					t = t + lt;
					for (i = 0; i < 30; i++)
						create_bullet(0, 1, object[1].x, object[1].y, i * 12 + t, 10, 5, YELLOW, 0);
				}
			}
			if (lt == 270) {
				i = 0;
				t = 0;
			}
			if (lt > 280 && lt < 305) {
				if ((int)leveltime % 5 == 1) {
					t = t + 7;
					create_bullet(0, 2, object[1].x, object[1].y, t, 10, 5, LIGHTRED, lt);
					create_bullet(0, 2, object[1].x, object[1].y, t - 180, 10, 5, YELLOW, lt);
				}
			}
			if (lt > 310 && lt < 330) {
				if ((int)leveltime % 5 == 1) {
					t = t - 17;
					create_bullet(0, 3, object[1].x, object[1].y, t, 10, 5, LIGHTRED, lt);
					create_bullet(0, 3, object[1].x, object[1].y, t + 180, 10, 5, LIGHTRED, lt);
					create_bullet(0, 3, object[1].x, object[1].y, -t - 180, 10, 5, YELLOW, lt);
					create_bullet(0, 3, object[1].x, object[1].y, -t, 10, 5, YELLOW, lt);
				}
			}
			if (lt > 330 && lt < 360) {
				if ((int)leveltime % 5 == 1) {
					t = t + 17;
					create_bullet(0, 4, object[1].x, object[1].y, t, 10, 5, LIGHTRED, lt);
					create_bullet(0, 4, object[1].x, object[1].y, t + 120, 10, 5, LIGHTRED, lt);
					create_bullet(0, 4, object[1].x, object[1].y, t + 240, 10, 5, LIGHTRED, lt);
					create_bullet(0, 4, object[1].x, object[1].y, -t - 180, 10, 5, YELLOW, lt);
					create_bullet(0, 4, object[1].x, object[1].y, -t - 300, 10, 5, YELLOW, lt);
					create_bullet(0, 4, object[1].x, object[1].y, -t - 420, 10, 5, YELLOW, lt);
				}
			}

			if (leveltime <= 0 && leveltime > -60) {
				setlinecolor(WHITE);
				for (i = 0; i < 900; i++) {
					circle(object[1].x, object[1].y, i);
					FlushBatchDraw();
					leveltime = -60;
				}
				destory(object[1]);
				for (i = 0; i <= bulno; )
					destory(bullet[i]);
				lasttime = time(NULL) - nowtime;
			}


			if (hp <= 0 && deadkill) {
				for (int i = 0; i < 20; i++) {
					setlinecolor(BLACK);
					for (int t = 0; t < 45; t++)circle(player.x, player.y, 900 - (i * 45 + t));
					if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
						standmpup = 2;
						mpup = standmpup;
						hp = maxhp / 2;
						deadkill = 0;
						for (int i = 0; i <= bulno; )
							destory(bullet[i]);
						setlinecolor(WHITE);
						for (int i = 0; i < 20; i++) {
							for (int t = 0; t < 45; t++)circle(player.x, player.y, i * 45 + t);
							FlushBatchDraw();
							blanktime();
						}
						break;
					}
					FlushBatchDraw();
					blanktime();
				}
			}if (hp <= 0) {
				setlinecolor(BLACK);
				destory(object[1]);
				for (i = 0; i <= bulno; )
					destory(bullet[i]);
				for (i = 0; i < 900; i++) {
					circle(player.x, player.y, i);
					FlushBatchDraw();
				}
				dialogue_lost();
				break;
			}
			updateWithoutInput_before();
			updateWithInput();
			show();
			updateWithoutInput_after();
			//Sleep(10000);
			leveltime--;

		}
	}
}

void level3() {
	leveljumpout = 0;
	while (true)
	{
		if (leveljumpout == 1)break;
		loadimage(&back[0], _T("image\\background\\3.png"));//���ر���ͼƬ
		nowtime = time(NULL);
		int deadkill = 1;
		standmpup = 3;
		hp = maxhp;
		mp = maxmp;
		int i = 0;
		int t = 0;
		qte = 0;
		qterand[0] = rand() % 135;
		qterand[1] = 180 + rand() % 135;
		(float)lt;
		leveltime = 21600;
		fps = 60;
		startup();
		object[1].y = -100;
		while (true)
		{
			if (leveljumpout == 1)break;
			lt = 21600 / fps - leveltime / fps;
			
			if (lt < 25) {
				if (object[1].y < 200)object[1].y++;
				if (lt > 5) {
					if ((int)leveltime % 10 == 1) {
						t += 17;
						for (i = 0; i < 8; i++)
							create_bullet(5, 2, object[1].x, object[1].y, t + i * 48, 10, 5, LIGHTGREEN, lt);
						setclock(lt, 3, 50,-1);
						for (i = 0; i < 8; i++)
							create_bullet(5, 2, object[1].x, object[1].y, t - i * 48, 10, 5, LIGHTBLUE, -lt);
						setclock(-lt, 2, 50,+2);
					}
				}
			}
			if (lt == 25) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 35 && lt < 80) {
				if ((int)leveltime % 13 == 0) {
					t += lt * 5;
					for (i = 0; i < 15; i++) {
						create_bullet(0, 3, object[1].x, object[1].y, t + i * 24, 7, 5, YELLOW, 0);
						create_bullet(0, 3, object[1].x, object[1].y, -t - i * 24, 7, 5, YELLOW, 0);
					}
				}
			}
			if (lt > 50 && lt < 80) {
				if ((int)leveltime % 5 == 0) {
					if ((int)leveltime % 10 == 1) {
						t += 17;
						for (i = 0; i < 8; i++)
							create_bullet(5, 4, object[1].x, object[1].y, t + i * 48, 10, 5, LIGHTGREEN, leveltime);
						setclock(leveltime, 3, 50,-2);
					}
				}
			}
			if (lt == 80) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 90 && lt < 120) {
				if (object[1].y < 450)object[1].y++;
				if ((int)leveltime % 1 == 0) {
					setlinecolor(WHITE);
					circle(player.x, player.y, 200);
					FlushBatchDraw();
					i += 2;
					int x, y;
					x = 200 * cos(i) + player.x;
					y = 200 * sin(i) + player.y;
					int ang = atan((player.y - y) / (player.x - x)) * 180 / PI;
					if ((player.x - x) < 0)ang = ang + 180;
					create_bullet(3, 3, x, y, ang + 60 * (sin(lt) + 1.2), 10, 5, 0xfffa57, 0);

				}
				if ((int)leveltime % 20) {
					for (int t = 0; t < 3; t++) {
						create_bullet(5, 20, object[1].x, object[1].y, t * 120 + leveltime / 4, 20, 5, LIGHTBLUE + leveltime / 4, 0);

					}
				}
			}
			if (lt == 120) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt >= 130 && lt < 160) {

				if ((int)leveltime % 1 == 0) {
					setlinecolor(WHITE);
					circle(player.x, player.y, 200);
					FlushBatchDraw();
					i += 1;
					int x, y;
					x = 200 * cos(i) + player.x;
					y = 200 * sin(i) + player.y;
					int ang = atan((player.y - y) / (player.x - x)) * 180 / PI;
					if ((player.x - x) < 0)ang = ang + 180;
					create_bullet(5, 3, x, y, ang + 60 * (sin(lt) + 1.2), 10, 5, 0xfffa57, 0);

				}
				if ((int)leveltime % 20) {
					for (int t = 0; t < 3; t++) {
						create_bullet(5, 20, object[1].x, object[1].y, t * 120 + leveltime / 3.5, 20, 5, LIGHTBLUE + leveltime / 4, 0);

					}
				}
			}
			if (lt == 160) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt == 170) {
				object[1].velocity = 2;
				object[1].Vangle = 45;
			}
			if (lt > 170 && lt < 210) {
				setlinecolor(WHITE);
				circle(object[1].x, object[1].y, 200);
				FlushBatchDraw();
				if (object[1].x >= 800) {
					object[1].x = 800;
					if ((int)object[1].Vangle % 360 < 180)
						object[1].Vangle += 90;
					else
						object[1].Vangle += 270;
				}
				if (object[1].x <= 0) {
					object[1].x <= 0;
					if ((int)object[1].Vangle % 360 > 180)
						object[1].Vangle += 90;
					else
						object[1].Vangle += 270;
				}
				if (object[1].y >= 900) {
					object[1].y = 900;
					if ((int)object[1].Vangle % 360 > 90)
						object[1].Vangle += 90;
					else
						object[1].Vangle += 270;
				}
				if (object[1].y <= 0) {
					object[1].y <= 0;
					if ((int)object[1].Vangle % 360 > 270)
						object[1].Vangle += 90;
					else
						object[1].Vangle += 270;
				}
				if ((int)leveltime % 1 == 0) {
					i += 1;
					int x, y;
					x = 200 * cos(i) + object[1].x;
					y = 200 * sin(i) + object[1].y;
					int ang = atan((object[1].y - y) / (object[1].x - x)) * 180 / PI;
					if ((object[1].x - x) < 0)ang = ang + 180;
					create_bullet(5, 3, x, y, ang + 60 * (sin(lt) + 0.5), 10, 5, WHITE, 0);

				}
			}
			if (lt == 210) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
				object[1].velocity = 0;
			}
			if (lt > 210 && lt < 225) {
				if (object[1].x < 400)object[1].x = object[1].x++;
				if (object[1].x > 400)object[1].x = object[1].x--;
				if (object[1].y > 200)object[1].y = object[1].y--;
				if (object[1].y < 200)object[1].y = object[1].y++;
			}
			if (lt > 220 && lt < 260) {
				if ((int)leveltime % 15 == 1) {
					t += 7;
					for (i = 0; i < 20; i++)
						create_bullet(0, 4 + (lt - 220) / 10, object[1].x, object[1].y, t + i * 18, 10, 5, LIGHTGREEN - (lt - 220) * 10, 0);
				}
			}
			if (lt > 270 && lt < 310) {
				if (object[1].y < 200)object[1].y++;
				if ((int)leveltime % 30 == 1) {
					t += 20;
					for (i = 0; i < 30; i++)
						create_bullet(5, 6, object[1].x, object[1].y, t + i * 12, 7, 5, WHITE, leveltime);
					setclock(leveltime, 3, 20,-3);
					for (i = 0; i < 30; i++)
						create_bullet(5, 6, object[1].x, object[1].y, -t - i * 12, 7, 5, WHITE, -leveltime);
					setclock(-leveltime, 4, 20,-3);
				}
			}
			if (lt == 310) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 320 && lt < 360) {
				if (object[1].y < 200)object[1].y++;
				if ((int)leveltime % 60 == 1) {
					t += 20;
					for (i = 0; i < 30; i++) {
						create_bullet(5, 4, 0, 900, t + i * 12, 7, 5, WHITE, leveltime);
						create_bullet(5, 4, 800,900, t + i * 12, 7, 5, WHITE, leveltime);
					}
					setclock(leveltime, 3, 20,-2);
					for (i = 0; i < 30; i++) {
						create_bullet(5, 4, 0, 900, -t - i * 12, 7, 5, WHITE, -leveltime);
						create_bullet(5, 4, 800,900, -t - i * 12, 7, 5, WHITE, -leveltime);
					}
					setclock(-leveltime, 4, 20,-2);
				}
			}









			if (leveltime <= 0 && leveltime > -60) {
				setlinecolor(WHITE);
				for (i = 0; i < 900; i++) {
					circle(object[1].x, object[1].y, i);
					FlushBatchDraw();
					leveltime = -60;
				}
				destory(object[1]);
				for (i = 0; i <= bulno; )
					destory(bullet[i]);
				lasttime = time(NULL) - nowtime;
			}


			if (hp <= 0 && deadkill) {
				for (int i = 0; i < 20; i++) {
					setlinecolor(BLACK);
					for (int t = 0; t < 45; t++)circle(player.x, player.y, 900 - (i * 45 + t));
					if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
						standmpup = 2;
						mpup = standmpup;
						hp = maxhp / 2;
						deadkill = 0;
						for (int i = 0; i <= bulno; )
							destory(bullet[i]);
						setlinecolor(WHITE);
						for (int i = 0; i < 20; i++) {
							for (int t = 0; t < 45; t++)circle(player.x, player.y, i * 45 + t);
							FlushBatchDraw();
							blanktime();
						}
						break;
					}
					FlushBatchDraw();
					blanktime();
				}
			}
			if (hp <= 0) {
				setlinecolor(BLACK);
				destory(object[1]);
				for (i = 0; i <= bulno; )
					destory(bullet[i]);
				for (i = 0; i < 900; i++) {
					circle(player.x, player.y, i);
					FlushBatchDraw();
				}
				dialogue_lost();
				break;
			}

			updateWithoutInput_before();
			updateWithInput();
			show();
			updateWithoutInput_after();
			//Sleep(10000);
			leveltime--;

		}
	}
}

void level4() {
	leveljumpout = 0;
	while (true)
	{
		if (leveljumpout == 1)break;
		loadimage(&back[0], _T("image\\background\\4.png"));//���ر���ͼƬ
		nowtime = time(NULL);
		int deadkill = 1;
		standmpup = 3;
		hp = maxhp;
		mp = maxmp;
		int i = 0;
		int t = 0;
		qte = 0;
		qterand[0] = rand() % 135;
		qterand[1] = 180 + rand() % 135;
		(float)lt;
		leveltime = 21600;
		fps = 60;
		startup();
		object[1].y = -100;
		while (true)
		{
			if (leveljumpout == 1)break;
			lt = 21600 / fps - leveltime / fps;
			
			if (lt < 25) {
				if (object[1].y < 200)object[1].y++;
				if (lt > 5) {
					if ((int)leveltime % 10 == 0) {
						t += 17;
						for (i = 0; i < 3; i++) {
							int ang = atan((player.y-200) / (player.x-200)) * 180 / PI;
							if (player.x - 200 < 0)ang = ang + 180;
							create_bullet(0, 5, 200, 200, ang, 15, 5, WHITE, 0);
							create_bullet(0, 5, 200, 200, ang + 20, 10, 5, WHITE, 0);
							create_bullet(0, 5, 200, 200, ang - 20, 10, 5, WHITE, 0);
						}
						for (i = 0; i < 3; i++) {
							int ang = atan((player.y-200) / (player.x-600)) * 180 / PI;
							if(player.x - 600<0)ang = ang + 180;
							create_bullet(0, 5, 600, 200, ang,15, 5, WHITE, 0);
							create_bullet(0, 5, 600, 200, ang + 20, 10, 5, WHITE, 0);
							create_bullet(0, 5, 600, 200, ang - 20, 10, 5, WHITE, 0);
						}
						for (int i = 0; i < 10 && (int)leveltime % 30 == 0; i++) {
							create_bullet(3, 3, 600, 200, t + i * 36, 7, 5, LIGHTBLUE, 0);
							create_bullet(3, 3, 600, 200, -t - i * 36, 7, 5, LIGHTBLUE, 0);
							create_bullet(3, 3, 200, 200, t + i * 36, 7, 5, LIGHTBLUE, 0);
							create_bullet(3, 3, 200, 200, -t - i * 36, 7, 5, LIGHTBLUE, 0);
						}
					}
				}
			}
			if (lt == 25) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 35 && lt < 81) {
				if ((int)leveltime % 10 == 0&&(int)leveltime%360<=80) {
					t += 10;
					if (t > 90)t -= 93;
					for (i = 0; i < 9; i++) {
						create_bullet(5, 0, i * 100, t * 10, 45, 7, 5, 0xfffa57, -1);
						create_bullet(5, 0, i * 100, t * 10, 135, 7, 5, 0xfffa57, -1);
					}
				}
				if ((int)leveltime % 360 == 80)setclock(-1, 5, 10,1);
			}
			if (lt == 80) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 90 && lt < 120) {
				if ((int)leveltime % 120 <= 10) {
					for(int i=0;i<10;i++)
						create_bullet(5, 3, object[1].x, object[1].y, leveltime * 10 + i, 15, 5, LIGHTRED, leveltime);
					for (int i = 0; i < 10; i++)
						create_bullet(5, 3, object[1].x, object[1].y, -leveltime * 10 - i+180, 15, 5, LIGHTBLUE, leveltime);
					setclock(leveltime,5,30,20);

				}
			}
			if (lt == 120) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt >= 130 && lt < 160) {

				if ((int)leveltime % 1 == 0) {
					setlinecolor(WHITE);
					circle(player.x, player.y, 200);
					FlushBatchDraw();
					i += 1;
					int x, y;
					x = 200 * cos(i) + player.x;
					y = 200 * sin(i) + player.y;
					int ang = atan((player.y - y) / (player.x - x)) * 180 / PI;
					if ((player.x - x) < 0)ang = ang + 180;
					create_bullet(5, 3, x, y, ang + 60 * (sin(lt) + 1.2), 10, 5, 0xfffa57, 0);

				}
				if ((int)leveltime % 20) {
					for (int t = 0; t < 3; t++) {
						create_bullet(5, 20, object[1].x, object[1].y, t * 120 + leveltime / 3.5, 20, 5, LIGHTBLUE + leveltime / 4, 0);

					}
				}
			}
			if (lt == 160) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt == 170) {
				object[1].velocity = 2;
				object[1].Vangle = 45;
			}
			if (lt > 170 && lt < 210) {
				setlinecolor(WHITE);
				circle(object[1].x, object[1].y, 200);
				FlushBatchDraw();
				if (object[1].x >= 800) {
					object[1].x = 800;
					if ((int)object[1].Vangle % 360 < 180)
						object[1].Vangle += 90;
					else
						object[1].Vangle += 270;
				}
				if (object[1].x <= 0) {
					object[1].x <= 0;
					if ((int)object[1].Vangle % 360 > 180)
						object[1].Vangle += 90;
					else
						object[1].Vangle += 270;
				}
				if (object[1].y >= 900) {
					object[1].y = 900;
					if ((int)object[1].Vangle % 360 > 90)
						object[1].Vangle += 90;
					else
						object[1].Vangle += 270;
				}
				if (object[1].y <= 0) {
					object[1].y <= 0;
					if ((int)object[1].Vangle % 360 > 270)
						object[1].Vangle += 90;
					else
						object[1].Vangle += 270;
				}
				if ((int)leveltime % 1 == 0) {
					i += 1;
					int x, y;
					x = 200 * cos(i) + object[1].x;
					y = 200 * sin(i) + object[1].y;
					int ang = atan((object[1].y - y) / (object[1].x - x)) * 180 / PI;
					if ((object[1].x - x) < 0)ang = ang + 180;
					create_bullet(5, 3, x, y, ang + 60 * (sin(lt) + 0.5), 10, 5, WHITE, 0);

				}
			}
			if (lt == 210) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
				object[1].velocity = 0;
			}
			if (lt > 210 && lt < 225) {
				if (object[1].x < 400)object[1].x = object[1].x++;
				if (object[1].x > 400)object[1].x = object[1].x--;
				if (object[1].y > 200)object[1].y = object[1].y--;
				if (object[1].y < 200)object[1].y = object[1].y++;
			}
			if (lt > 220 && lt < 260) {
				if ((int)leveltime % 15 == 1) {
					t += 7;
					for (i = 0; i < 20; i++)
						create_bullet(0, 4 + (lt - 220) / 10, object[1].x, object[1].y, t + i * 18, 10, 5, LIGHTGREEN - (lt - 220) * 10, 0);
				}
			}
			if (lt > 270 && lt < 310) {
				if (object[1].y < 200)object[1].y++;
				if ((int)leveltime % 30 == 1) {
					t += 20;
					for (i = 0; i < 30; i++)
						create_bullet(5, 6, object[1].x, object[1].y, t + i * 12, 7, 5, WHITE, leveltime);
					setclock(leveltime, 3, 20,-2);
					for (i = 0; i < 30; i++)
						create_bullet(5, 6, object[1].x, object[1].y, -t - i * 12, 7, 5, WHITE, -leveltime);
					setclock(-leveltime, 4, 20,-2);
				}
			}
			if (lt == 310) {
				mpup = standmpup;
				qte = 360;
				qterand[0] = rand() % 135;
				qterand[1] = 180 + rand() % 135;
				i = 0;
				t = 0;
			}
			if (lt > 320 && lt < 360) {
				if (object[1].y < 200)object[1].y++;
				if ((int)leveltime % 60 == 1) {
					t += 20;
					for (i = 0; i < 30; i++) {
						create_bullet(5, 4, 0, 900, t + i * 12, 7, 5, WHITE, leveltime);
						create_bullet(5, 4, 800, 900, t + i * 12, 7, 5, WHITE, leveltime);
					}
					setclock(leveltime, 3, 20,-2);
					for (i = 0; i < 30; i++) {
						create_bullet(5, 4, 0, 900, -t - i * 12, 7, 5, WHITE, -leveltime);
						create_bullet(5, 4, 800, 900, -t - i * 12, 7, 5, WHITE, -leveltime);
					}
					setclock(-leveltime, 4, 20,-2);
				}
			}









			if (leveltime <= 0 && leveltime > -60) {
				setlinecolor(WHITE);
				for (i = 0; i < 900; i++) {
					circle(object[1].x, object[1].y, i);
					FlushBatchDraw();
					leveltime = -60;
				}
				destory(object[1]);
				for (i = 0; i <= bulno; )
					destory(bullet[i]);
				lasttime = time(NULL) - nowtime;
			}


			if (hp <= 0 && deadkill) {
				for (int i = 0; i < 20; i++) {
					setlinecolor(BLACK);
					for (int t = 0; t < 45; t++)circle(player.x, player.y, 900 - (i * 45 + t));
					if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
						standmpup = 2;
						mpup = standmpup;
						hp = maxhp / 2;
						deadkill = 0;
						for (int i = 0; i <= bulno; )
							destory(bullet[i]);
						setlinecolor(WHITE);
						for (int i = 0; i < 20; i++) {
							for (int t = 0; t < 45; t++)circle(player.x, player.y, i * 45 + t);
							FlushBatchDraw();
							blanktime();
						}
						break;
					}
					FlushBatchDraw();
					blanktime();
				}
			}
			if (hp <= 0) {
				setlinecolor(BLACK);
				destory(object[1]);
				for (i = 0; i <= bulno; )
					destory(bullet[i]);
				for (i = 0; i < 900; i++) {
					circle(player.x, player.y, i);
					FlushBatchDraw();
				}
				dialogue_lost();
				break;
			}

			updateWithoutInput_before();
			updateWithInput();
			show();
			updateWithoutInput_after();
			//Sleep(10000);
			leveltime--;

		}
	}
}
