#include <windows.h>
#include <GL/glut.h>
#include <fstream>

typedef float Color[3];

//获取像素点的颜色
void getpixel(GLint x, GLint y, Color color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

//画点函数
void setpixel(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

//比较颜色是否相等
int compareColor(Color color1, Color color2) {
    if (color1[0] != color2[0] || color1[1] != color2[1] || color1[2] != color2[2]) { return 0; }
    else { return 1; }
}

void boundaryFill4(int x, int y, Color fillColor, Color boarderColor) {
    Color interiorColor;
    getpixel(x, y, interiorColor);
    if (compareColor(interiorColor, fillColor) == 0 && compareColor(interiorColor, boarderColor) == 0) {
        setpixel(x, y);
        boundaryFill4(x + 1, y, fillColor, boarderColor);
        boundaryFill4(x - 1, y, fillColor, boarderColor);
        boundaryFill4(x, y + 1, fillColor, boarderColor);
        boundaryFill4(x, y - 1, fillColor, boarderColor);
    }

}

void boundaryFill8(int x, int y, Color fillColor, Color boarderColor) {
    Color interiorColor, a, b, c, d;
    getpixel(x, y, interiorColor);
    getpixel(x + 1, y - 1, a);
    getpixel(x, y - 1, b);
    getpixel(x, y + 1, c);
    getpixel(x - 1, y, d);
    int i = 0;
    if (compareColor(a, boarderColor) == 1) i++;
    if (compareColor(b, boarderColor) == 1) i++;
    if (compareColor(c, boarderColor) == 1) i++;
    if (compareColor(d, boarderColor) == 1) i++;
    if (i <= 1) {
        if (compareColor(interiorColor, fillColor) == 0 && compareColor(interiorColor, boarderColor) == 0) {
            setpixel(x, y);
            boundaryFill8(x + 1, y, fillColor, boarderColor);
            boundaryFill8(x, y - 1, fillColor, boarderColor);
            boundaryFill8(x - 1, y, fillColor, boarderColor);
            boundaryFill8(x, y + 1, fillColor, boarderColor);
            boundaryFill8(x + 1, y - 1, fillColor, boarderColor);
            boundaryFill8(x - 1, y - 1, fillColor, boarderColor);
            boundaryFill8(x - 1, y + 1, fillColor, boarderColor);
            boundaryFill8(x + 1, y + 1, fillColor, boarderColor);

        }
    }

}

void polygon() {
    glBegin(GL_LINE_LOOP);
    glLineWidth(5);
    //此处修改坐标，绘制多边形
    glVertex2f(100, 100);
    glVertex2f(75, 125);
    glVertex2f(125, 110);
    glEnd();
}

void display(void) {
    Color fillColor = { 1.0, 1.0, 0.0 };//填充颜色
    Color boarderColor = { 0.0, 0.0, 1.0 };//边界颜色    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 500, 500);
    glColor3fv(boarderColor);
    polygon();
    glColor3fv(fillColor);
    //boundaryFill4(150, 150, fillColor, boarderColor);//设置起点坐标及颜色
    boundaryFill8(110, 110, fillColor, boarderColor);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("BoundaryFill1");

    glClearColor(1, 1, 1, 0.0);
    glMatrixMode(GL_PROJECTION);//投影模型
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;

}
