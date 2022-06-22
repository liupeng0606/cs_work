#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#define BITMAP_ID 0x4D42//��������
#pragma comment(lib,"glut32.lib")  
using namespace std;

GLfloat roate = 0.0;//��ת����
GLfloat rote = 0.0;//��ת�Ƕ�
GLfloat anglex = 0.0;//X����ת
GLfloat angley = 0.0;//Y����ת
GLfloat anglez = 0.0;//Z����ת
GLint WinW = 400;
GLint WinH = 400;
GLfloat oldx;//���������ʱ��¼�������  
GLfloat oldy;
GLuint Texture[1];
char TextureName[] = "teapot1.BMP";

// ��������
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
{
	FILE* filePtr;// �ļ�ָ��
	BITMAPFILEHEADER bitmapFileHeader;// bitmap�ļ�ͷ
	unsigned char* bitmapImage;// bitmapͼ������
	int	imageIdx = 0;// ͼ��λ������
	unsigned char tempRGB;// ��������

	filePtr = fopen(filename, "rb");// �ԡ�������+����ģʽ���ļ�filename
	if (filePtr == NULL) return NULL;
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);// ����bitmap�ļ�ͼ
	if (bitmapFileHeader.bfType != BITMAP_ID) {// ��֤�Ƿ�Ϊbitmap�ļ�
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);// ����bitmap��Ϣͷ
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);// ���ļ�ָ������bitmap����
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];// Ϊװ��ͼ�����ݴ����㹻���ڴ�
	if (!bitmapImage) {// ��֤�ڴ��Ƿ񴴽��ɹ�
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);// ����bitmapͼ������
	if (bitmapImage == NULL) {// ȷ�϶���ɹ�
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	for (imageIdx = 0; imageIdx < (bitmapInfoHeader->biSizeImage); imageIdx += 3) {//����bitmap�б���ĸ�ʽ��BGR�����ǽ���R��B��ֵ���õ�RGB��ʽ
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	fclose(filePtr);// �ر�bitmapͼ���ļ�
	return bitmapImage;
}

//��������
void texload(int i, char* filename)
{
	BITMAPINFOHEADER bitmapInfoHeader;// bitmap��Ϣͷ
	unsigned char* bitmapData;// ��������

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, Texture[i]);

	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight,0,GL_RGB,GL_UNSIGNED_BYTE,bitmapData);//�������к졢�̡������ݣ��ޱ߿�
}

//���Ʋ��
GLint GenTeapotList()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);

	GLfloat mat_diffuse[] = { 0.55, 0.55, 0.55, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 90.0 };


	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_SMOOTH);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEndList();
	return lid;
}

//��������
void init(void) 
{
	cout << "������������϶�ʵ�ֲ���϶���ת���������Ҽ�ʵ�ֲ����Y�������ת��" << endl;
	glEnable(GL_DEPTH_TEST);//����Ȳ���

	//�����Դ
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//���λ��
	GLfloat color_light[] = { 1.0,1.0,1.0,1.0 };//�����ɫ
	GLfloat Light_Model_Ambient[] = { 1,1,1,1 };//������

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, color_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//��������
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, Texture);

	texload(0, TextureName);
	glBindTexture(GL_TEXTURE_2D, Texture[0]);

	//�������ش洢ģʽ��������ȡ��ͼ�����ݵ��ж��뷽ʽ
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glDisable(GL_TEXTURE_2D);

}

//��ʾ
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture[0]); //ѡ������ͼ��
	glCallList(GenTeapotList());
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity(); //���ص�λ����  
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(rote, 0.0f, 1.0f, 0.0f);
	glRotatef(anglex, 1.0, 0.0, 0.0);
	glRotatef(angley, 0.0, 1.0, 0.0);
	glRotatef(anglez, 0.0, 0.0, 1.0);
	glutSolidTeapot(1.2);
	rote += roate;
	glutSwapBuffers();

	glFlush();
}

//����
void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//�����Ӧ
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
			roate = 0;
			rote = 0;
			oldx = x;//���������ʱ��¼�������  
			oldy = y;
		}
	}
	if (button == GLUT_RIGHT_BUTTON){
		if (state == GLUT_DOWN){
			roate += 1.0f;
		}
	}
}

//�ػ�ͼ��
void motion(int x, int y)
{
	GLint deltax = oldx - x;
	GLint deltay = oldy - y;
	anglex += 360 * (GLfloat)deltax / (GLfloat)WinW; 
	angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
	anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;//������Ļ����껬���ľ�����������ת�ĽǶ� 
	oldx = x;
	oldy = y;//����������꣬ʹ������ת�ɿ�
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);							
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//������ʾģʽ
	glutInitWindowPosition(0, 0);//���ô�������Ļ�ϵ�λ��
	glutInitWindowSize(600, 600);//���ô��ڵĴ�С
	glutCreateWindow("�����Ⱦ+��ת");	
	init();						
	glutDisplayFunc(display);//���û�ͼ����
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(display);

	glutMainLoop();	//����ѭ��
	return 0;
}

