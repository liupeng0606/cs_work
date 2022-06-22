#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
    gluOrtho2D(0.0,400.0,0.0,300.0);
}

void setPixel(GLint x,GLint y){
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}

void lineBres(){
    int x0 = 100;
    int y0 = 1;
    int xEnd = 10;
    int yEnd = 100;

    int dx = fabs(xEnd - x0);
    int dy = fabs(yEnd - y0);
    int p = 2*dy - dx;
    int twoDy = 2*dy;
    int twoDyMinusDx = 2*(dy - dx);
    int x,y;

    if(x0>xEnd){
        x = xEnd;
        y = yEnd;
        xEnd = x0;
    }else{
        x = x0;
        y = y0;
    }
    setPixel(x,y);
    while(x<xEnd){
        x++;
        if(p<0){
            p+=twoDy;
        }else{
            y++;
            p+=twoDyMinusDx;
        }
        setPixel(x,y);
    }
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // ��ʼ GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //�趨��ʾģʽ
    glutInitWindowPosition (50, 100);   // �趨����λ��
    glutInitWindowSize (400, 300);      // �趨���ڴ�С
    glutCreateWindow ("An Example OpenGL Program"); // ��ǰ��ָ�������������ڣ������崰������
    init ( );  // ����һЩ��ʼ������
    glutDisplayFunc(lineBres);
    glutMainLoop();
}
