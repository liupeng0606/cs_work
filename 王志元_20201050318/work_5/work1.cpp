#include <windows.h>
#include<GL\glut.h>
#include<iostream>
#include<cmath>
#include <stdio.h>

using namespace std;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
    glMatrixMode(GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

/*
    画点
*/
void setPixel(int x, int y)
{
    glColor3f(0.0, 1.0, 2.0);       // 蓝色
    glPointSize(2.0f);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
    glFlush();
}

/*
    8路对称
*/
void Cirpot(int x0, int y0, int x, int y)
{
    // 1
    setPixel((x0 + x), (y0 + y));
    // 2
    setPixel((x0 + y), (y0 + x));
    // 3
    setPixel((x0 + y), (y0 - x));
    // 4
    setPixel((x0 + x), (y0 - y));
    // 5
    setPixel((x0 - x), (y0 - y));
    // 6
    setPixel((x0 - y), (y0 - x));
    // 7
    setPixel((x0 - y), (y0 + x));
    // 8
    setPixel((x0 - x), (y0 + y));
}

/*
    中点画圆算法
*/
void MidPoint_Circle(int x0, int y0, int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r;      // d = 1.25-r的取整的结果
    Cirpot(x0, y0, x, y);
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
        Cirpot(x0, y0, x, y);
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
    // 用当前背景色填充窗口，如果不写这句会残留之前的图像
    glClear(GL_COLOR_BUFFER_BIT);

    int x0 = 100, y0 = 100, r = 80;
    MidPoint_Circle(x0, y0, r);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("MidCircle");
    glutDisplayFunc(display);
    glutReshapeFunc(ChangeSize);
    init();
    glutMainLoop();
    return 0;
}
