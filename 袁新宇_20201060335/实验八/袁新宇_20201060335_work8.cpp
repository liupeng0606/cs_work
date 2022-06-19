#include<stdio.h>
#include <GL/glut.h>

#define left 1
#define right 2
#define bottom 4
#define top 8
class LineClass{
public:
    GLfloat x1, y1, x2, y2;
    GLfloat x1_init, y1_init, x2_init, y2_init;
}line;

/*边界的坐标*/
GLfloat xleft = 50, xright = 350, ytop = 300, ybottom = 100;

/*判断点的所在区域*/
GLint encode(GLfloat x, GLfloat y) {
    GLint code = 0;
    if (x < xleft)  code |= left;
    if (x > xright)  code |= right;
    if (y > ytop) code |= top;
    if (y < ybottom)  code |= bottom;
    return code;
}

void pointChange() {
    GLfloat x=0, y=0, x0, y0;
    if (line.x1 == line.x2) line.x1++;
    if (line.y1 == line.y2) line.y1++;

    line.x1_init = line.x1;
    line.x2_init = line.x2;
    line.y1_init = line.y1;
    line.y2_init = line.y2;

    /*两个端点的编码*/
    GLint code1, code2;
    code1 = encode(line.x1, line.y1);
    code2 = encode(line.x2, line.y2);

    GLint code;

    /*直线不完全在裁剪窗口中中*/
    while (code1 != 0 || code2 != 0) {
        if (code1 & code2) {
            line.x1 = 0;
            line.x2 = 0;
            line.y1 = 0;
            line.y2 = 0;
            break;
         }

         if (code1 != 0)  code = code1;
         else code = code2;
         y0 = line.y1;
         x0 = line.x1;

         /*部分直线在裁剪窗口左边*/
         if (code & left) {
             x = xleft;
             y = y0 - (x0 - x) * (line.y1 - line.y2) / (line.x1 - line.x2);
         }
         /*部分直线在裁剪窗口右边*/
         else if (code & right) {
             x = xright;
             y = y0 - (x0 - x) * (line.y1 - line.y2) / (line.x1 - line.x2);
         }
         /*在裁剪窗口的下面*/
         else if (code & bottom) {
             y = ybottom;
             x = x0 - (y0 - y) * (line.x1 - line.x2) / (line.y1 - line.y2);
         }
         /*在裁剪窗口的上面*/
         else if (code & top) {
            y = ytop;
            x = x0 - (y0 - y) * (line.x1 - line.x2) / (line.y1 - line.y2);
         }
         /*更新数据*/
         if (code == code1) {
            line.x1 = x;
            line.y1 = y;
            code1 = encode(line.x1, line.y1);
         }
         else {
            line.x2 = x;
            line.y2 = y;
            code2 = encode(line.x2, line.y2);
         }
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
    pointChange();
}

void displayFcn() {
    glClear(GL_COLOR_BUFFER_BIT);
    /*边框颜色*/
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xleft, ybottom);
    glVertex2f(xright, ybottom);
    glVertex2f(xright, ytop);
    glVertex2f(xleft, ytop);
    glEnd();

    glFlush();
    /*画出原始的直线*/
    glColor3f(1.0, 0.5, 0.9);
    glPointSize(2);
    glBegin(GL_LINES);
    glVertex2f(line.x1_init, line.y1_init);
    glVertex2f(line.x2_init, line.y2_init);
    glEnd();
    glFlush();

    /*画出裁剪后的直线*/
    glColor3f(0.0, 1.0, 1.0);
    glPointSize(2);
    glBegin(GL_LINES);
    glVertex2f(line.x1, line.y1);
    glVertex2f(line.x2, line.y2);
    glEnd();
    glFlush();
}

int main(int argc, char* argv[]){
    printf("请分别输入两点坐标:");
    scanf_s("%f %f %f %f",&line.x1,&line.y1,&line.x2,&line.y2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Cohen-Sutherland");
    init();
    glutDisplayFunc(displayFcn);
    glutMainLoop();
    return 0;
}