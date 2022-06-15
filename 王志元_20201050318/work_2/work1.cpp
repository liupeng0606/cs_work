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
    glutInit (&argc, argv);                         // ��ʼ GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //�趨��ʾģʽ
    glutInitWindowPosition (50, 100);   // �趨����λ��
    glutInitWindowSize (400, 300);      // �趨���ڴ�С
    glutCreateWindow ("An Example OpenGL Program"); // ��ǰ��ָ�������������ڣ������崰������
    init ( );                            // ����һЩ��ʼ������
    glutDisplayFunc(lineDDA);
    glutMainLoop();
}

