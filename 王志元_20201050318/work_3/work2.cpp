#include <windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;

void setPixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void lineBres() {
	int x0, y0, xEnd, yEnd;
	x0 = 50;
	y0 = 100;
	xEnd = 500;
	yEnd = 380;
	int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
	float k = dy / (dx * 1.0), d = 0;
	int x, y;
	x = x0; y = y0;
	setPixel(x, y);
	while (x < xEnd) {
		x++;
		d = d + k;
		if (d >= 0.5) { y++; d = d - 1; }
		setPixel(x, y);
	}
}

void display(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	lineBres();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                         // ��ʼ GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //�趨��ʾģʽ
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("lineBres"); // ��ǰ��ָ�������������ڣ������崰������
	glutDisplayFunc(display);       // ָ�����ƵĻص�����
	glColor3f(0.0, 0.0, 1.0);//��ɫ
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutMainLoop();
	return 0;
}
