#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>

//初始化函数
void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);          //指定刷新颜色缓冲区时所用的颜色。
    glMatrixMode(GL_PROJECTION);               //对接下来要做什么进行一下声明
    gluOrtho2D(0.0,200.0,0.0,150.0);       // 用来指定屏幕区域对应的模型坐标范围
}
//画直线的主要代码
void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT);      //当前缓冲区清除值
    glColor3f(0.0,0.4,0.2); 
    glBegin(GL_LINES);
      glVertex2i(180,15);
      glVertex2i(10,145);
    glEnd();
    glFlush();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);          //在创建窗口的时候，指定其显示模式的类型
    glutInitWindowPosition(50,100);             //指定窗口的位置
    glutInitWindowSize(400,300);               //指定窗口的大小
    glutCreateWindow("示例直线段");
    init();
    glutDisplayFunc(lineSegment);     //调用display函数
    glutMainLoop();
    return 0;
}

