// jiaohushiyan.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include <GL/glut.h>  
#include <math.h>
#define DEG_TO_RAD 0.017453  //角度转为弧度的参数，即 2*PI/360

float theta = 30.0; //直线与X轴正方向的夹角
float length = 200.0;  //直线的长度
float x = 300.0, y = 200.0; //直线的第一个端点

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + length * cos(DEG_TO_RAD * theta),
        y + length * sin(DEG_TO_RAD * theta));
    glVertex2f(x + length * cos(DEG_TO_RAD * (theta + 30)),
        y + length * sin(DEG_TO_RAD * (theta + 30)));
    glEnd();
    glutSwapBuffers();     //交换前后台缓存
}

void idleFunc()
{
    theta += 0.1;
    if (theta > 360) theta -= 360;
    glutPostRedisplay(); //重新调用绘制函数
}
void myMouse(int button, int state, int x, int y)
{
    //按下鼠标左键
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        theta += 5.0;
   
    //按下鼠标右键
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        theta -= 5.0;
    if (theta > 360) theta -= 360;
    if (theta < 0) theta += 360;
    glutPostRedisplay(); //重新调用绘制函数
}
void myKeyboard(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')
        theta += 5.0;
    if (key == 's' || key == 'S')
        theta -= 5.0;
    if (key == 'c' || key == 'C')
        exit(0);
    if (theta > 360) theta -= 360;
    if (theta < 0) theta += 360;
    glutPostRedisplay(); //重新调用绘制函数
}
void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Draw Triangle with Double Buffer");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);           //指定空闲回调函数
    glutMainLoop();
}
