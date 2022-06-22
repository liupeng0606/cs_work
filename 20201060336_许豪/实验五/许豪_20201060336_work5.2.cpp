// zhongzitianchong.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include<vector>
#include<GL/glut.h>
#include<queue>
#include<stack>
using namespace std;
int window_width = 800, window_height = 600;

struct point
{
	int x, y;
	point()
	{}
	point(int xx, int yy)
		:x(xx), y(yy) {}
};
vector<point> vertice;
float newcolor[3] = { 1, 0, 0 };
float boundarycolor[3] = { 0, 0, 1 };

void draw_a_point(int x, int y);
bool is_equal(float* a, float* b);
void BoundaryFill4(int x, int y);
void BoundaryFill4_Stack(int x, int y);
void mymouse(int button, int state, int x, int y);
void KeyBoards(unsigned char key, int x, int y);

int main(int argc, char* argv[])
{
	cout << "点击鼠标左键画点；" << endl << "点击鼠标右键结束画点，形成多边形；" << endl << "点击鼠标中键确定区域填充种子点位置。" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("区域种子填充");
	glMatrixMode(GL_PROJECTION);/*设置为投影类型模式和其他观察参数*/
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();/*设置为投影类型模式和其他观察参数*/
	//gluOrtho2D(0, window_width, window_height, 0);/*设置为投影类型模式和其他观察参数，观察窗口的大小要与画布大小一致，所以直接设置全局变量即可*/
	gluOrtho2D(0, window_width, 0, window_height);//上面的不可以！！！

	glClearColor(1, 1, 1, 1);//设置绘制窗口颜色为白色
	glClear(GL_COLOR_BUFFER_BIT);

	glutMouseFunc(&mymouse);
	//glutKeyboardFunc(&KeyBoards);
	glutMainLoop();
	return 0;
}


void draw_a_point(int x, int y)
{
	glBegin(GL_POINTS);
	glColor3fv(newcolor);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}
bool is_equal(float* a, float* b)
{
	return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}
