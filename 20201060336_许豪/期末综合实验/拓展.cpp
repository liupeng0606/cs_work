// qimo2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<GL/glaux.h>

#include<gl/glut.h>
#include<stdio.h>
#include<math.h>
GLuint drawcube, drawsphere, drawteapot;

static GLfloat sx = 0, sy = 0, sz = 0;
static int lflag = GL_TRUE, rflag = GL_TRUE;
void reshape(int w, int h)

{

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(90, w / h, 0.5, 200);  //透视效果

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(-30, 30, 70, 0, 0, 0, 0, 10, 0);//设置观察点

}


void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //画出正方体显示列表
    drawcube = glGenLists(1);
    glNewList(drawcube, GL_COMPILE);
    glutSolidCube(1);
    glEndList();
    //画出球体显示列表
    drawsphere = glGenLists(1);
    glNewList(drawsphere, GL_COMPILE);
    glutSolidSphere(1, 20, 20);
    glEndList();
    //画出茶壶显示列表
    drawteapot = glGenLists(1);
    glNewList(drawteapot, GL_COMPILE);
    glutSolidTeapot(1);
    glEndList();


    //设置普通灯光照0位置及参数；
    GLfloat position0[] = { 30,5,30,1 };
    GLfloat light0s[] = { 0.10,0.10,0.10,0.0 };
    GLfloat light0d[] = { 0.6,0.7,0.7 };
    GLfloat light0a[] = { 0.9,0.9,0.9 };

    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0s);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0d);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0a);

    //设置探照灯光照1位置及参数
    GLfloat position1[] = { -60,40,0,1 };
    GLfloat light1s[] = { 1.0,1.0,1.0,1.0 };
    GLfloat light1d[] = { 0.06,0.1,0.1 };
    GLfloat light1a[] = { 0.91,0.99,0.96 };
    GLfloat  direction[] = { 0,-60,0,1 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1s);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1d);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1a);


    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);


}




void SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        sy -= 5.50f;
        glutPostRedisplay();
    }
    if (key == GLUT_KEY_DOWN)
    {
        sy += 5.50f;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_LEFT)
    {
        sx -= 0.50f;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_RIGHT)
    {
        sx += 0.50f;

        // sx= (GLfloat)((const int)sx % 360);
         // sy = (GLfloat)((const int)sy % 360);
        glutPostRedisplay();
    }
}




