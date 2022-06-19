#include<GL\glut.h>
#include<stdio.h>
GLsizei winWidth = 500, winHeight = 500;
char sixel;
float thera = 0;
float x = 0, y = 0, z = 0;
void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void displayWirePolyhedra(float x, float y, float z, float thera) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	glTranslatef(1.0, 2.0, 0.0);//下一个图形坐标
	glutSolidTeapot(1.5);
	//glutWireTeapot(1.5);//放大倍数
	glScalef(1.0, 1.0, 1.0);//缩放比
	glTranslatef(-1.0, -5.0, 0.0);//下一个图形坐标

	glRotatef(thera, x, y, z);
	glutWireTeapot(1.5);
	//glutSolidTeapot(2.0);
	glFlush();
}

void display() {
	displayWirePolyhedra(x, y, z, thera);
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
}

void main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("   ");
	init();
	printf("请选择绕拿一个轴旋转x,y,z \n");
	scanf_s("%c", &sixel);
	getchar();
	if (sixel == 'x') {
		x = 1.0;
		y = 0.0;
		z = 0.0;
		printf("请输入旋转的角度\n");
		scanf_s("%f", &thera);
	}
	else if (sixel == 'y') {
		x = 0.0;
		y = 1.0;
		z = 0.0;
		printf("请输入旋转的角度\n");
		scanf_s("%f", &thera);
	}
	else if (sixel == 'z') {
		x = 0.0;
		y = 0.0;
		z = 1.0;
		printf("请输入旋转的角度\n");
		scanf_s("%f", &thera);
	}
	else {
		printf("输入有误\n");
	}
	glutDisplayFunc(display);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}