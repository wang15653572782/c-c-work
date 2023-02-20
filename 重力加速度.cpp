#include <graphics.h>
#include <conio.h>
#include <stdio.h>
int main()
{
	int width = 800; // 画面宽度
	int height = 600; // 画面高度
	float g = 0.3; // 重力加速度
	float x = width / 6; // 小球x坐标
	float y = height / 3; // 小球y坐标
	float vy = 0; // 小球y方向速度
	int radius = 20; // 小球半径
	initgraph(width, height); // 新开一个画面

	while (1) // 一直循环
	{
		// 根据重力加速度，更新小球y方向的速度
		vy = vy + g;

		// 根据速度，更新小球的位置
		y = y + vy;

		// 小球碰到上下边界，y速度反向
		if (y <= radius)
			vy = -vy;
		if (y >= height - radius)
			vy = -vy;

		cleardevice(); // 清屏
		fillcircle(x, y, radius); // 画小球
		Sleep(3); // 暂停若干毫秒
	}
	return 0;
}


