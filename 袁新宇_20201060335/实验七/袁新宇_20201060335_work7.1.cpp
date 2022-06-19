#include<GL/glut.h>

GLsizei winWidth = 400, winHeight = 300;

void init(void) {
	glClearColor(0.0, 0.0, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void displayFunc(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth),0.0, GLdouble(newHeight));

	winWidth = newWidth;
	newHeight = newHeight;
}

void plotPoint(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		plotPoint(xMouse, winHeight - yMouse);
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);//初始化GLUT 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//设置显示模式 
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth,winHeight);//设置显示窗口的高和宽 
	glutCreateWindow("Mouse Plot Points");//创建显示窗口 

	init();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mousePtPlot);
	glutMainLoop();
}