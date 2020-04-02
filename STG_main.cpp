//stg弹幕游戏，作者：邵远航
//引用头文件
#include <stdio.h>//标准输入输出
#include <stdlib.h>//标准库
#include <conio.h>//键盘交互
#include <math.h>//数学
#include <Windows.h>//系统
#include <string.h>//字符串
#include <time.h>
#include <commdlg.h>
#include <atlstr.h>
#include <graphics.h>
#include <easyx.h>

#include"STG_io.h"
#include"STG_define.h"
#include"STG_global.h"
#include"STG_thread.h"
#include"STG_anime.h"
#include"STG_stage.h"
#include"STG_level.h"


//===============================================================================================================
//流程函数区////流程函数区////流程函数区////流程函数区////流程函数区////流程函数区////流程函数区////流程函数区///
//===============================================================================================================

//Debug测试函数//////////////////////////////////////////////////////////////////////////////////////////////////Debug测试函数
void Debug() 
{
	static int i=0;
	if ((kb_z == 1) && (i >= 10))
	{
		create_object(0, 0, player.x, player.y,270,0,1,35);
		i = 0;
	}
	i++;
	TCHAR s[20];
	swprintf_s(s, _T("%lf"), lasttime);
	outtextxy(0, 0, s);
	swprintf_s(s, _T("%lf"), TRUE_FPS);
	outtextxy(0, 20, s);
}

//启动界面
void very_startup() 
{
	int zoomrate = 1;
	printf("写在前面：\n\n首先，感谢您对本游戏的兴趣与支持！\n\n当前游戏版本为v.demo.1，剧情与关卡仅更新到第四章\n以及技能“居合斩”\n\n居合斩的使用方法为：按住【X】键时开始蓄力，蓄力完成后当子弹触碰到蓄力圈的瞬间按下【Z】键发动\n发动成功后可大幅减少所受伤害及回复全部体力\n");
	printf("\n按下鼠标左键或【esc】以使用暂停功能"); 
	printf("\n本游戏官方网站为：http://doyagame.rthe.net/ \n");
	printf("\n游玩前请确保已安装游戏目录下字体文件\n我是本游戏的制作者RIRKO，希望大家玩的愉快");
	printf("\n选择分辨率：\n1.800x900(推荐)\n2.720x810\n3.640x720\n4.560x630\n5.自定义\n");
	scanf_s("%d", &zoomrate);
	printf("\n选择难易度【最低为1】\n难易度将决定您在游戏中受到伤害的数值及得分，过低及过高的难易度将破坏您的游戏体验【推荐设置为4】\n请谨慎选择：");
	scanf_s("%d", &hard);
	if (hard < 1)hard = 4;
	switch (zoomrate)//界面初始化
	{
	case 1:
		windowwidth = 800;
		windowhigh = 900;
		initgraph(windowwidth,windowhigh);
		setaspectratio(1, 1);
		break;
	case 2:
		windowwidth = 720;
		windowhigh = 810;
		initgraph(windowwidth, windowhigh);
		setaspectratio(0.9, 0.9);
		break;
	case 3:
		windowwidth = 640;
		windowhigh = 720;
		initgraph(windowwidth, windowhigh);
		setaspectratio(0.8, 0.8);
		break;
	case 4:
		windowwidth = 560;
		windowhigh = 630;
		initgraph(windowwidth, windowhigh);
		setaspectratio(0.7, 0.7);
		break;

	case 5:
		printf("输入长度与宽度，用空格隔开（单位：像素）");
		scanf_s("%d %d", &windowwidth, &windowhigh);
		initgraph(windowwidth, windowhigh);
		setaspectratio(windowwidth / 800.0, windowhigh / 900.0);
		break;

	default:
		break;
	}
	DMG = hard * 50;
	srand((unsigned int)time(NULL));
	QueryPerformanceFrequency(&cpuFreq);//获取cpu频率
	loadimage(&TITLE[0], _T("image\\title\\title.png"));
	loadimage(&TITLE[1], _T("image\\title\\title3.png"));
	loadimage(&white, _T("image\\white.png"), WIDTH, HIGH);
	vedio[0].sprite.img[0] = &TITLE[0];
	vedio[0].sprite.strip = 10;
	vedio[0].x = WIDTH / 2;
	vedio[0].y = HIGH / 2;
	vedio[0].sprite.speed = 2;

	loadimage(&crarcter_doctor[0], _T("image\\crarcter\\doctor.png"));
	loadimage(&crarcter_doctor[1], _T("image\\crarcter\\doctor_mask.png"));
	loadimage(&crarcter_assistant[0], _T("image\\crarcter\\assistant.png"));
	loadimage(&crarcter_assistant[1], _T("image\\crarcter\\assistant_mask.png"));
	loadimage(&crarcter_kami[0], _T("image\\crarcter\\kami.png"));
	loadimage(&crarcter_kami[1], _T("image\\crarcter\\kami_mask.png"));

	BeginBatchDraw();//开始显卡绘制
	putimage(0, 0, &white);
	FlushBatchDraw();
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//主函数////主函数////主函数////主函数////主函数////主函数////主函数////主函数////主函数////主函数//
////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	very_startup();
	
	startanime();
	startgame();
	dialogue_1();
	level1();
	dialogue_1pass();
	chooseskill();
	dialogue_2();
	while (true)
	{
	level2();
	dialogue_2pass();
	chooseskill();
	dialogue_3();
	level3();
	dialogue_3pass();
	chooseskill();
	dialogue_4();
	level4();
	closegraph();
	printf("目前制作进度于此，后续内容请关注官方网站公告（或者加我qq捞我真人对线也行QQ：1250104511）");
	system("pause");
	initgraph(windowwidth, windowhigh);
	
	chooseskill();
	}

	endoff();
	return 0;
}