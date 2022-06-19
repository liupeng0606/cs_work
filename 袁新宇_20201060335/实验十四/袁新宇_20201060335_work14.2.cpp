#include <GL/glut.h>
#include <stdlib.h>

GLfloat ctrlpoints[4][3] = { {-40.0,-40.0,0.0},{-20.0,40.0,0.0},{20.0,-40.0,0.0},{40.0,40.0,0.0}};//控制点  
GLsizei winWidth = 500, winHeight = 500;

GLfloat xwcMin = -100.0, xwcMax = 100.0;
GLfloat ywcMin = -250.0, ywcMax = 250.0;

void init(void){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, *ctrlpoints);
    glEnable(GL_MAP1_VERTEX_3);
}

void display(void){
    GLint i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);  
    for (i = 0; i <= 50; i++)
        glEvalCoord1f(GLfloat(i) / 50.0);
    glEnd();
    /* The following code displays the control points as dots. */
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 4; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
    glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
    glViewport(0, 0, newHeight, newHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);

    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth,winHeight);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Bezier Curve");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
    return 0;
}
