#include<GL/glut.h>
#include<stdio.h>

int x, y, r;

class screenPt {
    private:
	    GLint x, y;
    public:
		screenPt() {
			x = y = 0;
		}
	void setCoords(GLint xCoord, GLint yCoord) {
		x = xCoord;
		y = yCoord;
	}
	GLint getx() const {
		return x;
	}
	GLint gety() const {
		return y;
	}
	void incrementx() {
		x++;
	}
	void decrementy() {
		y--;
	}
};

void setPixel(GLint xCoord, GLint yCoord) {
	glBegin(GL_POINTS);
	glVertex2i(xCoord, yCoord);
	glEnd();
}

void circleMidpoint(GLint xc, GLint yc, GLint radius) {
	screenPt circPt;
	GLint p = 1 - radius;
	circPt.setCoords(0, radius);

	void circlePlotPoints(GLint, GLint, screenPt);
	circlePlotPoints(xc, yc, circPt);

	while (circPt.getx() < circPt.gety()) {
		circPt.incrementx();
		if (p < 0)
			p += 2 * circPt.getx() + 1;
		else {
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt) {
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}

void init(void) {
	glLineWidth(2.5);
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-300.0, 300.0, -300.0, 300.0);
}

void lineSegment() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	circleMidpoint(x,y,r);

	glFlush();
}

int main(int argc, char** argv) {
	printf("坐标范围：-300<=x<=300,-300<=y<=300\n");
	printf("请依次输入圆心的坐标以及圆的半径:\n");
	scanf_s("%d %d %d", &x, &y, &r);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("A MidPlot circle");

	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();

	return 0;
}