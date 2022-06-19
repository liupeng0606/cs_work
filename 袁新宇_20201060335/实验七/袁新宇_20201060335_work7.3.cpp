#include <GL/glut.h>
#include <stdio.h>
#include<stdlib.h>

static float rotAngle = 0.;

void init(void){
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	glLineWidth(1.5);

	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void init2(void) {
	glLineWidth(1.5);

	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glRotatef(rotAngle, 0.0, 0.0, 0.1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.75, 0.75);
	glVertex2f(-0.75, 0.55);
	glVertex2f(-0.80, 0.0);
	glEnd();
	glPopMatrix();

	glFlush();
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
	case 'r': case 'R':
		rotAngle += 20.;
		if (rotAngle >= 360.0) rotAngle = 0.0;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv){
	int i;
	printf("输入i=0:反走样之前的图像,i=1:反走样之后的图像\n");
	scanf_s("%d", &i);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutCreateWindow(argv[0]);
	if(i==0) init2();
    else init();;
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
