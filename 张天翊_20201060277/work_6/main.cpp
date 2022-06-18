#include<windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<math.h>
#define pi 3.14159
GLfloat square[4][2];

//ƽ��
void Translate(GLfloat Tx,GLfloat Ty)
{
	for(int i=0;i<4;i++){
		square[i][0]+=Tx;
		square[i][1]+=Ty;
	}
    glColor4f(1.0,0.0,0.0,0.1);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(square[0][0],square[0][1]);
		glVertex2f(square[1][0],square[1][1]);
		glVertex2f(square[2][0],square[2][1]);
		glVertex2f(square[3][0],square[3][1]);
	glEnd();
}
//����/����
void Scale(GLfloat Sx,GLfloat Sy)
{
	for(int i=0;i<4;i++){
		square[i][0]*=Sx;
		square[i][1]*=Sy;
	}
	glColor4f(0.0,1.0,0.0,0.1);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(square[0][0],square[0][1]);
		glVertex2f(square[1][0],square[1][1]);
		glVertex2f(square[2][0],square[2][1]);
		glVertex2f(square[3][0],square[3][1]);
	glEnd();
}
//��ת
void Rotate(GLfloat degree)
{
	for(int i=0;i<4;i++){
		int tmpX=square[i][0],tmpY=square[i][1];
		square[i][0]=tmpX*cos(degree)-tmpY*sin(degree);
		square[i][1]=tmpX*sin(degree)+tmpY*cos(degree);
	}
	glColor4f(0.0,0.0,1.0,0.1);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(square[0][0],square[0][1]);
		glVertex2f(square[1][0],square[1][1]);
		glVertex2f(square[2][0],square[2][1]);
		glVertex2f(square[3][0],square[3][1]);
	glEnd();
}
//�Գ�
void Symmetry(int flag)
{
	for(int i=0;i<4;i++){
		if(flag){//����1����x��Գ�
			square[i][1]*=-1;
		}else{//����0����y��Գ�
			square[i][0]*=-1;
		}
	}
    glColor4f(1.0,1.0,0.0,0.1);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(square[0][0],square[0][1]);
		glVertex2f(square[1][0],square[1][1]);
		glVertex2f(square[2][0],square[2][1]);
		glVertex2f(square[3][0],square[3][1]);
	glEnd();
}

void myinit()//��ʼ�������ζ�������
{
	square[0][0]=-100.0;
	square[0][1]=100.0;
	square[1][0]=100.0;
	square[1][1]=100.0;
	square[2][0]=100.0;
	square[2][1]=-100.0;
	square[3][0]=-100.0;
	square[3][1]=-100.0;

}

void reshape(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);//�����ӿڴ�С����ʼ���봰��һ��

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400,400,-400,400);
}

void display()
{
	//���ñ�����ɫΪ��ɫ�������ɫ����
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//��������
	glColor4f(0.0,0.0,0.0,0.1);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(square[0][0],square[0][1]);
		glVertex2f(square[1][0],square[1][1]);
		glVertex2f(square[2][0],square[2][1]);
		glVertex2f(square[3][0],square[3][1]);
	glEnd();

    Scale(1.5,1.5);//����

	Translate(100, 100);//ƽ��
    Rotate(pi/3);//��ת
    Symmetry(1);//�Գ�

	glutSwapBuffers();//����ǰ�󻺳���
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);//��ʼ��OPENGL��ʾ��ʽ
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (600, 600); //�趨OPENGL����λ�úʹ�С
	glutCreateWindow ("��ά���α任");//�򿪴���
    myinit();//���ó�ʼ������

	glutReshapeFunc(reshape);//�趨���ڴ�С�仯�Ļص�����

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
