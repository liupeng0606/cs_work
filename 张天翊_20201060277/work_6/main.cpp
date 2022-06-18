#include<windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<math.h>
#define pi 3.14159
GLfloat square[4][2];

//平移
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
//比例/缩放
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
//旋转
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
//对称
void Symmetry(int flag)
{
	for(int i=0;i<4;i++){
		if(flag){//等于1关于x轴对称
			square[i][1]*=-1;
		}else{//等于0关于y轴对称
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

void myinit()//初始化正方形顶点数组
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
	glViewport(0,0,w,h);//设置视口大小比例始终与窗口一致

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400,400,-400,400);
}

void display()
{
	//设置背景颜色为白色并清除颜色缓冲
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//画正方形
	glColor4f(0.0,0.0,0.0,0.1);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(square[0][0],square[0][1]);
		glVertex2f(square[1][0],square[1][1]);
		glVertex2f(square[2][0],square[2][1]);
		glVertex2f(square[3][0],square[3][1]);
	glEnd();

    Scale(1.5,1.5);//比例

	Translate(100, 100);//平移
    Rotate(pi/3);//旋转
    Symmetry(1);//对称

	glutSwapBuffers();//交换前后缓冲区
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);//初始化OPENGL显示方式
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (600, 600); //设定OPENGL窗口位置和大小
	glutCreateWindow ("二维几何变换");//打开窗口
    myinit();//调用初始化函数

	glutReshapeFunc(reshape);//设定窗口大小变化的回调函数

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
