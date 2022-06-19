#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int x, y, xend, yend;
void setPixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

void BresenhamLine(int x0, int y0, int xend, int yend) {
	int x = x0, y = y0;
	int dx = xend - x0, dy = yend - y0;
	setPixel(x, y);
	if (y0 == yend) {
		while (x < xend) {
			x++;
			setPixel(x, y);
		}
	}
	if (x0 == xend) {
		while (y < yend) {
			y++;
			setPixel(x, y);
		}
	}
	double k = double(dy) / double(dx), e = -0.5;
	if (k < 1.0 && k>0.0) {
		while (x < xend) {
			e += k;
			x++;
			if (e <= 0) continue;
			else {
				y++;
				e--;
			}
			setPixel(x, y);
		}
	}
	if (k > -1.0 && k < 0.0) {
		while (x < xend) {
			e -= k;
			x++;
			if (e <= 0) continue;
			else {
				y--;
				e--;
			}
			setPixel(x, y);
		}
	}
	if (k >= 1.0) {
		double m = 1 / k;
		while (y < yend) {
			e += m;
			y++;
			if (e <= 0) continue;
			else {
				x++;
				e--;
			}
			setPixel(x, y);
		}
	}
	if (k <= -1.0) {
		double m = 1 / k;
		while (y > yend) {
			e -= m;
			y--;
			if (e <= 0) continue;
			else {
				x++;
				e--;
			}
			setPixel(x, y);
		}
	}
}

void init(void) {
	glClearColor(1.0, 0.9, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void lineSegment() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 0.2);
	BresenhamLine(x, y, xend, yend);

	glFlush();
}

int main(int argc, char** argv) {
	printf("请输入起点终点坐标,用空格隔开\n");
	printf("坐标范围0-300，且x0<xend\n");
	scanf_s("%d %d %d %d", &x, &y, &xend, &yend);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(300, 300);
	glutCreateWindow("A modified Bresenham line");

	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();

	return 0;
}