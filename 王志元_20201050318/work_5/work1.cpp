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
    ����
*/
void setPixel(int x, int y)
{
    glColor3f(0.0, 1.0, 2.0);       // ��ɫ
    glPointSize(2.0f);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
    glFlush();
}

/*
    8·�Գ�
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
    �е㻭Բ�㷨
*/
void MidPoint_Circle(int x0, int y0, int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r;      // d = 1.25-r��ȡ���Ľ��
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

// ���ڴ�С�ı�ʱ���õĵǼǺ���
void ChangeSize(GLsizei w, GLsizei h)
{

    if (h == 0)     h = 1;

    // ���������ߴ�
    glViewport(0, 0, w, h);

    // ��������ϵͳ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // �����޼��ռ�ķ�Χ
    if (w <= h)
        glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h / w, 1.0, -1.0);
    else
        glOrtho(0.0f, 250.0f*w / h, 0.0f, 250.0f, 1.0, -1.0);
}

/*

*/
void display(void)
{
    // �õ�ǰ����ɫ��䴰�ڣ������д�������֮ǰ��ͼ��
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
