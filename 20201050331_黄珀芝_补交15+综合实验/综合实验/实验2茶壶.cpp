#include <windows.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include <mmsystem.h>
#include <math.h>
//����������
#define BITMAP_ID 0x4D42
#define TEX_NUM 4

GLuint filter;         // �˲�����
GLuint Texture[TEX_NUM];
char *TextureName[] = {
	"teapot1.BMP",
	"teapot2.BMP",
	"teapot3.BMP",
	"teapot4.BMP",
};
// ��������
// �����ʾ�����飬������������ı�ʾ��
// ����: ͨ��ָ�룬����filename ָ����bitmap�ļ������ݡ�
// ͬʱҲ����bitmap��Ϣͷ.����֧��-bitλͼ��
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;						// �ļ�ָ��
	BITMAPFILEHEADER bitmapFileHeader;	// bitmap�ļ�ͷ
	unsigned char	*bitmapImage;		// bitmapͼ������
	int	imageIdx = 0;					// ͼ��λ������
	unsigned char tempRGB;				// ��������
	// �ԡ�������+����ģʽ���ļ�filename
	filePtr = fopen(filename,"rb");
	if (filePtr == NULL) return NULL;
	// ����bitmap�ļ�ͼ
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// ��֤�Ƿ�Ϊbitmap�ļ�
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	// ����bitmap��Ϣͷ
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// ���ļ�ָ������bitmap����
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// Ϊװ��ͼ�����ݴ����㹻���ڴ�
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// ��֤�ڴ��Ƿ񴴽��ɹ�
	if (!bitmapImage) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	// ����bitmapͼ������
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// ȷ�϶���ɹ�
	if (bitmapImage == NULL) {
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	//����bitmap�б���ĸ�ʽ��BGR�����潻��R��B��ֵ���õ�RGB��ʽ
	for (imageIdx = 0; imageIdx < (bitmapInfoHeader->biSizeImage); imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// �ر�bitmapͼ���ļ�
	fclose(filePtr);
	return bitmapImage;
}
//��������ĺ�����
void texload(int i, char *filename)
{
	BITMAPINFOHEADER bitmapInfoHeader;			// bitmap��Ϣͷ
	unsigned char*   bitmapData;				// ��������
	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, Texture[i]);
	// ָ����ǰ����ķŴ�/��С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0,		//mipmap���(ͨ��Ϊ����ʾ���ϲ�)
		GL_RGB,	//����ϣ���������к졢�̡�������
		bitmapInfoHeader.biWidth,	//��������������n�����б߿�+2
		bitmapInfoHeader.biHeight,	//����߶ȣ�������n�����б߿�+2
		0,		//�߿�(0=�ޱ߿�, 1=�б߿�)
		GL_RGB,	//bitmap���ݵĸ�ʽ
		GL_UNSIGNED_BYTE,	//ÿ����ɫ���ݵ�����
		bitmapData);		//bitmap����ָ��
}
//���Ʋ��
GLint GenTeapotList()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.55, 0.55, 0.55, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 90.0 };
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidTeapot(0.5);
	glEndList();
	return lid;
}
//��������ĺ�����
void init(void) //
{
	glEnable(GL_DEPTH_TEST);//����Ȳ���
	//�����Դ
	GLfloat position1[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//��������
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(TEX_NUM, Texture);
	for (int i = 0; i < TEX_NUM; i++) {
		texload(i, TextureName[i]);
		glBindTexture(GL_TEXTURE_2D, Texture[i]);
		//�������ش洢ģʽ��������ȡ��ͼ�����ݵ��ж��뷽ʽ.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glDisable(GL_TEXTURE_2D);
}
void display(void)
{glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture[0]); //ѡ������ͼ��
	glCallList(GenTeapotList());
	glFlush();
}
void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);										//��ʼ�����߰�
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);	//������ʾģʽ
	glutInitWindowPosition(0, 0);								//���ô�������Ļ�ϵ�λ��
	glutInitWindowSize(500, 500);							//���ô��ڵĴ�С
	glutCreateWindow("wenli");						//����Ļ����
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);	//���û�ͼ����
	init();						//��Ҫ��������ʼ������
	glutMainLoop();				//����ѭ��
	return 0;
}