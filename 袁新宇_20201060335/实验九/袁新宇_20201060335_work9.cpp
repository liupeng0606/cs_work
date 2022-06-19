#include<GL/glut.h>
#include<math.h>
#include<Windows.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
GLsizei winWidth = 600, winHeight = 600;
GLuint regHex;//显示表标识
/*设置世界坐标范围*/
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;
class wcPt3d{
public:
	GLfloat x, y, z;

};

typedef GLfloat Matrix4x4[4][4];
Matrix4x4 matComposite;//3D变换复合矩阵
const GLdouble pi = 3.14159;

static void init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);//设置为白色背景
}

void Matrix4x4SetIdentity(Matrix4x4 matIdent4x4){
	//生成一个单位矩阵
	GLint row, col;
	for (row = 0; row < 4; ++row)
		for (col = 0; col < 4; ++col){
			matIdent4x4[row][col] = (row == col);
		}
}
void matrix4x4Premultiply(Matrix4x4 m1, Matrix4x4 m2){
	//矩阵的乘法，结果储存在M2中
	GLint row, col;
	Matrix4x4 matTemp;
	for (row = 0; row < 4; ++row)
		for (col = 0; col < 4; col++){
			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col] + m1[row][3] * m2[3][col];
		}
	for (row = 0; row < 4; ++row)
		for (col = 0; col < 4; col++){
			m2[row][col] = matTemp[row][col];
		}
}

void translate3D(GLfloat tx, GLfloat ty, GLfloat tz){
	/*通过偏移量tx,ty产生平移矩阵matTransl之后，再通过矩阵的乘法，实现对象的平移*/
	Matrix4x4 matTransl;//平移矩阵
	Matrix4x4SetIdentity(matTransl);
	matTransl[0][3] = tx;
	matTransl[1][3] = ty;
	matTransl[2][3] = ty;
	/*矩阵乘法，平移*/
	matrix4x4Premultiply(matTransl, matComposite);
}
void rotate3d(wcPt3d p1, wcPt3d p2, GLfloat theta){
	Matrix4x4 matRot;//旋转矩阵
	GLfloat axisVecLength = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.x - p1.x) + (p2.z - p1.z) * (p2.z - p1.z));
	GLfloat cosTheta = cos(theta);
	GLfloat oneC = 1 - cosTheta;
	GLfloat sinTheta = sin(theta);
	GLfloat ux = (p2.x - p1.x) / axisVecLength;
	GLfloat uy = (p2.y - p1.y) / axisVecLength;
	GLfloat uz = (p2.z - p1.z) / axisVecLength;

	/*将旋转向量平移到原点*/
	translate3D(-p1.x, -p1.y, -p1.z);
	Matrix4x4SetIdentity(matRot);
	matRot[0][0] = ux * ux * oneC + cosTheta;
	matRot[0][1] = ux * uy * oneC - uz * sinTheta;
	matRot[0][2] = ux * uz * oneC + uy * sinTheta;
	matRot[1][0] = uy * uz * oneC + uz * sinTheta;
	matRot[1][1] = uy * uy * oneC + cosTheta;
	matRot[1][2] = uy * uz * oneC + uy * sinTheta;
	matRot[2][0] = uz * ux * oneC - uy * sinTheta;
	matRot[2][1] = uz * uy * oneC + ux * sinTheta;
	matRot[2][2] = uz * uz * oneC + cosTheta;
	matrix4x4Premultiply(matRot, matComposite);
	translate3D(p1.x, p1.y, p1.z);//平移回原来的位置
}

void translate3d(GLint nverts, wcPt3d* verts){
	//对象顶点与复合变换矩阵的乘法，得到坐标变换后的点
	GLint k;
	GLfloat temp;
	for (k = 0; k < nverts; ++k){
		temp = verts[k].x * matComposite[0][0] + verts[k].y * matComposite[0][1] + matComposite[0][2];
		verts[k].y = verts[k].x * matComposite[1][0] + verts[k].y * matComposite[1][1] + matComposite[1][2];
		verts[k].x = temp;
	}
}
void triangle(wcPt3d* verts){
	//输出一个空间三角形
	GLint k;
	glBegin(GL_TRIANGLES);
	cout << "当前顶点坐标为：";
	for (k = 0; k < 3; ++k){
		glVertex3f(verts[k].x, verts[k].y, verts[k].z);
		cout << verts[k].x << "," << verts[k].y << "," << verts[k].z << endl;
	}
	glEnd();
}

void displayFcn(){
	GLint nverts = 3;
	wcPt3d verts[3] = { { 100.0, 50.0,0 }, { 150.0, 25.0 ,50}, { 100.0, 100.0,100 } };//定义一个三角形
	GLdouble theta = pi / 4.0;//旋转45°
	wcPt3d p1, p2;
	p1.x = 0; p1.y = 0; p1.z = 0;
	p2.x = 0; p2.y = 0; p2.z = 1;//定义旋转轴为(0,0,1)
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.0, 1.0);
	triangle(verts);//蓝色三角形为原始三角形
	Matrix4x4SetIdentity(matComposite);
	glColor3f(1.0, 0.2, 0.5);//红色为移动后的三角形
	rotate3d(p1, p2, theta);//旋转
	translate3d(nverts, verts);
	glColor3f(1.0, 0.0, 1.0);//红色为移动后的三角形
	triangle(verts);
	glFlush();
}

void winReshapeFcn(int newWidth, int newHeight){
	//窗口重定形函数
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
	glOrtho(xwcMin, xwcMax, ywcMin, ywcMax, -55, 0);
	glClear(GL_COLOR_BUFFER_BIT);
} 

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("三维几何变换");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}