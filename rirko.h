#include <stdio.h>
#include <Windows.h>
LARGE_INTEGER cpuFreq;//cpu频率
LARGE_INTEGER tickBeginTime;//滴答开始时间
LARGE_INTEGER tickEndTime;//滴答结束时间
int fps = 60;//游戏帧率

void blanktime()
{
	double sleeptime;
	QueryPerformanceCounter(&tickEndTime);//获取帧结束滴答
	sleeptime = (double)(1000.0 / fps) - ((double)tickEndTime.QuadPart - (double)tickBeginTime.QuadPart) / (double)cpuFreq.QuadPart;
	if (sleeptime > 0 && sleeptime < 1000)
		Sleep(sleeptime);
	QueryPerformanceCounter(&tickBeginTime);//获取帧开始滴答
}