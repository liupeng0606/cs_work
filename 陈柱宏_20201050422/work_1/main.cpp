#include <GL/glut.h>      // (or others, depending on the system in use)
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // 指定清空颜色（背景色）为白色
    gluOrtho2D(0.0, 400.0, 0.0, 300.0);   //指定二维坐标系中被显示的区域
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  // 清空显示窗口
    glColor3f(0.0, 0.0, 1.0);      // 指定前景色（当前绘制颜色）为蓝色
    glBegin(GL_LINES);
    glVertex2i(180, 15);       // 指定顶点
    glVertex2i(10, 145);
    glEnd();
    glFlush();     // 使绘制立即反映到屏幕上
}
void main(int argc, char** argv)
{
    glutInit(&argc, argv);                         // 初始 GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //设定显示模式
    glutInitWindowPosition(50, 100);   // 设定窗口位置
    glutInitWindowSize(400, 300);      // 设定窗口大小
    glutCreateWindow("An Example OpenGL Program"); // 用前面指定参数创建窗口，并定义窗口名称
    init();                            // 进行一些初始化工作
    glutDisplayFunc(display);       // 指定绘制的回调函数
    glutMainLoop();          // 进入无穷循环，等待事件处理
}
