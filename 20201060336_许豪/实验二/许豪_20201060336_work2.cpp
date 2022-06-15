/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include<Windows.h>\
#include<math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

void setPixel(GLint x,GLint y);
int round(float a);
/* GLUT callback Handlers */

void lineDDA(int x0,int y0,int xEnd,int yEnd)
{
    glClear(GL_COLOR_BUFFER_BIT);// 清空显示窗口
    glColor3f(0.0, 0.4, 0.2);// 指定前景色（当前绘制颜色）为蓝色

    int dx=xEnd-x0,dy=yEnd-y0,steps,k;
    float xIncrement,yIncrement,x=x0,y=y0;

    if(abs(dx)>abs(dy))
        steps = abs(dy);
    else
        steps = abs(dx);
    xIncrement = float(dx)/float(steps);
    yIncrement = float (dy)/float(steps);

    setPixel(round(x),round(y));
    for (k=0;k<steps;k++)
    {
        x+=xIncrement;
        y+=yIncrement;
        setPixel(round(x),round(y));
    }
}
void setPixel(GLint x,GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
int round(float a)
{
    return int(a+0.5);
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);// 清空显示窗口

	lineDDA(0, 0, 200000, 200000);
	glFlush();// 使绘制立即反映到屏幕上
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);// 指定清空颜色（背景色）为白色
    glColor3f(1.0, 0.0, 0.0); /* draw in red */
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0); //指定二维坐标系中被显示的区域
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);// 初始 GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//设定显示模式
	glutInitWindowPosition(50, 100);// 设定窗口位置
	glutInitWindowSize(400, 300);// 设定窗口大小
	glutCreateWindow("DDA");// 用前面指定参数创建窗口，并定义窗口名称
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);//指定二维坐标系中被显示的区域

	init(); // 进行一些初始化工作
	glutDisplayFunc(myDisplay);// 指定绘制的回调函数
	glutMainLoop();// 进入无穷循环，等待事件处理

    return 0;
}
