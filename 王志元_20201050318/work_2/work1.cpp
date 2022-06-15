#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>      // (or others, depending on the system in use)

void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    gluOrtho2D(0.0,400.0,0.0,300.0);
}

inline int round (const float a){
    return int(a + 0.5);
}

void setPixel(GLint x,GLint y){
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}

void lineDDA(){
    int x0,xEnd,y0,yEnd;
    x0 = 500;
    xEnd = 10;
    y0 = 200;
    yEnd = 80;

    int dx = xEnd - x0;
    int dy = yEnd - y0;
    int steps;
    int k;

    float xIncrement,yIncrement;
    float x = x0;
    float y = y0;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);

    if(fabs(dx)>fabs(dy)){
        steps = fabs(dx);
    }else{
        steps = fabs(dy);
    }
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

    setPixel(round(x),round(y));
    for(k=0;k<steps;k++){
        x += xIncrement;
        y += yIncrement;
        setPixel(round(x),round(y));
    }
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // 初始 GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //设定显示模式
    glutInitWindowPosition (50, 100);   // 设定窗口位置
    glutInitWindowSize (400, 300);      // 设定窗口大小
    glutCreateWindow ("An Example OpenGL Program"); // 用前面指定参数创建窗口，并定义窗口名称
    init ( );                            // 进行一些初始化工作
    glutDisplayFunc(lineDDA);
    glutMainLoop();
}