void BoundaryFill4(int x, int y)
{
	queue<point> q;
	q.push(point(x, y));
	while (!q.empty())
	{
		point now = q.front();
		q.pop();
		int nowx = now.x, nowy = now.y;
		int temx, temy;
		temx = nowx;
		temy = nowy;
		float color[3];
		glReadPixels(nowx, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
		if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
		{
			glReadPixels(temx + 1, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
			while (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{
				temx = temx + 1;
				glReadPixels(temx + 1, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
				if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
				{
					draw_a_point(temx, nowy);
				}
				else
				{
					q.push(point(temx + 1, nowy));

				}
			}

			temx = nowx;
			glReadPixels(nowx, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
			while (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{
				temy = temy + 1;
				glReadPixels(nowx, temy + 1, 1, 1, GL_RGB, GL_FLOAT, color);
				if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
				{
					draw_a_point(nowx, temy);
				}
				else
				{
					q.push(point(nowx, temy));
					break;
				}
			}
			temy = nowy;
			glReadPixels(nowx, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
			while (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{

				temx = temx - 1;
				glReadPixels(temx - 1, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
				if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
				{
					draw_a_point(temx, nowy);
				}
				else
				{
					q.push(point(temx, nowy));
					break;
				}
			}

			temx = nowx;
			glReadPixels(nowx, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
			while (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{

				temy = temy - 1;
				glReadPixels(nowx, temy - 1, 1, 1, GL_RGB, GL_FLOAT, color);
				if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
				{

					draw_a_point(nowx, temy);
				}
				else
				{
					q.push(point(nowx, temy));
					break;
				}
			}

			draw_a_point(nowx, nowy);
		}
	}
}


void BoundaryFill4_Stack(int x, int y)
{
	stack < point> q;
	q.push(point(x, y));
	while (!q.empty())
	{
		point now = q.top();
		q.pop();
		int nowx = now.x, nowy = now.y;
		int temx, temy;
		int flag = 0;
		temx = nowx;
		temy = nowy;
		float color[3];
		glReadPixels(nowx, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
		if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
		{
			glReadPixels(nowx + 1, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
			if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{
				flag = flag + 1;
			}

			glReadPixels(nowx, nowy - 1, 1, 1, GL_RGB, GL_FLOAT, color);
			if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{
				flag = flag + 1;
			}

			glReadPixels(nowx - 1, nowy, 1, 1, GL_RGB, GL_FLOAT, color);
			if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{
				flag = flag + 1;
			}

			glReadPixels(nowx, nowy + 1, 1, 1, GL_RGB, GL_FLOAT, color);
			if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{
				flag = flag + 1;
			}


			draw_a_point(nowx, nowy);
			q.push(point(nowx + 1, nowy - 1));
			q.push(point(nowx - 1, nowy - 1));
			q.push(point(nowx + 1, nowy + 1));
			q.push(point(nowx - 1, nowy + 1));
		}


		if (flag != 0)
		{
			glReadPixels(temx + 1, temy, 1, 1, GL_RGB, GL_FLOAT, color);
			while (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{
				temx = temx + 1;
				glReadPixels(temx + 1, temy, 1, 1, GL_RGB, GL_FLOAT, color);
				if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
				{
					draw_a_point(temx, temy);
				}
				else
				{
					q.push(point(temx, temy));
				}
			}

			temx = nowx; temy = nowy;
			glReadPixels(temx, temy - 1, 1, 1, GL_RGB, GL_FLOAT, color);
			while (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{

				temy = temy - 1;
				glReadPixels(temx, temy - 1, 1, 1, GL_RGB, GL_FLOAT, color);
				if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
				{
					draw_a_point(temx, temy);
				}
				else
				{
					q.push(point(temx, temy));
					break;
				}
			}

			temx = nowx; temy = nowy;
			glReadPixels(temx - 1, temy, 1, 1, GL_RGB, GL_FLOAT, color);
			while (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{
				temx = temx - 1;
				glReadPixels(temx - 1, temy, 1, 1, GL_RGB, GL_FLOAT, color);
				if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
				{
					draw_a_point(temx, temy);
				}
				else
				{
					q.push(point(temx, temy));
					break;
				}
			}

			temx = nowx; temy = nowy;
			glReadPixels(temx, temy + 1, 1, 1, GL_RGB, GL_FLOAT, color);
			while (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
			{
				temy = temy + 1;
				glReadPixels(temx, temy + 1, 1, 1, GL_RGB, GL_FLOAT, color);
				if (!is_equal(color, newcolor) && !is_equal(color, boundarycolor))
				{
					draw_a_point(temx, temy);
				}
				else
				{
					q.push(point(temx, temy));
					break;
				}
			}


			draw_a_point(nowx, nowy);
		}
	}
	/*q.push(point(nowx, nowy + 1));
	q.push(point(nowx, nowy - 1));
	q.push(point(nowx + 1, nowy));
	q.push(point(nowx - 1, nowy));*/
}
void mymouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		draw_a_point(x, window_height - y);

		point p(x, window_height - y);
		vertice.push_back(p);
		cout << "顶点" << vertice.size() << ": (" << x << ", " << y << ")" << endl;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glClearColor(1, 1, 1, 1);//设置绘制窗口颜色为白色
		glColor3fv(boundarycolor);
		glLineWidth(4);
		glBegin(GL_LINES);

		for (int i = 0; i < vertice.size(); i++)
		{
			if (i == vertice.size() - 1)//画完最后一个点，使其闭合
			{
				glVertex2f(vertice[0].x, vertice[0].y);
				glVertex2f(vertice[i].x, vertice[i].y);
			}
			else
			{
				glVertex2f(vertice[i].x, vertice[i].y);
				glVertex2f(vertice[i + 1].x, vertice[i + 1].y);
			}
		}
		glEnd();
		glFlush();
		vertice.clear();
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		cout << "center: (" << x << ", " << y << ")" << endl;
		//BoundaryFill4(x, window_height - y);
		BoundaryFill4_Stack(x, window_height - y);
	}
}
void KeyBoards(unsigned char key, int x, int y)
{
	if (key == 32)
	{
		BoundaryFill4(x, window_height - y);
		glFlush();
	}
}
