#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void line_Bres(int x0, int y0, int xEnd, int yEnd) {
	int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
	int p = dx - 2 * dy;
	int pp = dy - 2 * dx;
	int twoDy = -2 * dy, twoDxMinusDy = 2 * (dx - dy);
	int twoDx = -2 * dx, twoDyMinusDx = 2 * (dy - dx);
	int x, y;
	float k = (yEnd - y0) / (xEnd - x0);
	if (x0 > xEnd) {
		x = xEnd; y = yEnd; xEnd = x0;
	}
	else { x = x0; y = y0; }
	setPixel(x, y);
	while (x < xEnd) {
		if (k >= 0 && k <= 1) {
			x++;
			if (p < 0) {
				y++; p = p + twoDxMinusDy;
			}
			else
				p = p + twoDy;
			setPixel(x, y);
		}
		if (k > 1) {
			y++;
			if (pp < 0) {
				x++; pp = pp + twoDyMinusDx;
			}
			else
				pp = pp + twoDx;
			setPixel(x, y);
		}
		if (k<0 && k>-1) {
			x++;
			if (p < 0) {
				y--; p = p + twoDxMinusDy;
			}
			else
				p = p + twoDy;
			setPixel(x, y);
		}
		if (k < -1) {
			y++;
			if (pp < 0) {
				x--; pp = pp + twoDyMinusDx;
			}
			else
				pp = pp + twoDx;
			setPixel(x, y);
		}
	}
}
void display(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 300);
	line_Bres(0, 0, 500, 300);
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(" Bres_line");
	glutDisplayFunc(display);
	glColor3f(0.0, 1.0, 1.0);//颜色
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutMainLoop();
	return 0;
}