#include <windows.h>
#include <GL/glut.h>
#include <cstdio>
#define LEFT 1//0001
#define RIGHT 2//0010
#define BOTTOM 4//0100
#define TOP 8//1000
int x1 = 150, y1 = 50, x2 = 50, y2 = 250, XL = 100, XR = 300, YB = 100, YT = 200;  //(x1,y1)、(x2,y2)为直线段的端点，XL为左边界，XR为右边界，YB为下边界，YT为上边界
int x1_init = 150, y1_init = 50, x2_init = 50, y2_init = 250;  //将直线段端点备份，以便画出裁剪前的直线段
void encode(int x, int y,int &c)
{//|或运算两者有一个为1结果就为1
	c = 0;
	if (x < XL) c |= LEFT;//按照数字进行或运算，左边界
	else if (x > XR) c |= RIGHT;//右边界
	if (y < YB) c |= BOTTOM;//下边界
	else if (y > YT) c |= TOP;//上边界
}
//上左:1001; 中左:0001; 下左:0101;
//上中:1000; 中中:0000 下中:0100
//上右:1010  中右:0010  下右:0110
void CS_LineClip()  //Cohen-Sutherland裁剪算法
{
	int x, y;
	int code1, code2, code;
    encode(x1, y1, code1);//先求出端点所在的区号
    encode(x2, y2, code2);//先求出端点所在的区号
	//循环处理
	while (code1 != 0 || code2 != 0)//只有两个端点同时都在矩形区域里才不使用函数
	{
		if (code1 & code2)//两个都为1才成立，这两个都在同一个区域中 直接不进行处理
			return;
		if (code1 != 0)//如果
			code = code1;
		else
			code = code2;

		if (LEFT & code)//线段与左边界相交(如果
		{
			x = XL;//求出的左边界的交点的x值
			y = y1 + (y2 - y1)*(XL - x1) / (x2 - x1);//求出左边交点的y值
		}
		else if (RIGHT & code)//线段与右边界相交
		{
			x = XR;//求出右边界的交点的x值
			y = y1 + (y2 - y1)*(XR - x1) / (x2 - x1);//根据斜率计算出右边界的交点的y值
		}
		else if (BOTTOM & code)//线段与下边界相交
		{
			y = YB;//求出下边界的交点的y值
			x = x1 + (x2 - x1)*(YB - y1) / (y2 - y1);//求出下边界的交点的x值根据斜率
		}
		else if (TOP & code)//线段与上边界相交
		{
			y = YT;
			x = x1 + (x2 - x1)*(YT - y1) / (y2 - y1);
		}
		if (code == code1)
		{
			x1 = x; y1 = y;  encode(x1, y1, code1);//将区域 外的端点覆盖掉
		}
		else
		{
			x2 = x; y2 = y; encode(x2, y2, code2);//将区域 外的端点覆盖掉
		}
	}
}
void mydisplay()  //显示函数
{
	//绘制方形边界
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);//设置背景颜色
	glPointSize(2);//设置点的大小
	glBegin(GL_LINE_LOOP);//绘制区域的操作
	glVertex2i(XL, YT);//绘制矩形
	glVertex2i(XL, YB);
	glVertex2i(XR, YB);
	glVertex2i(XR, YT);
	glEnd();
	glFlush();
	//绘制未裁剪前的线段
	glBegin(GL_LINES);//绘制直线的操作
	glVertex2i(x1_init, y1_init);
	glVertex2i(x2_init, y2_init);
	glEnd();
	glFlush();
	//绘制裁剪后的线段
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glFlush();
	//绘制剪裁区域外的直线段
	x1_init = 400, y1_init = 50, x2_init = 300, y2_init = 250;
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(x1_init, y1_init);
	glVertex2i(x2_init, y2_init);
	glEnd();
	glFlush();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 100);//窗口位置
	glutInitWindowSize(500, 400);
	glutCreateWindow("Cohen-Sutherland裁剪算法");
	glClearColor(1.0, 1.0, 1.0, 0.0);  //设置背景颜色
	glMatrixMode(GL_PROJECTION);       // 设置投影参数
	gluOrtho2D(0.0, 600.0, 0.0, 400.0); // 设置场景的大小
	CS_LineClip();  //执行一次裁剪算法
	glutDisplayFunc(&mydisplay);//调用绘制函数
	glutMainLoop();
	return 0;
}
