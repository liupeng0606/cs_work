
/*使用DDA算法画线*/
#include<iostream>
using namespace std;

#include<windows.h>
#include<math.h>
#include<gl/glut.h>

void myDisplay(void);//用这个函数来调用lineDDA
void setPixel(int x,int y);//教科书里画点的函数，在OpenGL中可以用glVertex来实现
double round(double x);
void ChangeSize(GLsizei w, GLsizei h);
void lineDDA(int x0,int y0,int xEnd,int yEnd);

void myDisplay(void)
{
    //glClear(GL_COLOR_BUFFER_BIT);//好像没这句话也可以啊。。初学好迷=。=
    lineDDA(50,50,200,200);
}

void setPixel(int x,int y)
{
    //用OpenGL自己的函数实现书上的setPixel
    //glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

double round(double x)
{
    return (int)(x+0.5);
}

//窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
    if(h==0)
        h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(0.0f,250.0f,0.0f,250.0f*h/w,1.0,-1.0);
    else
        glOrtho(0.0f,250.0f*w/h,0.0f,250.0f,1.0,-1.0);
}

void lineDDA(int x0,int y0,int xEnd,int yEnd)
{
    glPointSize(3.0f);//设置像素点大小
    int dx=xEnd-x0,dy=yEnd-y0,steps,k;
    float xIncrement,yIncrement,x=x0,y=y0;
    if(abs(dx)>abs(dy))//确定步长，谁大就取谁
        steps=abs(dx);
    else
        steps=abs(dy);
    xIncrement=float(dx)/float(steps);//增量当中有一个会为1，另一个会为斜率k
    yIncrement=float(dy)/float(steps);
    setPixel(round(x),round(y));//由于每次都加了小于1的增量，所以需要取整
    for(k=0; k<steps; k++)
    {
        x+=xIncrement;
        y+=yIncrement;
        setPixel(round(x),round(y));
    }
}

int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(400,400);
    glutCreateWindow("Daily Practice");
    glutDisplayFunc(&myDisplay);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();
    return 0;
}
