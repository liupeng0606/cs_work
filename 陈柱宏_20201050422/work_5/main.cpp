// Bresenham_circile.cpp : 定义控制台应用程序的入口点。
#include<stdlib.h>
#include <GL/glut.h>

/* initialization: */
void myinit(void)
{

    /* attributes */

    glClearColor(1.0, 1.0, 1.0, 0.0); /* white background */
    glColor3f(1.0, 0.0, 0.0); /* draw in red */

/* set up viewing: */
/* 500 x 500 window with origin lower left */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}
void  plot_circle_points(int xc, int yc, int x, int y)
{
    glBegin(GL_POINTS);
    glVertex3f(xc + x, yc + y, 0);
    glVertex3f(xc - x, yc + y, 0);
    glVertex3f(xc + x, yc - y, 0);
    glVertex3f(xc - x, yc - y, 0);
    glVertex3f(xc + y, yc + x, 0);
    glVertex3f(xc - y, yc + x, 0);
    glVertex3f(xc + y, yc - x, 0);
    glVertex3f(xc - y, yc - x, 0);
    glEnd();
}
void drawcircle(int xc, int yc, int radius)
{
    int x, y, p;
    x = 0;
    y = radius;
    p = 3 - 2 * radius;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    while (x < y)
    {
        plot_circle_points(xc, yc, x, y);
        if (p < 0)
            p = p + 4 * x + 6;
        else
        {
            p = p + 4 * (x - y) + 10;
            y -= 1;
        }
        x += 1;
    }
    if (x == y)
        plot_circle_points(xc, yc, x, y);
}


/* the display callback: */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */

    /*----------------------------------------*/
    /*  viewport stuff                        */
    /*----------------------------------------*/
    /* set up a viewport in the screen window */
    /* args to glViewport are left, bottom, width, height */
    glViewport(0, 0, 500, 500);
    /* NB: default viewport has same coords as in myinit, */
    /* so this could be omitted: */


    drawcircle(200, 200, 100);

    /* and flush that buffer to the screen */
    glFlush();
}

int main(int argc, char** argv)
{

    /* Standard GLUT initialization */

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); /* default, not needed */
    glutInitWindowSize(500, 500); /* 500 x 500 pixel window */
    glutInitWindowPosition(0, 0); /* place window top left on display */
    glutCreateWindow("Bresenham  circile"); /* window title */
    glutDisplayFunc(display); /* display callback invoked when window opened */
    myinit(); /* set attributes */
    glutMainLoop(); /* enter event loop */
}