#include<GL/glut.h>
#include<stdio.h>
#include<windows.h>

int pointnum;
const int max = 10;
typedef struct XET {
	float x;
	float dx, ymax;
	XET* next;
}AET, NET;
struct point {
	float x;
	float y;
}

point[max]={};

void polyScan() {
	int MaxY = 0;
	int i;
	for (i = 0; i < pointnum; i++) {
		if (point[i].y > MaxY)
			MaxY = point[i].y;
	}
	AET* pAET = new AET;
	pAET->next = NULL;
	NET* pNET[1024];
	for (i = 0; i <= MaxY; i++) {
		pNET[i] = new NET;
		pNET[i]->next = NULL;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (i = 0; i < MaxY; i++) {
		for (int j = 0; j < pointnum; j++) {
			if (point[j].y == i) {
				if (point[(j - 1 + pointnum) % pointnum].y > point[j].y) {
					NET* p = new NET;
					p->x = point[j].x;
					p->ymax = point[(j - 1 + pointnum) % pointnum].y;
					p->dx = (point[(j - 1 + pointnum) % pointnum].x - point[j].x) / (point[(j - 1 + pointnum) % pointnum].y - point[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
				if (point[(j + 1 + pointnum) % pointnum].y > point[j].y) {
					NET* p = new NET;
					p->x = point[j].x;
					p->ymax = point[(j + 1 + pointnum) % pointnum].y;
					p->dx = (point[(j + 1 + pointnum) % pointnum].x - point[j].x) / (point[(j + 1 + pointnum) % pointnum].y - point[j].y);
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
			}
		}
	}
	for (i = 0; i <= MaxY; i++) {
		NET* p = pAET->next;
		while (p) {
			p->x = p->x + p->dx;
			p = p->next;
		}
		AET* tq = pAET;
		p = pAET->next;
		tq->next = NULL;
		while (p) {
			while (tq->next && p->x >= tq->next->x)
				tq = tq->next;
			NET* s = p->next;
			p->next = tq->next;
			tq->next = p;
			p = s;
			tq = pAET;
		}
		AET* q = pAET;
		p = q->next;
		while (p) {
			if (p->ymax == i) {
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else {
				q = q->next;
				p = q->next;
			}
		}
		p = pNET[i]->next;
		q = pAET;
		while (p) {
			while (q->next && p->x >= q->next->x)
				q = q->next;
			NET* s = p->next;
			p->next = q->next;
			q->next = p;
			p = s;
			q = pAET;
		}
		p = pAET->next;
		while (p && p->next) {
			for (float j = p->x; j <= p->next->x; j++) {
				glVertex2i(static_cast<int>(j), i);
			}
			p = p->next;
		}
	}
	glEnd();
	glFlush();
}

void main(int argc, char* argv) {
	int i;
	printf("请输入顶点个数\n");
	scanf_s("%d", & pointnum);
	for (i = 0; i < pointnum; i++) {
		printf("请输入第%d个点的坐标:",i+1);
		scanf_s("%f %f", &point[i].x, &point[i].y);
	}
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(700, 500);
	glutCreateWindow("扫描线填充算法");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 600.0, 0.0, 450.0);
	glutDisplayFunc(polyScan);
	glutMainLoop();
}