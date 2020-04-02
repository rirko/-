//////////////////
//动态图显示脚本//
//作者：邵远航  //
//////////////////
#pragma once
#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
//(长带图路径,	总帧数,	循环次数,	动画左上角x坐标,	动画左上角y坐标,	动画宽度	,动画高度)
void showgif(
	LPCTSTR path, 
	int strip, 
	int time, 
	int x, 
	int y, 
	int w,
	int h
	)
{
	IMAGE gif;
	loadimage(&gif, path, w * strip, h);
	int widt = w;
	int heig = h;
	int i=0;
	while (true) 
	{

		putimage(
			x,
			y,
			widt, heig,
			&gif,
			i * widt, 0);
		FlushBatchDraw();
		Sleep(100);
		i++;
		if (i == strip && time ==1)break;
		if (i == strip && time > 1) {
			i = 0;
			time--;
		}
	}
}