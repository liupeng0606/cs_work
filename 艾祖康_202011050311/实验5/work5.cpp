//#include <math.h>
#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
using namespace std;
#define pi 3.1415926
void init(void){
    glClearColor(1.0,1.0,1.0,0.0);// 使背景变白
    glMatrixMode(GL_PROJECTION);//设置投影参数s.
    gluOrtho2D(0.0,200.0,0.0,150.0);//设置窗口的位置和大小
}
void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h / w, 1.0, -1.0);
	else
		glOrtho(0.0f, 250.0f*w / h, 0.0f, 250.0f, 1.0, -1.0);
}
//设置点的参数，描述点与其他点的关系
void CirclePoint(int x0,int y0,int x,int y){
    //set the color of the points
    glColor3f(0.0, 0.0, 1.0);
    //draw these circle in a special turn
    glVertex2f(x, y);
    glVertex2f(y - (y0 - x0), x + (y0 - x0));
	glVertex2f(y - (y0 - x0), x0 + y0 - x);
	glVertex2f(x, 2 * y0 - y);
	glVertex2f(2 * x0 - x, 2 * y0 - y);
	glVertex2f(x0 + y0 - y, x0 + y0 - x);
	glVertex2f(x0 + y0 - y, x + (y0 - x0));
	glVertex2f(2 * x0 - x, y);
}
//中间画圆算法，x0,y0是圆心，r是圆的半径
void MidPointCircle(int x0,int y0,int r){
    glColor3f(0.0, 0.0, 1.0);  //将点的颜色设置为蓝色
	glPointSize(2.0f);        //设置点的大小
	glVertex2f(x0, y0);        //画心
	int x, y;
	int d,b;
	x = x0; y = r + y0; d = 5 - 4 * r; b = y0 - x0;
	CirclePoint(x0, y0, x, y);
	while (x + b <= y)
	{
		if (d < 0)
			d += 8*(x - x0) + 12;
		else {
			d += 8*x - 8*y + 8*b + 16;
			y--;
		}
		x++;
		CirclePoint(x0, y0, x, y);
	}
}
void display()
{
	int x1_1 = 20, y1_1 = 20, x2_1 = 160, y2_1 = 80;
	int x1_2 = 20, y1_2 = 40, x2_2 = 160, y2_2 = 100;
	int x1_3 = 20, y1_3 = 60, x2_3 = 160, y2_3 = 120;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	MidPointCircle(80, 60, 60);
	glEnd();
	glBegin(GL_POINTS);
	MidPointCircle(80, 80, 60);
	glEnd();
	glFlush();
}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,300);
    glutCreateWindow("draw a circle");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}

