#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
inline int round(const float a) {
	return int(a + 0.5);
}
void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void line_DDA(int x0, int y0, int xEnd, int yEnd) {
	int dx = xEnd - x0, dy = yEnd - y0, steps, k;
	float xIncrement, yIncrement, x = x0, y = y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	xIncrement = float(dx) / float(steps);
	yIncrement = float(dy) / float(steps);
	setPixel(round(x), round(y));
	for (k = 0; k < steps; k++) {
		x = x + xIncrement;
		y = y + yIncrement;
		setPixel(round(x), round(y));
	}
}
void display(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	line_DDA(0, 0, 500, 500);
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("DDA_line ");
	glutDisplayFunc(display);
	glColor3f(0.0, 1.0, 1.0);//颜色
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutMainLoop();
	return 0;
}