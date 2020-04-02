#pragma once
#include<easyx.h>
#include<graphics.h>
#include <time.h>
#include"STG_thread.h"
#include"STG_stage.h"
//startup游戏初始化//////////////////////////////////////////////////////////////////////////////////////////////startup游戏初始化
void startup()
{
	QueryPerformanceFrequency(&cpuFreq);//获取cpu频率

	startup_activate_object();//启用实体

	loadimage(&player_picture[0], _T("image\\player.png"));//加载玩家图片
	loadimage(&player_picture[1], _T("image\\player_mask.png"));//加载玩家蒙版图片
	player.sprite.img[0] = &player_picture[0];
	player.sprite.img[1] = &player_picture[1];
	player.sprite.strip = 3;
	player.sprite.speed = 2;
	player.hitbox = 5 - skillnumber[8];
	player.depht = 3;
	player.x = 400;
	player.y = 700;

	loadimage(&judgecircle[0], _T("image\\circle.png"));//加载判断圈图片
	loadimage(&judgecircle[1], _T("image\\circle_mask.png"));//加载判断圈蒙版图片spr[0].img[1]
	spr[0].img[0] = &judgecircle[0];
	spr[0].img[1] = &judgecircle[1];
	spr[0].strip = 8;
	spr[0].speed = 2;

	loadimage(&picture[1][0], _T("image\\cross.png"));
	loadimage(&picture[1][1], _T("image\\cross_mask.png"));
	create_object(1, 0, 400, 200, 0, 60, 3, 8);
	mpup = 3;
	stddmgrate = dmgrate;
	BeginBatchDraw();//开始显卡绘制
}

//显示类//////////////////////////////////////////////////////////////////////////////////////////////////////////显示类

