// Bresenham.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//Bresenham划线算法
//绘制斜率大于0且小于1的线段
//Bresenham划线算法
//绘制斜率大于0且小于1的线段
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include<math.h>
using namespace std;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void display()
{
	int x1 = 10, y1 = 10, x2 = 150, y2 = 100;
	//cout<<"please enter the positions of start point and the end point:x1,y1,x2,y2:"<<endl;
	//cin>>x1>>y1>>x2>>y2;
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int x, y;
	int temp1 = 2 * dy;
	int temp2 = 2 * (dy - dx);
	int p = temp1 - dx;
	if (x1 > x2)
	{
		x = x2;
		y = y2;
		x2 = x1;
	}
	else {
		x = x1;
		y = y1;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(x, y);
	while (x < x2)
	{
		x++;
		if (p < 0)
			p += temp1;
		else
		{
			y++;
			p += temp2;
		}
		glVertex2i(x, y);
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Bresenham Draw Line");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
