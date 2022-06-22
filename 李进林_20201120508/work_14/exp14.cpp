#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
GLsizei winWIdth = 600, winHeight = 600;
GLfloat xwcMin = -50.0, xwcMax = 50.0, ywcMin = -50.0, ywcMax = 50.0;
class wcPt3D
{
public:
    GLfloat x, y, z;
};
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
void plotPoint(wcPt3D p)
{
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
}
void binomialCoeffs(GLint n, GLint *C)
{
    GLint i, j;
    for (i = 0; i <= n; i++)
    {
        C[i] = 1;
        for (j = n; j >= i + 1; j--)
        {
            C[i] *= j;
        }
        for (j = n - i; j >= 2; j--)
        {
            C[i] /= j;
        }
    }
}
void computeBezPt(GLfloat u, wcPt3D *bezPt, GLint nCtrlPts, wcPt3D *ctrlPts, GLint *C)
{
    GLint i, j = nCtrlPts - 1;
    GLfloat bezBlendFcn;
    bezPt->x = bezPt->y = bezPt->z = 0.0;
    for (i = 0; i < nCtrlPts; i++)
    {
        bezBlendFcn = C[i] * pow(u, j) * pow(1 - u, j - i);
        bezPt->x += ctrlPts[i].x * bezBlendFcn;
        bezPt->y += ctrlPts[i].y * bezBlendFcn;
        bezPt->z += ctrlPts[i].z * bezBlendFcn;
    }
}
void bezier(wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezPts)
{
    GLint *C, k;
    GLfloat u;
    wcPt3D bezPt;
    C = new GLint[nCtrlPts];
    binomialCoeffs(nCtrlPts - 1, C);
    for (k = 0; k <= nBezPts; k++)
    {
        u = GLfloat(k) / GLfloat(nBezPts);
        computeBezPt(u, &bezPt, nCtrlPts, ctrlPts, C);
        plotPoint(bezPt);
    }
    delete[] C;
}
void displayFcn(void)
{
    GLint nCtrlPts = 4, nBezCurvePts = 1000;
    wcPt3D ctrlPts[4] = {
        {-40.0, -40.0, 0.0},
        {-10.0, 200.0, 0.0},
        {10.0, -200.0, 0.0},
        {40.0, 40.0, 0.0}};
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);
    glColor3f(1.0, 0.0, 0.0);
    bezier(ctrlPts, nCtrlPts, nBezCurvePts);
    glFlush();
}
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}
void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWIdth, winHeight);
    glutCreateWindow("Bezier Curve");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
}