void show()
{
	backanime(back[0]);
	//显示耐力圈和生命圈
	if (kb_x || mp < maxmp * 0.3) {
		setlinecolor(WHITE);
		if (mp <= 0)setlinecolor(BLUE);
		float mparc = (mp / (float)maxmp) * pi * 2;
		for (int i = 0; i < 10; i++) {
			arc(player.x - 70 - i, player.y - 70 - i, player.x + 70 + i, player.y + 70 + i, 0.5 * pi, mparc + 0.5 * pi);
		}
	}
	if (kb_x || hp < maxhp * 0.6 || hp < hpup) {
		setlinecolor(LIGHTGREEN);
		if (hpup > hp)setlinecolor(RED);
		float hparc = (hp / (float)maxhp) * pi * 2;
		for (int i = 0; i < 10; i++) {
			arc(player.x - 80 - i, player.y - 80 - i, player.x + 80 + i, player.y + 80 + i, 0.5 * pi, hparc + 0.5 * pi);
		}
	}
	if (kb_shift == 1)	animesprite(0, player.x, player.y);//显示旋转圈
	settextstyle(30, 0, _T("问藏书房"));//显示敌方位置
	setbkcolor(RED);
	setbkmode(OPAQUE);
	settextcolor(WHITE);
	outtextxy(object[1].x - 40, 870, _T("ENEMY"));
	imageFresh();//刷新贴图位置
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	if (kb_x) {
		setlinecolor(YELLOW);
		circle(player.x, player.y, 100 - cutclock);
	}
	if (kb_shift == 1)	fillcircle(player.x, player.y, player.hitbox+1);//显示判定点


	setfillcolor(BLACK);//显示血条等ui
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
	solidpie(5, 5, 55, 55, pi / 2, pi / 2 - (1 - leveltime / 21600) * 2 * pi);
	setfillcolor(BLACK);
	solidcircle(30, 30, 15);



	if (qte > 0) {//qte圈
		settextstyle(15, 0, _T("黑体"));
		settextcolor(YELLOW);
		setbkcolor(LIGHTMAGENTA);
		setbkmode(OPAQUE);
		if (lt % 2 == 1)outtextxy(player.x - 65, player.y + 60, _T("Intensify Chance"));
		setlinecolor(RED);
		for (int i = 0; i < 10; i++) {
			arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qte) * pi / 180, 1.5 * pi);
		}
		setlinecolor(GREEN);
		if (qte > qterand[0] && qte <= qterand[0] + 45)
			for (int i = 0; i < 10; i++)
				arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qte) * pi / 180, (270 - qterand[0]) * pi / 180);

		if (qte > qterand[0] && qte > qterand[0] + 45)
			for (int i = 0; i < 10; i++)
				arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qterand[0] - 45) * pi / 180, (270 - qterand[0]) * pi / 180);

		setlinecolor(YELLOW);
		if (qte > qterand[1] && qte <= qterand[1] + 45)
			for (int i = 0; i < 10; i++)
				arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qte) * pi / 180, (270 - qterand[1]) * pi / 180);

		if (qte > qterand[1] && qte > qterand[1] + 45)
			for (int i = 0; i < 10; i++)
				arc(object[1].x - 150 - i, object[1].y - 150 - i, object[1].x + 150 + i, object[1].y + 150 + i, (270 - qterand[1] - 45) * pi / 180, (270 - qterand[1]) * pi / 180);

	}


	if (//显示break字样
		(lt > 25 && lt < 30) ||
		(lt > 65 && lt < 70) ||
		(lt > 100 && lt < 105) ||
		(lt > 155 && lt < 160) ||
		(lt > 230 && lt < 245) ||
		(lt > 270 && lt < 280)) {
		settextstyle(20, 0, _T("黑体"));
		settextcolor(GREEN);
		setbkcolor(BLACK);
		setbkmode(OPAQUE);
		outtextxy(0, 60, _T("OPERATION BREAK"));
	};
	//datawindow();
	if (leveltime <= 0)showscore();
}
//与玩家操作无关的更新 帧前///////////////////////////////////////////////////////////////////////////////////////与玩家操作无关的更新 帧前
void updateWithoutInput_before()
{
	if (mp < maxmp)mp = mp + mpup;//体力及耐力回复
	if (mp > maxmp)mp = maxmp;//体力及耐力回复
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
//与玩家操作有关的更新////////////////////////////////////////////////////////////////////////////////////////////与玩家操作有关的更新
void updateWithInput()
{
	keyboard();//键入

	if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) || (GetAsyncKeyState(VK_LBUTTON) & 0x8000))pausetime();
	player_move();//玩家移动及耐力消耗
	if (kb_shift == 1 && mp > 10)mp = mp - 2;
	if (kb_space == 1 && player.x < 0) {
		player.x = WIDTH;
		mp = mp - 100;
	}
	if (kb_space == 1 && player.x > WIDTH) {
		player.x = 0;
		mp = mp - 100;
	}

	if (kb_z == 1 && shootclock < 0&&!kb_x) {//发射子弹
		mp = mp - 20;
		if (kb_shift) {
			int ang = atan((object[1].y - player.y) / (object[1].x - player.x)) * 180 / pi;
			if ((object[1].x - player.x) < 0)ang = ang + 180;
			create_bullet(-1, 40, player.x - 20, player.y, ang, 20, 2, WHITE, 0);
			create_bullet(-1, 40, player.x + 20, player.y, ang, 20, 2, WHITE, 0);
		}
		else {
			create_bullet(-1, 40, player.x + 30, player.y, 270, 10, 2, WHITE, 0);
			create_bullet(-1, 40, player.x - 30, player.y, 270, 10, 2, WHITE, 0);
			int ang = atan((object[1].y - player.y) / (object[1].x - player.x + 50)) * 180 / pi;
			if ((object[1].x - player.x + 50) < 0)ang = ang + 180;
			create_bullet(-1, 40, player.x - 50, player.y, ang, 20, 2, WHITE, 0);

			ang = atan((object[1].y - player.y) / (object[1].x - player.x - 50)) * 180 / pi;
			if ((object[1].x - player.x - 50) < 0)ang = ang + 180;
			create_bullet(-1, 40, player.x + 50, player.y, ang, 20, 2, WHITE, 0);
		}
		shootclock = 10;
		if (skillnumber[5] && hp < hpup)shootclock = 5;
	}

	if (qte > qterand[0] && qte < (qterand[0] + 45) && kb_space) {//qte操作
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

//与玩家操作无关的更新 帧后////////////////////////////////////////////////////////////////////////////////////////与玩家操作无关的更新 帧后
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
	if (player.x < 0)player.x = 0;//防止玩家出屏
	if (player.y < 0)player.y = 0;
	if (player.x > WIDTH)player.x = WIDTH;
	if (player.y > HIGH)player.y = HIGH;

	Vmove();//在速度影响下的位移

	hitcheck();//碰撞检测

	int i;//子弹时钟判定
	for (i = 0; i <= bulno; i++) {
		if (bullet[i].clock[1] == 0) {
			int ang = atan((player.y - bullet[i].y) / (player.x - bullet[i].x)) * 180 / pi;
			if ((player.x - bullet[i].x) < 0)ang = ang + 180;
			velocity_bul(i, bullet[i].velocity, ang);
		}
		if (bullet[i].clock[2] == 0) {
			velocity_bul(i, bullet[i].velocity + bullet[i].tempdate /*+2*/, bullet[i].Vangel + 90);
		}
		if (bullet[i].clock[3] == 0) {
			velocity_bul(i, bullet[i].velocity + bullet[i].tempdate /** 0.5*/, bullet[i].Vangel - 90);
		}
		if (bullet[i].clock[4] == 0) {
			velocity_bul(i, bullet[i].velocity + bullet[i].tempdate /** 0.5*/, bullet[i].Vangel + 90);
		}
		if (bullet[i].clock[5] == 0) {
			velocity_bul(i, bullet[i].velocity + bullet[i].tempdate/*+1*/, bullet[i].Vangel);
		}
	}

	auto_destory();//出屏删除物品

	FlushBatchDraw();//显卡批量绘制
	keyboard_release();//释放键盘变量
	blanktime();//补帧
}



