#include <GL/glut.h> 

GLfloat angle = 10.0f;
GLfloat xDirection = 0.0f;
GLfloat yDirection = 0.0f;
GLfloat zDirection = 10.0f;

void InitEnvironment()
{
	glEnable(GL_DEPTH);
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(0, 0, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65, 1, 1, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xDirection, yDirection, zDirection, 0, 0, 0, 0, 1, 0);
}

void KeyBoards(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		glMatrixMode(GL_MODELVIEW);
		glRotatef(angle, -1, 0, 0);
		glutPostRedisplay();
		break;
	case 'a':
		glMatrixMode(GL_MODELVIEW);
		glRotatef(angle, 0, 0, -1);
		glutPostRedisplay();
		break;
	case 's':
		glMatrixMode(GL_MODELVIEW);
		glRotatef(angle, 1, 0, 0);
		glutPostRedisplay();
		break;
	case 'd':
		glMatrixMode(GL_MODELVIEW);
		glRotatef(angle, 0, 0, 1);
		glutPostRedisplay();
		break;
	case '4':
		xDirection += 0.5;

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(65, 1, 1, 50);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(xDirection, yDirection, zDirection, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case '5':
		yDirection += 0.5;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(65, 1, 1, 50);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(xDirection, yDirection, zDirection, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;

	case '6':
		zDirection += 0.5;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(65, 1, 1, 50);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(xDirection, yDirection, zDirection, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;

	case '1':
		xDirection -= 0.5;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(65, 1, 1, 50);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(xDirection, yDirection, zDirection, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case '2':
		xDirection -= 0.5;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(65, 1, 1, 50);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(xDirection, yDirection, zDirection, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case '3':
		xDirection -= 0.5;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluPerspective(65, 1, 1, 50);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(xDirection, yDirection, zDirection, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutWireTeapot(4);
	glutSwapBuffers();
}

void RotateRect()
{
	angle += 0.5;
	if (angle >= 360)
	{
		angle = 0.0f;
	}
	Sleep(30);
	myDisplay();
}

void OnMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(RotateRect);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(NULL);
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);   //初始化GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow("OpenGL");
	InitEnvironment();   //初始化显示环境
	glutKeyboardFunc(&KeyBoards);  //注册键盘事件
	glutDisplayFunc(&myDisplay);   //回调函数 
	glutMainLoop();    //持续显示，当窗口改变会重新绘制图形
	return 0;
}