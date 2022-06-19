#include<GL/glut.h>
#include <cstdlib> 
#include <cstdio> 
#include <cmath> 
#define stripeImageWidth 28
#define stripeImageHeight 28

GLubyte stripeImage[stripeImageWidth][stripeImageHeight][4];
// 初始化材质属性、光源、照明模型和深度缓冲区

GLfloat rx, ry, rz = 0.0;		// 物体 旋转
GLdouble size=0.5;

void SetImage(void){    //设置纹理
    int i, j;
    for (i = 0; i < stripeImageWidth; i++){
        for (j = 0; j < stripeImageHeight; j++){
            stripeImage[i][j][0] = (GLubyte)(i * 8-1);
            stripeImage[i][j][1] = (GLubyte)(j * 13- 1);
            stripeImage[i][j][2] = (GLubyte)222;
            stripeImage[i][j][3] = (GLubyte)112;
        }
    }
}

static GLfloat xequalzero[] = { 0.3,0.8,0.9, 1.0 };
static GLfloat* currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
static float roangles;

void init(void){
    GLfloat mat_ambient[] = { 0.6, 0.2, 0.7, 1.0 };    //环境光照分量
    GLfloat mat_specular[] = { 0.6, 0.2, 0.7, 1.0 };   //镜面反射参数
    GLfloat mat_diffuse[] = { 0.8, 0.1, 0.5, 1.0 };    //漫反射光照分量
    GLfloat mat_shininess[] = { 85.0 };                //高光指数

    GLfloat light_position[] = { 1.0, 1.0, 1.0,0.0 };   //光源位置
    GLfloat light_specular[] = { 0.9, 0.1, 0.5,1.0 };   //折射光参数
    GLfloat light_diffuse[] = { 0.6, 0.5, 0.4, 1.0 };   //满射光参数
    GLfloat light_ambient[] = { 0.6, 0.5, 0.4, 1.0 };   //环境光参数

    glClearColor(0.2, 0.5, 0.9, 1.0);
    glEnable(GL_DEPTH_TEST);    //消除隐藏曲面
    glShadeModel(GL_SMOOTH);
    SetImage();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   //提取像素方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       //设置环绕模式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //缩小过滤器，线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //放大过滤器，线性过滤
    glTexImage2D(GL_TEXTURE_2D, 0, 4, stripeImageWidth, stripeImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);//载入纹理
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);        //指定环境模式为：纹理单位颜色与几何图形颜色相乘。


    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
    glTexGenfv(GL_S, currentPlane, currentCoeff);  //自动生成纹理坐标
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_2D);   //启用纹理
    glEnable(GL_LIGHTING);     //激活OpenGL光源
    glEnable(GL_LIGHT0);       //启用此光照
    glEnable(GL_AUTO_NORMAL);  //以分析方式计算图面法向量
    glEnable(GL_NORMALIZE);    //使用 glNormal 指定的正常向量在转换后缩放为单位长度。
    
    roangles = 50.0f;

    //光照
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);       //设置材料漫反射指数
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);      //设置材料环境光照指数    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    //设置材料反射指数（纯镜面反射）
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  //设置材料反射指数（材料反射指数）

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);   //建立光源 （光源位置）
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);       //建立光源 （漫反射光分量强度）
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);      //建立光源 （折射光分量强度）
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_ambient);    //建立光照模式
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glutSolidSphere (1.0, 20, 16);
    glPushMatrix();
    glRotatef(roangles, 0.0, 1.0, 0.0);
	glutSolidTeapot(size);
    glPopMatrix();
    glRotatef(rx, 1.0f, 0.0f, 0.0f);                      // 绕X轴旋转
    glRotatef(ry, 0.0f, 1.0f, 0.0f);                      // 绕Y轴旋转
    glRotatef(rz, 0.0f, 0.0f, 1.0f);                      // 绕Z轴旋转
	glFlush();
}

void myKey(unsigned char key, int x, int y) { //键盘
    switch (key){
        case 'a':case 'A': 
            roangles += 5.0; 
            glutPostRedisplay();   //重新调用绘制函数
            break;
        case 's':case 'S': 
            roangles -= 5.0; 
            glutPostRedisplay(); 
            break;
            //控制大小
        case 'w':case'W':
            size += -0.1; 
            glutPostRedisplay(); 
            break;
        case 'd':case'D':
            size +=  0.1; 
            glutPostRedisplay(); 
            break;
        case 27:exit(0); break;
    }

    if (roangles> 360) roangles-= 360;
    if (roangles< 0) roangles+= 360;
}

void mySpecialKey(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        rx += 1;
        glutPostRedisplay();   //重新调用绘制函数
        break;
    case GLUT_KEY_RIGHT:
        rx -= 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        rz += 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        rz -= 1;
        glutPostRedisplay();
        break;
    case 27:exit(0); break;
    }
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);   // 指定当前操作矩阵为投影矩阵。
	glLoadIdentity();              //重置坐标系统
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
			1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,
			1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);  //指定当前操作矩阵为模型视图矩阵。
	glLoadIdentity();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
    glutCreateWindow("茶壶渲染");

	init();
	glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    glutSpecialFunc(mySpecialKey);

	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}