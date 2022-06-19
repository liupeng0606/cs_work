#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

int x, y, xEnd, yEnd;

void setPixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}

void BresenhamLine(int x0, int y0, int xend, int yend) {
	int x = x0, y = y0, p;
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
	double k = double(dy) / double(dx);
	if (k < 1.0 && k>0.0) {
		p = 2 * dy - dx;
		while (x < xend) {
			x++;
			if (p < 0) p += 2 * dy;
			else {
				y++;
				p = p + 2 * dy - 2 * dx;
			}
			setPixel(x, y);
		}
	}
	if (k >= 1.0) {
		p = dy;
		while (y < yend) {
			y++;
			if (p < 0) p += 2 * dx;
			else {
				x++;
				p = p + 2 * dx - 2 * dy;
			}
			setPixel(x, y);
		}
	}
	if (k > -1.0 && k < 0.0) {
		p = 2 * dy + dx;
		while (x < xend) {
			x++;
			if (p >= 0) p += 2 * dy;
			else {
				y--;
				p = p + 2 * dy + 2 * dx;
			}
			setPixel(x, y);
		}
	}
	if (k <= -1.0) {
		p = 2 * dx - dy;
		while (y > yend) {
			y--;
			if (p >= 0) p -= 2 * dx;
			else {
				x++;
				p = p - 2 * dx - 2 * dy;
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
	BresenhamLine(x, y, xEnd, yEnd);

	glFlush();
}

int main(int argc, char** argv) {
	printf("请分别输入起点、终点坐标，中间用空格隔开\n");
	printf("取值范围为0-300\n");
	scanf_s("%d %d %d %d", &x, &y, &xEnd, &yEnd);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(300, 300);
	glutCreateWindow("A Bresenham line");

	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();

	return 0;
}