//关闭程序
void endoff()
{

	EndBatchDraw();//终止显卡绘制
}



void level1() {
	leveljumpout = 0;
	while (true)
	{
		if (leveljumpout == 1)break;
		loadimage(&back[0], _T("image\\background\\1.png"));//加载背景图片
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
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：卡莱，冷静下来，就和往常一样就可以了"));
				dialogue(crarcter_doctor, _T("卡兰德克塔娜：……我明白的，阿斯克勒皮俄斯大人，只是这次的患者是……"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：不用紧张，在我的协助下，所有的病魔都将曝光在光明下"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：你只要跟往常一样对患者进行手术就可以了"));
				dialogue(crarcter_doctor, _T("卡兰德克塔娜：嗯，我知道了"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：你应该记得，用【方向键】来控制你在空间中的投影"));
			}
			if (leveltime == 6900) {
				settextcolor(BLACK);
				settextstyle(60, 50, _T("问藏书房"));
				setbkmode(TRANSPARENT);
				outtextxy(90, 450, _T("按下方向键以调整投影位置"));
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
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：很好，看上去你已经找回感觉了"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：现在开始对患者身上的瘟疫进行映射，准备好了吗？"));
				dialogue(crarcter_doctor, _T("卡兰德克塔娜：我想应该可以了"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：好，投影开始"));
			}
			if (lt > 6 && lt < 13)object[1].y++;
			if (leveltime == 6500) {
				setbkcolor(WHITE);
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：注意，在瘟疫反抗手术时"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：瘟疫的投影也会由于本体的波动而扩散出弹幕状的攻击"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：若被击中会对你和患者的生命安全造成危害，注意躲避"));
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
				dialogue(crarcter_doctor, _T("卡兰德克塔娜：唯手熟尔"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：很好"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：对方可能会进行大密度的弹幕攻击"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：必要时刻不要吝啬耐力值，按下【shift】进入精细模式"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：但是请留意耐力计量表，当耐力清空时将动弹不得"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：按下【X】键可以近距离观察体力与耐力计量表"));

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
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：是强化机会！把握住，不要错过"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：注意观察对方周围的那段圆弧"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：在圆弧走到特殊的位置时按下【空格键】可以获得相应的强化"));
				if (hp == maxhp) {
					dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：当圆弧走到黄色的位置时按下空格"));
					dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：你将获得【耐力加速回复】的强化，直到下一次强化机会"));
					dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：绿色的位置是【回复所有体力值】的强化"));
					dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：不过看上去并没有必要（笑）"));
				}
				else {
					dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：当圆弧走到绿色的位置时按下空格"));
					dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：你将获得【回复所有体力值】的强化，可以补救之前的损失"));
					dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：顺便一提，黄色的位置是【耐力加速回复】的强化"));
					dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：选择哪一个要凭你自己权衡利弊了"));
				}

			}
			if (leveltime == 3600) {
				setbkcolor(WHITE);
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：【空格键】除了之前说的那种用途外"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：还可以让你在空间的边缘进行穿梭"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：当你在空间的最左边或最右边时，按下左键或右键的同时按下空格键"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：就可以穿梭到另一边的边界"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：这个举措会大量消耗耐力，要注意哦"));
			}

			if (lt > 60 && lt < 75)
			{
				object[1].x = player.x;
				if ((int)leveltime % 10 == 0)create_bullet(1, 6, object[1].x, object[1].y, 90, 15, 5, YELLOW, 0);
			}
			if (leveltime == 2400) {
				object[1].x = 400;
				setbkcolor(WHITE);
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：在躲避的同时，我们也要进行反击"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：按下【Z】键加速对瘟疫进行瓦解"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：瘟疫的瓦解度会反应在左上角的圆环中"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：随着瘟疫被逐步瓦解，圆环的红色部分将逐步收敛"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：当红色部分消失时，瘟疫完全瓦解"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：当然，主动加速瓦解是要消耗耐力的"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：因此，倘若耐力不足的话，就安心躲弹幕吧！"));
			}
			if (leveltime > 2300)shootclock = 10;
			if (leveltime == 2300) {
				settextcolor(BLACK);
				settextstyle(60, 50, _T("问藏书房"));
				setbkmode(TRANSPARENT);
				outtextxy(110, 450, _T("按下【Z】键以发射子弹"));
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
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：危险！你的体力计量表下降到零界点以下了！"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：现在是你一场手术失误后 唯一一次 挽救机会！"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：在被命中的一瞬间按下【空格键】，你将以一半体力值的状态返回"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：并且，你会处于耐力回复速度下降的异常状态"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：但总比力尽倒下好，不是吗？"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：要在什么时机按下空格键？要具体说的话……"));
				dialogue(crarcter_kami, _T("阿斯克勒皮俄斯：就是现在！！！"));
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
		loadimage(&back[0], _T("image\\background\\2.png"));//加载背景图片
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
		loadimage(&back[0], _T("image\\background\\3.png"));//加载背景图片
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
					int ang = atan((player.y - y) / (player.x - x)) * 180 / pi;
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
					int ang = atan((player.y - y) / (player.x - x)) * 180 / pi;
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
				object[1].Vangel = 45;
			}
			if (lt > 170 && lt < 210) {
				setlinecolor(WHITE);
				circle(object[1].x, object[1].y, 200);
				FlushBatchDraw();
				if (object[1].x >= 800) {
					object[1].x = 800;
					if ((int)object[1].Vangel % 360 < 180)
						object[1].Vangel += 90;
					else
						object[1].Vangel += 270;
				}
				if (object[1].x <= 0) {
					object[1].x <= 0;
					if ((int)object[1].Vangel % 360 > 180)
						object[1].Vangel += 90;
					else
						object[1].Vangel += 270;
				}
				if (object[1].y >= 900) {
					object[1].y = 900;
					if ((int)object[1].Vangel % 360 > 90)
						object[1].Vangel += 90;
					else
						object[1].Vangel += 270;
				}
				if (object[1].y <= 0) {
					object[1].y <= 0;
					if ((int)object[1].Vangel % 360 > 270)
						object[1].Vangel += 90;
					else
						object[1].Vangel += 270;
				}
				if ((int)leveltime % 1 == 0) {
					i += 1;
					int x, y;
					x = 200 * cos(i) + object[1].x;
					y = 200 * sin(i) + object[1].y;
					int ang = atan((object[1].y - y) / (object[1].x - x)) * 180 / pi;
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
		loadimage(&back[0], _T("image\\background\\4.png"));//加载背景图片
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
							int ang = atan((player.y-200) / (player.x-200)) * 180 / pi;
							if (player.x - 200 < 0)ang = ang + 180;
							create_bullet(0, 5, 200, 200, ang, 15, 5, WHITE, 0);
							create_bullet(0, 5, 200, 200, ang + 20, 10, 5, WHITE, 0);
							create_bullet(0, 5, 200, 200, ang - 20, 10, 5, WHITE, 0);
						}
						for (i = 0; i < 3; i++) {
							int ang = atan((player.y-200) / (player.x-600)) * 180 / pi;
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
					int ang = atan((player.y - y) / (player.x - x)) * 180 / pi;
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
				object[1].Vangel = 45;
			}
			if (lt > 170 && lt < 210) {
				setlinecolor(WHITE);
				circle(object[1].x, object[1].y, 200);
				FlushBatchDraw();
				if (object[1].x >= 800) {
					object[1].x = 800;
					if ((int)object[1].Vangel % 360 < 180)
						object[1].Vangel += 90;
					else
						object[1].Vangel += 270;
				}
				if (object[1].x <= 0) {
					object[1].x <= 0;
					if ((int)object[1].Vangel % 360 > 180)
						object[1].Vangel += 90;
					else
						object[1].Vangel += 270;
				}
				if (object[1].y >= 900) {
					object[1].y = 900;
					if ((int)object[1].Vangel % 360 > 90)
						object[1].Vangel += 90;
					else
						object[1].Vangel += 270;
				}
				if (object[1].y <= 0) {
					object[1].y <= 0;
					if ((int)object[1].Vangel % 360 > 270)
						object[1].Vangel += 90;
					else
						object[1].Vangel += 270;
				}
				if ((int)leveltime % 1 == 0) {
					i += 1;
					int x, y;
					x = 200 * cos(i) + object[1].x;
					y = 200 * sin(i) + object[1].y;
					int ang = atan((object[1].y - y) / (object[1].x - x)) * 180 / pi;
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
