// bafenfaBresenham.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<GL/glut.h>
#include<stdio.h> 
#include<math.h>


void setpoint(int x0, int y0, int x, int y)//同时绘制八个点(对称)
{
	glColor3f(1.0f, 1.0f, 0.0);
	glVertex2f((x0 + x), (y0 + y));
	glVertex2f((x0 + y), (y0 + x));
	glVertex2f((x0 + y), (y0 - x));
	glVertex2f((x0 + x), (y0 - y));
	glVertex2f((x0 - x), (y0 - y));
	glVertex2f((x0 - y), (y0 - x));
	glVertex2f((x0 - y), (y0 + x));
	glVertex2f((x0 - x), (y0 + y));
}
void midpointcircle(int x0, int y0, int r)//中点画圆法
{
	int x = 0;
	int y = r;
	int d = 1 - r;      // 为了简化算法，摆脱浮点数，所以对d进行取整计算所以从1.25-r变到了1-r
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	setpoint(x0, y0, x, y);
	while (x < y)
	{
		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		setpoint(x0, y0, x, y);
	}
	glEnd();
	glFlush();
}
void ChangeSize(GLsizei w, GLsizei h)
{
	if (h == 0)     h = 1;
	// 设置视区尺寸
	glViewport(0, 0, w, h);
	// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 建立修剪空间的范围
	if (w <= h)
		glOrtho(0.0f, 250.0f, 0.0f, 250.0f * h / w, 1.0, -1.0);
	else
		glOrtho(0.0f, 250.0f * w / h, 0.0f, 250.0f, 1.0, -1.0);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	int x0 = 100, y0 = 100, r = 60;
	printf("请输入圆的半径：");
	scanf_s("%d", &r);
	midpointcircle(x0, y0, r);
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(400, 400);
	glutCreateWindow("圆");
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	glClearColor(1.0, 1.0, 1.0, 0.0);  //设置窗口背景的颜色       
	glutMainLoop();
	return 0;
}
