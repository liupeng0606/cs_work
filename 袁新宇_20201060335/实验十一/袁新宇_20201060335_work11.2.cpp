#include <GL/glut.h>  
#include <math.h>
#include<stdlib.h>
#define DEG_TO_RAD 0.017453  //角度转为弧度的参数，即 2*PI/360

float theta = 30.0; //直线与X轴正方向的夹角
float length = 200.0;  //直线的长度
float x = 300.0, y = 200.0; //直线的第一个端点
int dir = 1;
int flag = 1;

void init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + length * cos(DEG_TO_RAD * theta),
        y + length * sin(DEG_TO_RAD * theta));
    glVertex2f(x + length * cos(DEG_TO_RAD * (theta + 30)),
        y + length * sin(DEG_TO_RAD * (theta + 30)));
    glEnd();
    glutSwapBuffers();     //交换前后台缓存
}

void idleFunc(){
    theta += 0.1;
    if (theta > 360) theta -= 360;
    glutPostRedisplay(); //重新调用绘制函数
}

void myKey(unsigned char key, int x, int y){ //键盘
    if (key == ' ') {
        flag ^= 1;
        if (flag)glutIdleFunc(idleFunc);

        else glutIdleFunc(NULL);
    }
    if (key == 'a' || key == 'A')
        theta += 5.0;
    if (key == 's' || key == 'S')
        theta -= 5.0;
    if (theta > 360) theta -= 360;
    if (theta < 0) theta += 360;
    if (key == 'c' || key == 'C')
        exit(0);
    glutPostRedisplay(); //重新调用绘制函数

}

void myKeyboard(unsigned char key, int x, int y){
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

void mySpecialKeyboard(int key, int x, int y){
    if (key == GLUT_KEY_F1 || key == GLUT_KEY_LEFT)
        theta += 5.0;
    x += 100;
    if (key == GLUT_KEY_F2 || key == GLUT_KEY_RIGHT)
        theta -= 5.0;
    if (theta > 360) theta -= 360;
    if (theta < 0) theta += 360;
    glutPostRedisplay(); //重新调用绘制函数
}

void main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Draw Triangle with Single Buffer");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    glutSpecialFunc(mySpecialKeyboard);
    glutIdleFunc(idleFunc);             //指定空闲回调函数
    glutMainLoop();
}