/*改进的Bresenham算法生成直线*/
#include<iostream>
#include<string>
#include<cstdio>
#include<windows.h>
#include <GL/glut.h>
#include<math.h>

int x_1, y_1, x_2, y_2;

void setPixel(int x, int y){
	glPointSize(3.0f);
	glBegin(GL_POINTS);
        glVertex2i(x, y);
	glEnd();
	glFlush();
}

void ChangeSize(GLsizei w, GLsizei h){
    if(h==0)
		h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
    else
        glOrtho(0.0f, 250.0f*w/h, 0.0f,250.0f, 1.0, -1.0);
}

void lineBresenham_2(int x0, int y0, int xEnd, int yEnd){
    int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
    int d = 2 * dx - dy;
    int x = x0, y = y0;

    while(x < xEnd){
        if(d < 0){
            x++;
            y++;
            d += 2*(dx -dy);
        }
        else{
            x++;
            d -= 2*dy;
        }
        setPixel(x, y);
    }
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
	lineBresenham_2(x_1, y_1, x_2, y_2);
}

int main(int argc, char *argv[])
{
    printf("请输入起始位置x0:\n");
    scanf("%d",&x_1);
    printf("请输入起始位置y0:\n");
    scanf("%d",&y_1);
    printf("请输入终止位置xEnd:\n");
    scanf("%d",&x_2);
    printf("请输入终止位置yEnd:\n");
    scanf("%d",&y_2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL's work");

    glutDisplayFunc(&myDisplay);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
    return 0;
}
