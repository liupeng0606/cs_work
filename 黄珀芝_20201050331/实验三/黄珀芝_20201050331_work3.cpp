#include<windows.h> //我将bresenham算法和dda算法放在一起了，这里已经注释掉dda算法，调用的是breasenham算法
#include<GL\glut.h>
#include<iostream>
#include<cmath>
#include <stdio.h>
using namespace std;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

/*
    数值微分方法画线

void LineDDA(int x1, int y1, int x2, int y2)
{


    glColor3f(1.0, 0.0, 0.0);       // 红色
    glPointSize(2.0f);

    /*
        两点重合尚未判断


    int dm = 0;
    if (abs(x2 - x1) >= abs(y2 - y1))
    {
        dm = abs(x2 - x1);
    }
    else
    {
        dm = abs(y2 - y1);
    }
    float dx = (float)(x2 - x1) / dm;
    float dy = (float)(y2 - y1) / dm;
    float x = x1;
    float y = y1;

    for (int i = 0; i < dm; ++i)
    {
        glBegin(GL_POINTS);
        glVertex2f((int)x, (int)y);
        glEnd();
        glFlush();
        x += dx;
        y += dy;
    }
}*/



/*
    交换两个int 类型的变量的值
*/
void swap_value(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*
    Bresenham 画线法
*/
void LineBres(int x1, int y1, int x2, int y2)
{
    glColor3f(0.0, 0.0, 1.0);       // 蓝色
    glPointSize(2.0f);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    // 两点重合
    if (dx == 0 && dy == 0)
    {
        glBegin(GL_POINTS);
            glVertex2f(x1, y1);
        glEnd();
        glFlush();
        return ;
    }

    int flag = 0;       // 将斜率变换到 0 <= |k| <= 1 区间
    if (dx < dy)
    {
        flag = 1;
        swap_value(&x1, &y1);
        swap_value(&x2, &y2);
        swap_value(&dx, &dy);
    }

    int tx = (x2 - x1) > 0 ? 1 : -1;
    int ty = (y2 - y1) > 0 ? 1 : -1;
    int curx = x1;
    int cury = y1;
    int dS = 2 * dy;
    int dT = 2 * (dy - dx);
    int d = dS - dx;
    while (curx != x2)
    {
        if (d < 0)
            d += dS;
        else
        {
            cury += ty;
            d += dT;
        }

        if (flag)
        {
            glBegin(GL_POINTS);
                glVertex2f(cury, curx);
            glEnd();
            glFlush();
        }
        else
        {
            glBegin(GL_POINTS);
                glVertex2f(curx, cury);
            glEnd();
            glFlush();
        }
        curx += tx;
    }

}

// 窗口大小改变时调用的登记函数
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
        glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h / w, 1.0, -1.0);
    else
        glOrtho(0.0f, 250.0f*w / h, 0.0f, 250.0f, 1.0, -1.0);

}

/*

*/
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    int x1 = 20, y1 = 20, x2 = 160, y2 = 80;

   // LineDDA(x1, y1, x2, y2);
    LineBres(x1, y1, x2, y2);
}

int main(int argc, char* argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Line");

    glutDisplayFunc(&display);

    glutReshapeFunc(ChangeSize);
    init();
    glutMainLoop();
    return 0;
}
