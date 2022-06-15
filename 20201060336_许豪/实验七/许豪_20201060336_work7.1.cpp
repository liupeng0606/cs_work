#include <iostream>
// test3.cpp : 定义控制台应用程序的入口点。
//


#include <math.h>
#include <GL/glut.h>

#define GLUT_LEFT_BUTTON    0
#define GLUT_MIDDLE_BUTTON  1
#define GLUT_RIGHT_BUTTON    2
#define GLUT_DOWN        0
#define GLUT_UP          1
int Width = 500, Height = 500;
int x01, y01, x02, y02;
int FirstPointHaveDraw = 0;
int RightButtonDown = 0;
float red = 0.0f, green = 0.0f, blue = 0.0f;
int moveSpeed = 2;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
	glMatrixMode(GL_PROJECTION);       // Set projection parameters.
	gluOrtho2D(0.0, Width, 0.0, Height);  //设置窗口坐标范围
}

void lineBres(int x0, int y0, int xEnd, int yEnd, int red, int green, int blue)
{
	glPointSize(4);
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
	//画第一个点
	if (x0 > xEnd)
	{
		int t;
		t = x0; x0 = xEnd; xEnd = t;
		t = y0; y0 = yEnd; yEnd = t;
	}
	int x = x0;
	int y = y0;
	glVertex2i(x, y);
	//当线段垂直时。
	if (x0 == xEnd)
	{
		while (y < yEnd)
		{
			y++;
			glVertex2i(x, y);
		}
		glEnd();
		glFlush();
		return;
	}
	//当线段水平时。
	if (y0 == yEnd)
	{
		while (x < xEnd)
		{
			x++;
			glVertex2i(x, y);
		}
		glEnd();
		glFlush();
		return;
	}
	int dx = xEnd - x0;
	int dy = yEnd - y0;
	int twoDx = 2 * dx;
	int twoDy = 2 * dy;
	int twoDyMinusDx = 2 * (dy - dx);
	int twoDxMinusDy = 2 * (dx - dy);
	int twoDxAddDy = 2 * (dx + dy);
	int p;
	double k = (double)(yEnd - y0) / (double)(xEnd - x0);
	//斜率
	//当线段斜率0<k<=1时。
	if (0 < k && k <= 1)
	{
		p = 2 * dy - dx;
		while (x < xEnd)
		{
			x++;
			if (p < 0)
			{
				p += twoDy;
			}
			else
			{
				y++;
				p += twoDyMinusDx;
			}
			glVertex2i(x, y);
		}
		glEnd();
		glFlush();
		return;
	}
	//当线段斜率-1<=k<0时。
	if (k < 0 && k >= -1)
	{
		p = 2 * dy + dx;
		while (x < xEnd)
		{
			x++;
			if (p >= 0)
				p += twoDy;
			else
			{
				y--;
				p += twoDxAddDy;
			}
			glVertex2i(x, y);
		}
		glEnd();
		glFlush();
		return;
	}
	//当线段斜率k<-1时。
	if (k < -1)
	{
		p = 2 * dx - dy;
		while (y > yEnd)
		{
			y--;
			if (p >= 0)
				p -= twoDx;
			else
			{
				x++;
				p -= twoDxAddDy;
			}
			glVertex2i(x, y);
		}
		glEnd();
		glFlush();
		return;
	}
	//当线段斜率k>1时。
	if (k > 1)
	{
		p = dy;
		while (y < yEnd)
		{
			y++;
			if (p < 0)
			{
				p += twoDx;
			}
			else
			{
				x++;
				p -= twoDyMinusDx;
			}
			glVertex2i(x, y);
		}
		glEnd();
		glFlush();
		return;
	}
}

void Drawline(int button, int state, int x, int y)
{
	glPointSize(1);
	glColor3f(0.1, 0.0, 0.0);
	if (RightButtonDown == 0)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_DOWN)
			{
				if (FirstPointHaveDraw == 0)
				{
					x01 = x;
					y01 = Height - y;
					glPointSize(2);
					glBegin(GL_POINTS);
					glVertex2i(x01, y01);
					glEnd();
					glFlush();
					FirstPointHaveDraw = 1;
				}
				printf("画下点 x:%d,y:%d\n", x01, y01);
			}
			else
			{
				x02 = x;
				y02 = Height - y;
				lineBres(x01, y01, x02, y02, red, green, blue);
				FirstPointHaveDraw = 0;
			}
		}
	}
}

void mousemove(int x, int y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	printf("鼠标移动中, x:%d,y:%d\n", x, Height - y);
	lineBres(x01, y01, x, Height - y, red, green, blue);
}

void ColorMenu(int value) {

	switch (value)
	{
	case 1:red = 1.0; green = 0.0; blue = 0.0; break;
	case 2:red = 0.0; green = 1.0; blue = 0.0; break;
	case 3:red = 0.0; green = 0.0; blue = 1.0; break;
	default:break;
	}
}

void myMenu(int value)
{
	if (value == 0)
	{
		exit(0);
	}
	else
	{
		ColorMenu(value);
	}
}

void ProcessSpecialKeyboead(int key, int x, int y)
{
	if (GLUT_KEY_UP == key)
	{
		printf("up\n");
		y01 += moveSpeed;
		y02 += moveSpeed;
		glClear(GL_COLOR_BUFFER_BIT);
		lineBres(x01, y01, x02, y02, red, green, blue);
		glFlush();
	}
	if (GLUT_KEY_DOWN == key)
	{
		printf("down\n");
		y01 -= moveSpeed;
		y02 -= moveSpeed;
		glClear(GL_COLOR_BUFFER_BIT);
		lineBres(x01, y01, x02, y02, red, green, blue);
		glFlush();
	}
	if (GLUT_KEY_LEFT == key)
	{
		printf("left\n");
		x01 -= moveSpeed;
		x02 -= moveSpeed;
		glClear(GL_COLOR_BUFFER_BIT);
		lineBres(x01, y01, x02, y02, red, green, blue);
		glFlush();
	}
	if (GLUT_KEY_RIGHT == key)
	{
		printf("right\n");
		x01 += moveSpeed;
		x02 += moveSpeed;
		glClear(GL_COLOR_BUFFER_BIT);
		lineBres(x01, y01, x02, y02, red, green, blue);
		glFlush();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(100, 100);   // Set top-left display-window position.
	glutInitWindowSize(Width, Height);      // 设置窗口在显示器上的大小
	glutCreateWindow("An Example OpenGL Program"); // Create display window.

	init();                            // Execute initialization procedure.
	glClear(GL_COLOR_BUFFER_BIT);
	glutMouseFunc(Drawline);
	glutMotionFunc(mousemove);
	int sub_menu;
	sub_menu = glutCreateMenu(ColorMenu);
	glutAddMenuEntry("Red", 1);//添加菜单项  
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutCreateMenu(myMenu);//注册菜单回调函数
	//glutAddMenuEntry("Rotate", 4);
	glutAddSubMenu("Color", sub_menu);
	glutAddMenuEntry("Exit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//把当前菜单注册到指定的鼠标键  
	glutSpecialFunc(ProcessSpecialKeyboead);
	glutMainLoop();                    // Display everything and wait.
}
