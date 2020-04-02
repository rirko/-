#pragma once
////////////////////
//rirko2.h补帧函数//
//  作者：邵远航  //
////////////////////
/*使用说明：
	在主函数中引用该头文件。
	变量fps为游戏帧率
	通过赋值语句改变fps的参数达到控制帧率的效果
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>


LARGE_INTEGER cpuFreq;
LARGE_INTEGER tickBeginTime;
LARGE_INTEGER tickEndTime;
int fps=60;
double sleeptime;
double TRUE_FPS;
int total_flame = 0;
double lasttime;

void blanktime()
{
	static double temp;
	QueryPerformanceCounter(&tickEndTime);
	lasttime = (((double)tickEndTime.QuadPart - (double)tickBeginTime.QuadPart) / (double)cpuFreq.QuadPart) * 1000;
	sleeptime = (double)(1000.0 / fps) - lasttime;
	if (sleeptime > 0 && sleeptime < 1000) Sleep(sleeptime);
	QueryPerformanceCounter(&tickBeginTime);
	TRUE_FPS = 1.0 / (((double)tickBeginTime.QuadPart - temp) / (double)cpuFreq.QuadPart);
	temp = tickBeginTime.QuadPart;
	total_flame++;
}