void draw()
{
    if (lflag)
        glEnable(GL_LIGHT0);
    if (rflag)
        glEnable(GL_LIGHT1);




    glPushMatrix();
    glTranslatef(sx, sy, sz);

    //绘制地面；
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.05, 0.2, 0.15, 0.0);
    glTranslatef(0, -20, 0);
    glScalef(150, 1, 150);
    glCallList(drawcube);
    glColor4f(0.0, 1.0, 0.0, 0.0);
    glutWireCube(1);

    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    //装饰地面
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.9, 0.6, 0.99, 0.0);

    glBegin(GL_LINES);

    float y = -19.5, z1 = 50;
    for (float x1 = -50; x1 < 50; ++x1)
    {
        glVertex3f(x1, y, z1);
        glVertex3f(x1, y, -z1);

    }
    float x2 = 50;
    for (float z2 = -50; z2 < 50; ++z2)
    {
        glVertex3f(x2, y, z2);
        glVertex3f(-x2, y, z2);

    }

    glEnd();
    glPopMatrix();

    //绘制四个桌腿：
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(1.0, 0.05, 0.0, 0.0);
    glTranslatef(20, -10, -20);
    glScalef(1, 20, 1);
    glCallList(drawcube);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(1.0, 0.05, 0.0, 0.0);
    glTranslatef(-20, -10, -20);
    glScalef(1, 20, 1);
    glCallList(drawcube);

    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(1.0, 0.05, 0.0, 0.0);
    glTranslatef(-20, -10, 20);
    glScalef(1, 20, 1);
    glCallList(drawcube);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(1.0, 0.05, 0.0, 0.0);
    glTranslatef(20, -10, 20);
    glScalef(1, 20, 1);
    glCallList(drawcube);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    //画出桌面：
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.1, 1.0, 0.1, 0.0);
    glScalef(50, 1, 50);
    glCallList(drawcube);
    glColor4f(0.39, 0.30, 0.1, 0.0);
    glutWireCube(1);
    // glFlush();
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    //绘制两边台阶；
    glPushMatrix();//左边第一级台阶
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.51, 0.40, 0.1, 0.0);
    glTranslatef(-30, -12, 0);
    glScalef(10, 4, 50);
    glCallList(drawcube);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.1, 0.50, 0.51, 0.0);
    glutWireCube(1);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    glPushMatrix();// 右边第一级台阶
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.51, 0.40, 0.1, 0.0);
    glTranslatef(40, -12, 0);
    glScalef(10, 4, 50);
    glCallList(drawcube);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.1, 0.50, 0.51, 0.0);
    glutWireCube(1);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();


    glPushMatrix();//左边第二级台阶
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.51, 0.40, 0.1, 0.0);
    glTranslatef(-32.5, -8, 0);
    glScalef(5, 4, 50);
    glCallList(drawcube);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.1, 0.50, 0.51, 0.0);
    glutWireCube(1);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    glPushMatrix();//右边第二级台阶
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.51, 0.40, 0.1, 0.0);
    glTranslatef(42.5, -8, 0);
    glScalef(5, 4, 50);
    glCallList(drawcube);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.1, 0.50, 0.51, 0.0);
    glutWireCube(1);

    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    //桌面上摆放物品，茶壶一只，鸡蛋一个
    glPushMatrix();//茶壶
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.51, 0.0, 0.1, 0.0);
    glTranslatef(0, 8, 0);
    glScalef(5, 10, 5);
    glCallList(drawteapot);

    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();


    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    glPushMatrix();//鸡蛋
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(1.00, 0.91, 0.05, 0.8);
    glTranslatef(-13, 6, 10);
    glScalef(2, 5, 2);
    glCallList(drawsphere);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();



    glPushMatrix();//地面上球体
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.30, 0.11, 0.15, 0.8);
    glTranslatef(15, -13, 25);
    glScalef(5, 5, 5);
    glCallList(drawsphere);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();


    glPushMatrix();//圆环一个
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.90, 0.01, 0.95, 0.8);
    glRotatef(1, 0, 0, 45);
    glTranslatef(-35, -13, 35);
    glutSolidTorus(1, 6, 20, 20);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();




    GLUquadricObj* pObj;
    glPushMatrix();//第一个杯子  左边
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    glTranslatef(-8, 6, 8);
    glRotatef(90, 1, 0, 0);
    gluCylinder(pObj, 1.50f, 1.0f, 5.0f, 26, 13);
    glPopMatrix();

    glPushMatrix();  //第2个杯子 右边
    glTranslatef(8, 6, 8);
    glRotatef(90, 1, 0, 0);
    gluCylinder(pObj, 1.50f, 1.0f, 5.0f, 26, 13);
    glPopMatrix();


    glPushMatrix();  //桌面上垫圈
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.21, 0.21, 0.21, 0.0);

    pObj = gluNewQuadric();
    //gluQuadricDrawStyle(pObj3,GLU_LINE);
    glTranslatef(-8, 1, 8);
    glRotatef(90, 1, 0, 0);
    gluDisk(pObj, 0.50f, 3.0f, 10, 10);
    glPopMatrix();

    glPushMatrix();  //桌面上垫圈

    pObj = gluNewQuadric();
    glTranslatef(8, 1, 8);
    glRotatef(90, 1, 0, 0);
    gluDisk(pObj, 0.50f, 3.0f, 30, 30);
    glPopMatrix();


    glPushMatrix(); //地面上放置 圆锥体；
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glColor4f(0.01, 0.01, 0.81, 0.0);

    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_LINE);
    glTranslatef(-15.0, 5.0, 15);
    glRotatef(90, 1, 0, 0);
    gluCylinder(pObj, 0.0f, 2.0f, 5.0f, 26, 13);
    glPopMatrix();


    glPopMatrix();

    glutSwapBuffers();


}


void  main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("综合实验");
    init();
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialKeys);
    // glutMouseFunc(mouse);
    glutDisplayFunc(draw);
    glutMainLoop();

}
