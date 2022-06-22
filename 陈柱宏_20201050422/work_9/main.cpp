#include <windows.h>
#pragma once
#define GLUT_DISABLE_ATEXIT_HACK //防止GLUT版本问题出错
#include <GL/glut.h>
int cx = 0, cy = 0, cz = 0;
float m_xRotate = 0, m_yRotate = 0, m_zRotate = 0;
int spin = 0;
void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);		//设置背景颜色为黑色
	glShadeModel(GL_FLAT);
	// glShadeModel选择平坦或光滑渐变模式。GL_SMOOTH为缺省值，为光滑渐变模式，GL_FLAT为平坦渐变模式。
}
void DrawCoordinate()
{
	glLineWidth(2);
	glBegin(GL_LINES);		//开始画线
//绘制一条从原点到x=300的蓝色线段
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(300.0, 0.0, 0.0);

	//绘制一条从原点到y=300的绿色线段
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);

	//绘制一条从原点到z=300的红色线段
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 300.0);
}
void DrawCube()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);		//设置背景颜色为黑色
	glClear(GL_COLOR_BUFFER_BIT);	//用背景颜色替换原有颜色
	glLineWidth(2);
	glBegin(GL_LINES);		//开始画线

	//绘制一条从原点到x=300的蓝色线段
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(300.0, 0.0, 0.0);

	//绘制一条从原点到y=300的绿色线段
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);

	//绘制一条从原点到z=300的红色线段
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 300.0);

	glEnd();	//结束绘制
	glColor3f(1.0, 0.6, 1.0);		//设置颜色为白色
	glutWireCube(100.0f);		//绘制一个边长为100个单位的线框立方体

	glMatrixMode(GL_MODELVIEW);
	//-----在这里填写变换函数，分别实现平移变换、旋转变换和缩放变换
	//1、平移
	glPushMatrix();
	glTranslatef(400.0, 0.0, 0.0);   //沿X方向平移400个单位
	glColor3f(1.0, 0.6, 0.5);		//设置颜色为土色
	glutWireCube(100.0f);		//绘制一个边长为100个单位的线框立方体
	glPopMatrix();
	//2、旋转
	glPushMatrix();
	glTranslatef(150.0, 150.0, 150.0);  //沿坐标系对角线方向平移150个单位
	glRotatef(45, 1.0, 1.0, 1.0);			      //基于对角线方向旋转45度
	glColor3f(1.0, 0.6, 1.0);		//设置颜色为粉色
	glutWireCube(100.0f);		//绘制一个边长为100个单位的线框立方体
	glPopMatrix();

	//3、缩放
	glPushMatrix();
	glTranslatef(300.0, 300.0, 300.0);   //沿坐标系对角线方向平移300个单位
	glScalef(3.0, 3.0, 3.0);					  //对整体放大3倍
	glColor3f(0.6, 1.6, 1.0);		//设置颜色为青色
	glutWireCube(100.0f);	//绘制一个边长为100个单位的线框立方体
	glPopMatrix();
	//-----在这里填写变换函数，分别实现平移变换、旋转变换和缩放变换
	glFlush();
}
void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*if (w <= h)
	{
		glOrtho(-800.0, 800, -800.0 * h/w, 800 * h/w, -800, 800);
	}
	else
	{
		glOrtho(-800.0 * w/h, 800 * w/h, -800.0, 800, -800, 800);
	}*/
	glOrtho(-800.0 * w / h, 800 * w / h, -800.0, 800, -800, 800);

}


void myMouseMotion(GLint x, GLint y)
{
	m_xRotate = cx - x;
	m_yRotate = cy - y;
	cx = x, cy = y;
	glMatrixMode(GL_MODELVIEW);
	glRotatef(m_xRotate, 1.0, 0.0, 0.0);
	glRotatef(m_yRotate, 0.0, 1.0, 0.0);
	glutPostRedisplay();
}
void mykeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case'd':
		spin = spin + 90;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(spin, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case'a':
		spin = spin - 90;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(spin, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case'w':
		spin = spin + 90;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(spin, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case's':
		spin = spin - 90;
		glMatrixMode(GL_MODELVIEW);
		glRotatef(spin, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case'r':
		glLoadIdentity();
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}
}

int  main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);		//初始化颜色模式为RGB
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("三维变换");
	Init();
	glutDisplayFunc(DrawCube);
	glutReshapeFunc(Reshape);
	glutMotionFunc(myMouseMotion);

	glutKeyboardFunc(mykeyboard);
	glutMainLoop();
	return 0;
}
