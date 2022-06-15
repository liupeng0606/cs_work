#include<windows.h>
#include <gl/glut.h>
#pragma comment(lib, "glut32.lib")

#define NO 0
#define YES 1

int Drawing;

void Initialization()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);

	glEnable(GL_POINT_SMOOTH);           //���õ㷴����
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);            //����ֱ�߷���������ʼ�������������õ���3�����������������
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);


	Drawing = NO;
}

void OnDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (Drawing == YES)		//���û��״̬����ʼ�������������õ���3�����������������
	{
		glEnable(GL_BLEND);
	}
	else					//�رջ��״̬
	{
		glDisable(GL_BLEND);
	}
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //��ǰ��ͼɫΪ��ɫ

	glLineWidth(10);
	glBegin(GL_LINE_STRIP);
	{
		glVertex2f(-3.0f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(3.0f, -0.5f);
	}
	glEnd();

	glPointSize(10);
	glBegin(GL_POINTS);
	{
		glVertex2f(0.0f, 1.0f);
	}
	glEnd();

	glutSwapBuffers();
}

void OnReShape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //����ǰ����ָ��ΪͶӰģʽ
	glLoadIdentity();

	if (h != 0)
	{
		GLfloat aspect = (float)w / (float)h;

		if (w < h)
		{
			gluOrtho2D(-3, 3, -3 * aspect, 3 * aspect);
		}
		else
		{
			gluOrtho2D(-3 / aspect, 3 / aspect, -3, 3);
		}
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Createmenu(void)
{
	glutAddMenuEntry("������ʾ", NO);
	glutAddMenuEntry("������", YES);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void OnMenu(int value)
{
	Drawing = value;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	glutCreateWindow("OpenGL������");

	glutReshapeFunc(OnReShape);
	glutDisplayFunc(OnDisplay);
	glutCreateMenu(OnMenu);

	Initialization();
	CreateMenu();


	glutMainLoop();
}
