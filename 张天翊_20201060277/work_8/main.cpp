#include <windows.h>
#include <GL/glut.h>
#include <cstdio>
#define LEFT 1//0001
#define RIGHT 2//0010
#define BOTTOM 4//0100
#define TOP 8//1000
int x_1, y_1, x_2, y_2;//(x1,y1)��(x2,y2)Ϊֱ�߶εĶ˵�
int XL = 100, XR = 300, YB = 100, YT = 200;  //XLΪ��߽磬XRΪ�ұ߽磬YBΪ�±߽磬YTΪ�ϱ߽�
int x1_init, y1_init, x2_init, y2_init;  //�߶ζ˵�ı���
void encode(int x, int y,int &c)
{//|������������һ��Ϊ1�����Ϊ1
	c = 0;
	if (x < XL) c |= LEFT;//�������ֽ��л����㣬��߽�
	else if (x > XR) c |= RIGHT;//�ұ߽�
	if (y < YB) c |= BOTTOM;//�±߽�
	else if (y > YT) c |= TOP;//�ϱ߽�
}
//����:1001; ����:0001; ����:0101;
//����:1000; ����:0000 ����:0100
//����:1010  ����:0010  ����:0110
void CS_LineClip()  //Cohen-Sutherland�ü��㷨
{
	int x, y;
	int code1, code2, code;
    encode(x_1, y_1, code1);//������˵����ڵ�����
    encode(x_2, y_2, code2);//������˵����ڵ�����
	//ѭ������
	while (code1 != 0 || code2 != 0)//ֻ�������˵�ͬʱ���ھ���������Ų�ʹ�ú���
	{
		if (code1 & code2)//������Ϊ1�ų���������������ͬһ�������� ֱ�Ӳ����д���
			return;
		if (code1 != 0)//���
			code = code1;
		else
			code = code2;

		if (LEFT & code)//�߶�����߽��ཻ(���
		{
			x = XL;//�������߽�Ľ����xֵ
			y = y_1 + (y_2 - y_1)*(XL - x_1) / (x_2 - x_1);//�����߽����yֵ
		}
		else if (RIGHT & code)//�߶����ұ߽��ཻ
		{
			x = XR;//����ұ߽�Ľ����xֵ
			y = y_1 + (y_2 - y_1)*(XR - x_1) / (x_2 - x_1);//����б�ʼ�����ұ߽�Ľ����yֵ
		}
		else if (BOTTOM & code)//�߶����±߽��ཻ
		{
			y = YB;//����±߽�Ľ����yֵ
			x = x_1 + (x_2 - x_1)*(YB - y_1) / (y_2 - y_1);//����±߽�Ľ����xֵ����б��
		}
		else if (TOP & code)//�߶����ϱ߽��ཻ
		{
			y = YT;
			x = x_1 + (x_2 - x_1)*(YT - y_1) / (y_2 - y_1);
		}
		if (code == code1)
		{
			x_1 = x; y_1 = y;  encode(x_1, y_1, code1);//������ ��Ķ˵㸲�ǵ�
		}
		else
		{
			x_2 = x; y_2 = y; encode(x_2, y_2, code2);//������ ��Ķ˵㸲�ǵ�
		}
	}
}
void mydisplay()  //��ʾ����
{
	//���Ʒ��α߽�
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);//���ñ�����ɫ
	glPointSize(2);//���õ�Ĵ�С
	glBegin(GL_LINE_LOOP);//��������Ĳ���
	glVertex2i(XL, YT);//���ƾ���
	glVertex2i(XL, YB);
	glVertex2i(XR, YB);
	glVertex2i(XR, YT);
	glEnd();
	glFlush();
	//����δ�ü�ǰ���߶�
	glBegin(GL_LINES);//����ֱ�ߵĲ���
	glVertex2i(x1_init, y1_init);
	glVertex2i(x2_init, y2_init);
	glEnd();
	glFlush();
	//���Ʋü�����߶�
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(x_1, y_1);
	glVertex2i(x_2, y_2);
	glEnd();
	glFlush();
}
int main(int argc, char *argv[])
{
    printf("��߽�XLΪ100\n�ұ߽�XRΪ300\n�±߽�YBΪ100\n�ϱ߽�YTΪ200\n");
    printf("�������߶���ʼλ��x0:\n");
    scanf("%d",&x_1);
    printf("�������߶���ʼλ��y0:\n");
    scanf("%d",&y_1);
    printf("�������߶���ֹλ��xEnd:\n");
    scanf("%d",&x_2);
    printf("�������߶���ֹλ��yEnd:\n");
    scanf("%d",&y_2);
    x1_init = x_1, y1_init = y_1, x2_init = x_2, y2_init = y_2;  //��ֱ�߶ζ˵㱸�ݣ��Ա㻭���ü�ǰ��ֱ�߶�

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 100);//����λ��
	glutInitWindowSize(500, 400);
	glutCreateWindow("Cohen-Sutherland�ü��㷨");
	glClearColor(1.0, 1.0, 1.0, 0.0);  //���ñ�����ɫ
	glMatrixMode(GL_PROJECTION);       // ����ͶӰ����
	gluOrtho2D(0.0, 600.0, 0.0, 400.0); // ���ó����Ĵ�С
	CS_LineClip();  //ִ��һ�βü��㷨
	glutDisplayFunc(&mydisplay);//���û��ƺ���
	glutMainLoop();
	return 0;
}
