#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <math.h>
#include <windows.h>
typedef float Color[3];
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);//投影模型
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}
bool compareColor(Color c1, Color c2) {
    for (int i = 0; i < 3; i++)
        if (c1[i] - c2[i] > 0.001 || c1[i] - c2[i] < -0.001) return false;
    return true;
}
void setpixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getpixel(GLint x, GLint y, Color& color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);//先加载所有缓存区的像素点，再找目标点的颜色 
}
void boundaryFill4(int x, int y, Color fillColor, Color boarderColor) {
    Color interiorColor;
    getpixel(x, y, interiorColor);
    glColor3fv(fillColor);
    if (!(compareColor(interiorColor, fillColor))  && !(compareColor(interiorColor, boarderColor) )) {
        setpixel(x, y);
        boundaryFill4(x + 1, y, fillColor, boarderColor);
        boundaryFill4(x - 1, y, fillColor, boarderColor);
        boundaryFill4(x, y + 1, fillColor, boarderColor);
        boundaryFill4(x, y - 1, fillColor, boarderColor);
    }

}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    glLineWidth(2.0f);
    double w = glutGet(GLUT_WINDOW_WIDTH);
    double h = glutGet(GLUT_WINDOW_HEIGHT);
    float offset = 160;
    glBegin(GL_LINE_LOOP);
    glVertex2f(0 + offset, 0 + offset);
    glVertex2f(0 + offset, h - offset);
    glVertex2f(w - offset, h - offset);
    glVertex2f(w - offset, 0 + offset);
    glEnd();
    Color fillColor = { 0.0, 1.0, 1.0 };//填充颜色 蓝色
    Color boarderColor = { 0.0, 1.0, 0.0 };//边界颜色 绿色
    boundaryFill4(200, 200, fillColor, boarderColor);//设置起点坐标及颜色
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
    glutInitWindowPosition(400, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("BoundaryFill1");
    
    init();
    glutDisplayFunc(&display);
    glutMainLoop();
}