//GLUT鼠标函数实验
#include <windows.h>
#include <GL/glut.h>
//窗口长宽
int width = 400, height = 400;
//鼠标点击位置
int hit_pos_x, hit_pos_y;
//鼠标拖动位置
int move_pos_x, move_pos_y;
//鼠标操作种类
int button_kind = -1;

void display()
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//重新设置OpenGL窗口：原点位置为左上角，x轴从左到右，y轴从上到下，坐标值与像素坐标值相同
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);

	if (button_kind == 0)	//左键点击
	{
		//画一个蓝色的点
		glPointSize(20);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(hit_pos_x, hit_pos_y);
		glEnd();
	}
	else if (button_kind == 2)	//右键点击
	{
		//画一个绿色的点
		glPointSize(20);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(hit_pos_x, hit_pos_y);
		glEnd();
	}
	else if (button_kind == 3)	//鼠标拖动
	{
		//沿拖动轨迹画一条红色的线
		glLineWidth(5);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(hit_pos_x, hit_pos_y);
		glVertex2f(move_pos_x, move_pos_y);
		glEnd();
	}

	//双缓存交换缓存以显示图像
	glutSwapBuffers();
	//每次更新显示
	glutPostRedisplay();
}

void mouse_hit(int button, int state, int x, int y)
{
	//鼠标操作种类赋值
	button_kind = button;

	//鼠标操作基本结构
	switch (button)
	{
	case GLUT_LEFT_BUTTON:	//左键操作，也可为数字0
		if (state == GLUT_DOWN)	//左键按下时
		{
			//记录按键位置
			hit_pos_x = x;
			hit_pos_y = y;
		}
		break;
	case GLUT_RIGHT_BUTTON:	//右键操作，也可为数字1
		if (state == GLUT_DOWN)	//右键按下时
		{
			//记录按键位置
			hit_pos_x = x;
			hit_pos_y = y;
		}
		break;
	default:
		break;
	}
}

void mouse_move(int x, int y)
{
	//鼠标移动时操作种类设为3(0 1 2分别为左键、中键、右键)
	button_kind = 3;
	//记录拖动位置
	move_pos_x = x;
	move_pos_y = y;
}

int main(int argc, char** argv)
{
	//初始化GL
	glutInit(&argc, argv);
	//设置显示参数(双缓存，RGB格式)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//设置窗口尺寸：width*height
	glutInitWindowSize(width, height);
	//设置窗口位置：在屏幕左上角像素值(100,100)处
	glutInitWindowPosition(100, 100);
	//设置窗口名称
	glutCreateWindow("OpenGL");
	//显示函数，display事件需要自行编写
	glutDisplayFunc(display);
	//鼠标点击函数，mouse_hit事件需要自行编写
	glutMouseFunc(mouse_hit);
	//鼠标拖动函数，mouse_move事件需要自行编写
	glutMotionFunc(mouse_move);


	//重复循环GLUT事件
	glutMainLoop();
	return 0;
}

