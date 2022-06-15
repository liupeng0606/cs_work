#include <windows.h>
#include<GL/glut.h>
#define imageWidth 50
GLfloat roate = 0.0;// 设置旋转速率
GLfloat rote = 0.0;//旋转角度
GLfloat anglex = 0.0;//X 轴旋转
GLfloat angley = 0.0;//Y 轴旋转
GLfloat anglez = 0.0;//Z 轴旋转
GLint WinW = 400;
GLint WinH = 400;
GLfloat oldx;//当左键按下时记录鼠标坐标
GLfloat oldy;
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat windowWidth;
GLfloat windowHeight;
float xrot;
GLubyte stripeImage[3 * imageWidth];
//定义纹理图像
void makeStripeImage(void)
{
        int j;
        for(j = 0; j < imageWidth; j++)
        {
                stripeImage[3 * j] = 300;
                stripeImage[3 * j + 1] = 165 / 3 * j;
                stripeImage[3 * j + 2] = 140;
        }
}
/* 参数设置 */
GLfloat sgenparams[] = {1.0, 1.0, 1.0, 0.0};

void  Scene(void)
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);//开启深度测试
        glDepthFunc(GL_LESS);//深度测试函数
        glColor3f(1.0, 0.0, 0.0);
        glLoadIdentity();//加载矩阵
        glPushMatrix();//矩阵入栈
        glRotatef(rote, 0.0f, 1.0f, 0.0f);
        glRotatef(anglex,1.0,0.0,0.0);
        glRotatef(angley,0.0,1.0,0.0);
        glRotatef(anglez,0.0,0.0,1.0);
        rote += roate;
        glutSolidTeapot(50);//绘制茶壶
        glPopMatrix();//矩阵出栈
        glutPostRedisplay();
        glutSwapBuffers();
}

void RC(void)
{
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };//材质的镜面反射系数
        GLfloat mat_shininess[] = { 50.0 };//材质的镜面光指数
        // 光源 0
        GLfloat light_position[] = { -50.0, 100.0, 100.0, 0.0};//光源位置
        GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};//环境光
        GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//漫反射
        GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };//镜面光

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glShadeModel(GL_SMOOTH);//光暗处理
        makeStripeImage();//绘制纹理
        //函数设定从内存中读取纹理图并放到屏幕上的方式
        //指定内存中每个象素行起始的排列要求为字节排列（1）
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        //定义纹理环境参数：调整当前亮度和颜色信息，使之适应纹理图像
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        //纹理绕转使用重复方式
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //定义纹理放大和缩小函数均为GL_LINEAR
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //定义纹理
        glTexImage1D(GL_TEXTURE_1D, 0, 3, imageWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, stripeImage);
        //控制纹理坐标的生成
        //指定单值纹理生成参数
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
        //指定纹理坐标生成函数,系数由sgenparams指定
        glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);

        glEnable(GL_TEXTURE_GEN_S);//开启纹理坐标映射
        glEnable(GL_TEXTURE_1D);//开启纹理

        glEnable(GL_LIGHT0);//开启0光源
        //设置材质
        glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glEnable(GL_LIGHTING);//开启光照效果
        //设置光照材质与位置
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

}

void  ChangeSize(GLsizei w, GLsizei h)
{
        glViewport(0, 0, (GLsizei) w, (GLsizei) h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if(w <= h)
                glOrtho(-100.0, 100, -100.0 * (GLfloat)h / (GLfloat)w, 100.0 * (GLfloat)h / (GLfloat)w, -1000.0, 1000.0);
        else
                glOrtho(-100.0 * (GLfloat)w / (GLfloat)h, 100.0 * (GLfloat)w / (GLfloat)h, -100.0, 100.0, -1000.0, 1000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}
void mouse(int button, int state, int x, int y) // 鼠标函数
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            if (state == GLUT_DOWN)
            {
                roate = 0;
                rote = 0;
                oldx = x;//当左键按下时记录鼠标坐标
                oldy = y;
            }
        }
        if (button == GLUT_RIGHT_BUTTON)
        {
            if (state == GLUT_DOWN)
            {
                roate += 1.0f;
            }
        }
    }

 void motion(int x, int y)
    {
        GLint deltax = oldx - x;
        GLint deltay = oldy - y;
        anglex  += 360 * (GLfloat)deltax / (GLfloat)WinW;//根据屏幕上鼠标滑动的距离来设置旋转的角度
        angley += 360 * (GLfloat)deltay / (GLfloat)WinH;
        anglez += 360 * (GLfloat)deltay / (GLfloat)WinH;
        oldx = x;//记录此时的鼠标坐标，更新鼠标坐标
        oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控
        glutPostRedisplay();
    }

int main(int argc,char** argv)
{
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(640, 480);
        glutInitWindowPosition(100, 150);
        glutInit(&argc,argv);
        glutCreateWindow("茶壶");
        glutDisplayFunc(Scene);
        glutReshapeFunc(ChangeSize);
        glutMouseFunc(mouse);
        glutMotionFunc(motion);
        RC();
        glutMainLoop();
        return 0;
}
