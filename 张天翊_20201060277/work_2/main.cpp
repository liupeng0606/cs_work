/*DDA算法生成直线*/
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

int round(const float a){
	return int(a+0.5);
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

void lineDDA(int x0, int y0, int xEnd, int yEnd){
    glPointSize(1.0f);
    int dx=xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;

    if(fabs(dx) > fabs(dy))//斜率绝对值小于1
        steps = fabs(dx);
    else
        steps = fabs(dy);
    xIncrement = float (dx)/float (steps);
    yIncrement = float (dy)/float (steps);

    setPixel(round (x),round (y));
    for(k = 0; k < steps; k++){
        x += xIncrement;
        y += yIncrement;
        setPixel(round (x),round (y));
    }
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
	lineDDA(x_1, y_1, x_2, y_2);
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
