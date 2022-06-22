// yansebianmajianmo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<Windows.h>
#include <iostream>
#include<GL/glut.h>
//GLsiei intialsiseot the dsplay windows
GLsizei winWidth=500,winHeight=500;
/*Set 1imits for the rectangular area in complex plane.*/
GLfloat xComplexMin = -2.00, xComplexMax = 0.50;
GLfloat yComplexMin = -1.25, yComplexMax = 1.25;
GLfloat complexWidth =xComplexMax -xComplexMin;
GLfloat complexHeight = yComplexMax - yComplexMin;
class complexNum{
    public:
          GLfloat x,y;
};
struct color { GLfloat r, g, b; };
void init(void){
    /*Set display -window colorto white.8*/
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
void plotPoint(complexNum z) {
   glBegin(GL_POINTS);
   glVertex2f(z.x,z.y);
   glEnd();
}
/*Calculate the square ofa complex number. */
complexNum complexSquare(complexNum z){
   complexNum zSquare;
   zSquare.x=z.x*z.x- z.y *z.y;
   zSquare.y=2*z.x*z.y;
   return zSquare;
}
GLint mandelSqTransf(complexNum z0,GLint maxIter) {
    complexNum z = z0;
    GLint count = 0;
    /* Quit whenz*z > 4 */
    while ((z.x * z.x + z.y * z.y <= 4.0) && (count < maxIter)) {
        z=complexSquare(z);
        z.x += z0.x;
        z.y +=z0.y;
        count++;
    }
    return count;
}
void mandelbrot(GLint nx, GLint ny, GLint maxIter) {
    complexNum z, zIncr;
    color ptColor;
    GLint iterCount;
    zIncr.x = complexWidth / GLfloat(nx);
    zIncr.y = complexHeight / GLfloat(ny);
    for (z.x = xComplexMin; z.x < xComplexMax; z.x += zIncr.x)
        for (z.y = yComplexMin; z.y < yComplexMax; z.y += zIncr.y) {
            iterCount = mandelSqTransf(z, maxIter);
            if (iterCount >= maxIter)
                /*Set point color to black .*/
                ptColor.r = ptColor.g = ptColor.b = 0.0;
            else if (iterCount > (maxIter / 8)) {
                /* Set point color to orange.*/
                ptColor.r = 1.0;
                ptColor.g = 0.5;
                ptColor.b = 0.0;
            }
            else if (iterCount > (maxIter / 10)) {
                /*set point color to red.*/
                ptColor.r = 1.0;
                ptColor.g = ptColor.b = 0.0;
            }
            else if (iterCount > (maxIter / 20)) {
                /*Set point color to dark blue. */
                ptColor.b = 0.5;
                ptColor.r = ptColor.g = 0.0;

            }
            else if (iterCount > (maxIter / 40)) {
                /*Set point color to yellow. */
                ptColor.r = ptColor.g = 1.0;
                ptColor.b = 0.0;
            }
            else if (iterCount > (maxIter / 100) ){
                /*set pointcolor to dark green */
                ptColor.r = 0.0;
                    ptColor.b = 0.0;
                    ptColor.g = 0.3;

            }
            else {
                /*set pointcolor to cyan */
                ptColor.r = 0.0;
                    ptColor.b = ptColor.g = 1.0;

            }
            glColor3f(ptColor.r, ptColor.g, ptColor.b);
            plotPoint(z);
        }
}
void displayFcn() {
/*set number of x and y sudsvs. and the max iterations.*/
    GLint nx = 1000, ny = 1000, maxIter = 1000;
    glClear(GL_COLOR_BUFFER_BIT);
    mandelbrot(nx, ny, maxIter);
    glFlush();

}
void winReshapeFcn(GLint newWidth, GLint newHeight) {
    glViewport(0, 0, newHeight, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
    glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Mandelbrot Set");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
    return 0;
}
