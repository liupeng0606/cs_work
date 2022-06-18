#include <windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#define stripeImageWidth 32
#define stripeImageHeight 32
GLubyte stripeImage[stripeImageWidth][stripeImageHeight][4];
void makeStripeImage(void)
{
    int i, j;
    for (i = 0; i < stripeImageWidth; i++)
    {
        for (j = 0; j < stripeImageHeight; j++)
        {
            stripeImage[i][j][0] = (GLubyte)0;
            stripeImage[i][j][1] = (GLubyte)(j * 6 - 1);
            stripeImage[i][j][2] = (GLubyte)200;
            stripeImage[i][j][3] = (GLubyte)(i * 4 - 1);
        }
    }
}
static GLfloat xequalzero[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat slanted[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
static float roangles;
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    makeStripeImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, stripeImageWidth, stripeImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
    glTexGenfv(GL_S, currentPlane, currentCoeff);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0);
    roangles = 90.0f;
    //光照
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 90.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };    //光源位置
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat Light_Model_Ambient[] = { 0.6, 0.6, 0.6, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);    //设置材料反射指数（纯镜面反射）
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  //设置材料反射指数（材料反射指数）
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);   //建立光源 （光源位置）
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);       //建立光源 （漫反射光分量强度）
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);      //建立光源 （折射光分量强度）
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);
}
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(roangles, 0.0, 1.0, 0.0);
    glutSolidTeapot(2.0);
    glPopMatrix();
    glFlush();
}
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-3.5, 3.5, -3.5*(GLfloat)h / (GLfloat)w, 3.5*(GLfloat)h / (GLfloat)w, -3.5, 3.5);
    else
        glOrtho(-3.5*(GLfloat)w / (GLfloat)h, 3.5*(GLfloat)w / (GLfloat)h, -3.5, 3.5, -3.5, 3.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void idle()
{
    roangles += 0.05f;
    glutPostRedisplay();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(250, 250);
    glutCreateWindow("计算机图形学期末综合————三维图形渲染");
    glutIdleFunc(idle);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
