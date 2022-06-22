#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#define BITMAP_ID 0x4D42//读纹理函数
#pragma comment(lib,"glut32.lib")  
using namespace std;

GLfloat roate = 0.0;//旋转速率
GLfloat rote = 0.0;//旋转角度
GLfloat anglex = 0.0;//X轴旋转
GLfloat angley = 0.0;//Y轴旋转
GLfloat anglez = 0.0;//Z轴旋转
GLint WinW = 400;
GLint WinH = 400;
GLfloat oldx;//当左键按下时记录鼠标坐标  
GLfloat oldy;
GLuint Texture[1];
char TextureName[] = "teapot1.BMP";

// 读纹理函数
unsigned char* LoadBitmapFile(char* filename, BITMAPINFOHEADER* bitmapInfoHeader)
{
	FILE* filePtr;// 文件指针
	BITMAPFILEHEADER bitmapFileHeader;// bitmap文件头
	unsigned char* bitmapImage;// bitmap图像数据
	int	imageIdx = 0;// 图像位置索引
	unsigned char tempRGB;// 交换变量

	filePtr = fopen(filename, "rb");// 以“二进制+读”模式打开文件filename
	if (filePtr == NULL) return NULL;
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);// 读入bitmap文件图
	if (bitmapFileHeader.bfType != BITMAP_ID) {// 验证是否为bitmap文件
		fprintf(stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);// 读入bitmap信息头
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);// 将文件指针移至bitmap数据
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];// 为装载图像数据创建足够的内存
	if (!bitmapImage) {// 验证内存是否创建成功
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);// 读入bitmap图像数据
	if (bitmapImage == NULL) {// 确认读入成功
		fprintf(stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	for (imageIdx = 0; imageIdx < (bitmapInfoHeader->biSizeImage); imageIdx += 3) {//由于bitmap中保存的格式是BGR，于是交换R和B的值，得到RGB格式
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	fclose(filePtr);// 关闭bitmap图像文件
	return bitmapImage;
}

//加载纹理
void texload(int i, char* filename)
{
	BITMAPINFOHEADER bitmapInfoHeader;// bitmap信息头
	unsigned char* bitmapData;// 纹理数据

	bitmapData = LoadBitmapFile(filename, &bitmapInfoHeader);
	glBindTexture(GL_TEXTURE_2D, Texture[i]);

	// 指定当前纹理的放大/缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,bitmapInfoHeader.biWidth,bitmapInfoHeader.biHeight,0,GL_RGB,GL_UNSIGNED_BYTE,bitmapData);//该纹理有红、绿、蓝数据，无边框
}

//绘制茶壶
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

//定义纹理
void init(void) 
{
	cout << "点击鼠标左键并拖动实现茶壶拖动旋转，点击鼠标右键实现茶壶绕Y轴加速旋转。" << endl;
	glEnable(GL_DEPTH_TEST);//打开深度测试

	//定义光源
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };//光的位置
	GLfloat color_light[] = { 1.0,1.0,1.0,1.0 };//光的颜色
	GLfloat Light_Model_Ambient[] = { 1,1,1,1 };//环境光

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, color_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//定义纹理
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, Texture);

	texload(0, TextureName);
	glBindTexture(GL_TEXTURE_2D, Texture[0]);

	//设置像素存储模式控制所读取的图像数据的行对齐方式
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glDisable(GL_TEXTURE_2D);

}

//显示
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture[0]); //选择纹理图案
	glCallList(GenTeapotList());
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity(); //加载单位矩阵  
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

//重塑
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

//鼠标响应
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
			roate = 0;
			rote = 0;
			oldx = x;//当左键按下时记录鼠标坐标  
			oldy = y;
		}
	}
	if (button == GLUT_RIGHT_BUTTON){
		if (state == GLUT_DOWN){
			roate += 1.0f;
		}
	}
}

//重绘图像
void motion(int x, int y)
{
	GLint deltax = oldx - x;
	GLint deltay = oldy - y;
	anglex += 360 * (GLfloat)deltax / (GLfloat)WinW; 
	angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
	anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;//根据屏幕上鼠标滑动的距离来设置旋转的角度 
	oldx = x;
	oldy = y;//更新鼠标坐标，使滑动旋转可控
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);							
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//设置显示模式
	glutInitWindowPosition(0, 0);//设置窗口在屏幕上的位置
	glutInitWindowSize(600, 600);//设置窗口的大小
	glutCreateWindow("茶壶渲染+旋转");	
	init();						
	glutDisplayFunc(display);//调用绘图函数
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(display);

	glutMainLoop();	//进入循环
	return 0;
}

