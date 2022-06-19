#include<GL/glut.h>
#include <stdlib.h>

GLsizei winWidth = 400, winHeight = 300;
GLint endPtCtr = 0;

class scrPt {
public:
	GLint x, y;
};

void init(void) {
	glClearColor(0.0, 0.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void displayFunc(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.3, 1.0, 0.0);
	glPointSize(3.0);
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));

	winWidth = newWidth;
	newHeight = newHeight;
}

void drawLineSegment(scrPt endPt1, scrPt endPt2) {
	glBegin(GL_LINES);
	glVertex2i(endPt1.x, endPt1.y);
	glVertex2i(endPt2.x, endPt2.y);
	glEnd();
}

void polyLine(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	static scrPt endPt1, endPt2;
	if (endPtCtr == 0) {
		if (button == GLUT_LEFT && action == GLUT_DOWN) {
			endPt1.x = xMouse;
			endPt1.y = winHeight - yMouse;
			endPtCtr = 1;
		}
		else {
			if (button == GLUT_RIGHT_BUTTON) exit(0);
		}
	}
	else {
		if (button == GLUT_LEFT && action == GLUT_DOWN) {
			endPt2.x = xMouse;
			endPt2.y = winHeight - yMouse;
			drawLineSegment(endPt1, endPt2);

			endPt1 = endPt2;
		}
		else
		if (button == GLUT_RIGHT_BUTTON) exit(0);
	}
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(winWidth,winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Draw Interaction Polyline");

	init();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(polyLine);
	glutMainLoop();

	return 0;
}