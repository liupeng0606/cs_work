#include <windows.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <process.h>
static int year = 0, day = 0;
static int longitude = 200, latitude = 200;
static GLuint texture[3] = {0, 0, 0};
static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat yequalzero[] = {0.0, 1.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
GLubyte *readImg(char *filename, int *imagewidth, int *imageheight)
{
    int pixellength;
    GLubyte *pixeldata;
    FILE *pfile = fopen(filename, "rb"); //打开文件
    if (pfile == 0)
        exit(0);
    //读取图像大小
    fseek(pfile, 0x0012, SEEK_SET);
    fread(imagewidth, sizeof(*imagewidth), 1, pfile);
    fread(imageheight, sizeof(*imageheight), 1, pfile);
    //计算像素数据长度
    pixellength = (*imagewidth) * 3;
    while (pixellength % 4 != 0)
        pixellength++;
    pixellength *= (*imageheight);
    //读取像素数据
    pixeldata = (GLubyte *)malloc(pixellength);
    if (pixeldata == 0)
        exit(0);
    fseek(pfile, 54, SEEK_SET);
    fread(pixeldata, pixellength, 1, pfile);
    fclose(pfile); //关闭文件
    return pixeldata;
}

void LoadTexture(char *filename, GLuint &texture)
{
    GLubyte *data;
    GLint width, height;
    FILE *file;
    //读文件
    data = readImg(filename, &width, &height);
    glGenTextures(1, &texture);                                  //生成纹理的数量并存储存储纹理索引
    glBindTexture(GL_TEXTURE_2D, texture);                       //绑定纹理
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //指定纹理贴图与材质的混合模式
    //线性滤图
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //自动生成纹理坐标，使用球面映射
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);                                                   //指定OpenGL如何从数据缓存区中解包图像数据
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); //根据指定的参数，生成一个2D纹理
    glEnable(GL_TEXTURE_2D);                                                                 //打开纹理映射
    free(data);                                                                              //释放纹理图像数据
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);                            //设置好清除颜色
    glShadeModel(GL_SMOOTH);                                     //对多边形内部所有点的颜色通过对多边形顶点颜色插值产生
    glEnable(GL_DEPTH_TEST);                                     //开启深度测试
    glDepthFunc(GL_LESS);                                        //目标像素与当前像素在z方向上值大小比较
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);                   //设置两面均为填充
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};                //漫放射系数，对应RGBA四个分量
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};               //镜面放射系数,对应RGBA四个分量
    GLfloat mat_shininess[] = {5.0};                             //材料反射指数
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse); //设置环境光系数和漫反射光系数
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);           //设置镜面光反射
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);         //设置材料反射指数
    glEnable(GL_LIGHTING);                                       // 开启光照计算
    glEnable(GL_LIGHT0);                                         //开启0号光源，OpenGL中有8种光源
    LoadTexture("D:\\develop\\earth.bmp", texture[0]);           //创建并绑定纹理对象
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};     //光源位置
    GLfloat light_ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};  // 环境强度
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  // 散射强度
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // 镜面强度
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);   //光源位置
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);     //光源强度,不写这三句将使用默认值，
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glColor3f(1.0, 1.0, 1.0);   //启用光源后，不再使用颜色函数对物体着色
    glMatrixMode(GL_MODELVIEW); //使用模型视图矩阵栈保存后面的几何变换

    //用二次曲面画球体
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    glPushMatrix();
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);            //看地球的侧面
    glBindTexture(GL_TEXTURE_2D, texture[0]); //绑定纹理
    gluQuadricTexture(qobj, GL_TRUE);         //纹理函数
    gluSphere(qobj, 1.5, 60, 60);             //二次曲面qobj
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);                 //使视区大小保持与窗口的显示区域大小一致
    glMatrixMode(GL_MODELVIEW);                               //使用模型视图矩阵栈
    glLoadIdentity();                                         //重置当前指定的矩阵为单位矩阵
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //设定观察视点和观察方向
    glMatrixMode(GL_PROJECTION);                              //使用投影矩阵栈，准备设定投影矩阵
    glLoadIdentity();                                         //初始化投影矩阵为单位矩阵
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.5, 30.0); //定义视景体,根据四个参数计算用以投影变换的透视投影矩阵
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'Z':
        day = (day + 10) % 360; //增加自转的角度，逆时针旋转
        glutPostRedisplay();    // 标记当前窗口并重新绘制出地球逆时针自转后的图
        break;
    case 'R':
        day = (day - 10) % 360; //减少自转的角度，顺时针旋转
        glutPostRedisplay();    // 标记当前窗口并重新绘制出地球逆时针自转后的图
        break;

    case 'L':
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //使用线框模型显示物体
        glDisable(GL_LIGHTING);                    //关闭光照计算
        glDisable(GL_TEXTURE_2D);                  //关闭纹理映射
        longitude = 20;
        latitude = 16;
        glutPostRedisplay(); //标记当前窗口并重新绘制出地球的线框图
        break;
    case 'F':
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //使用多边形填充模型型显示物体
        glEnable(GL_LIGHTING);                     //开启光照计算
        glEnable(GL_TEXTURE_2D);                   //打开纹理映射
        glEnable(GL_TEXTURE_GEN_S);                //打开纹理坐标自动映射，纹理图像中的S相当于x坐标
        glEnable(GL_TEXTURE_GEN_T);                //打开纹理坐标自动映射，纹理图像中的T相当于y坐标
        longitude = 200;
        latitude = 200;
        glutPostRedisplay(); // 标记当前窗口并重新绘制出填充后显示的图
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       //初始化OpenGL
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //设置显示参数(双缓存，RGB格式)
    glutInitWindowSize(500, 500);                //设置窗口尺寸
    glutInitWindowPosition(100, 100);            //设置窗口显示位置，在屏幕左上角像素值(100,100)处
    glutCreateWindow("地球");                    //设置窗口名称
    init();                                      //程序初始化
    glutDisplayFunc(display);                    //显示函数，参数display为上文中的函数
    glutReshapeFunc(reshape);                    //当窗口尺寸改变时，图形比例不发生变化
    glutKeyboardFunc(keyboard);                  //键盘交互事件函数
    glutMainLoop();                              //多次调用glut函数
    return 0;
}
