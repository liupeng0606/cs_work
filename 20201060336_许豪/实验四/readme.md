# 实验四 填充算法实验
## 时间：2022年4月6 日 地点：信息学院2202机房
##  教材P66，填充六边形。使用opengl，用扫描线填充算法填充多边形。
 
   
### 扫描线填充算法函数
```
void PolyScan()
{
	/*得到最高点的y坐标*/
	int Max_Y = 0;
	for (int i = 0; i < vertice.size(); i++)
		/*Max_Y = max(Max_Y, vertice[i].y);*/
		if (vertice[i].y > Max_Y)
			Max_Y = vertice[i].y;


	//初始化AET表
	AET* pAET = new AET;
	pAET->next = NULL;

	//初始化NET表
	NET* pNET[800]; //吊桶
	for (int i = 0; i <= Max_Y; i++)
	{
		pNET[i] = new NET;
		pNET[i]->next = NULL;;
	}

	//扫描并且建立NET表
	int len = vertice.size(); //顶点个数
	for (int i = 0; i <= Max_Y; i++)
	{
		for (int j = 0; j < len; j++) //扫描每个点
		{
			if (i == vertice[j].y)
			{
				//如果一个点和前一个点有一条边相连，则该点和后面一个点也相连
				//！这个式子 便于最后一个顶点和第一个点相连 和 防止出现负数

				//判断当前点的高低，使ymax、DX、DY的计算有变化
				if (vertice[(j - 1 + len) % len].y > vertice[j].y)
				{
					//前一个点在当前点的上方
					NET* p = new NET;
					p->x = vertice[j].x;
					p->ymax = vertice[(j - 1 + len) % len].y;//与当前扫描线相交的活性边 的 最高点即为相邻顶点的y
					float DX = vertice[(j - 1 + len) % len].x - vertice[j].x;
					float DY = vertice[(j - 1 + len) % len].y - vertice[j].y;
					p->dx = DX / DY;//dx为直线斜率的倒数
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
				if (vertice[(j + 1) % len].y > vertice[j].y)
				{
					//后一个点在当前点的上方
					NET* p = new NET;
					p->x = vertice[j].x;
					p->ymax = vertice[(j + 1) % len].y;
					float DX = vertice[(j + 1) % len].x - vertice[j].x;
					float DY = vertice[(j + 1) % len].y - vertice[j].y;
					p->dx = DX / DY;//dx为直线斜率的倒数
					p->next = pNET[i]->next;
					pNET[i]->next = p;
				}
			}
		}
	}

	//建立并且更新活性边表AET
	//各条扫描线i
	for (int i = 0; i <= Max_Y; i++)
	{
		/*把新边表NET[i] 中的边结点用插入排序法插入AET表，使之按x坐标递增顺序排列*/

		//计算每条扫描线上不同线产生的新的交点x，更新AET
		NET* p = pAET->next;
		while (p)
		{
			p->x = p->x + p->dx; //更新x坐标
			p = p->next;
		}

		//断表排序,不再开辟空间 
		AET* tq = pAET;
		p = pAET->next;
		tq->next = NULL;
		while (p)//顺着链表往下走
		{
			//找到第一个比它大的数字tq->next->next->x，则从p->next到tq->next都是比p->x小的
			while (tq->next != NULL && tq->next->x <= p->x)
				tq = tq->next;
			//插入p到tq和tq->next之间
			NET* t = p->next;
			p->next = tq->next;
			tq->next = p;
			p = t;

			tq = pAET;//回到头
		}

		/*(改进算法) 取消求交，减少计算量*/
		//先从AET表中删除ymax==i的结点****************************************/
		//像素的取舍问题，保证多边形的“下闭上开”，避免填充扩大化（交点的个数应保证为偶数个）
		AET* q = pAET;
		p = q->next;
		while (p)
		{
			if (p->ymax == i)
			{
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else
			{
				q = q->next;
				p = q->next;
			}
		}

		//若NET中有新点，将其用插入法插入AET，按x递增的顺序排列
		p = pNET[i]->next;
		q = pAET;
		while (p)
		{
			while (q->next && p->x >= q->next->x)
				q = q->next;
			//插入p
			NET* t = p->next;
			p->next = q->next;
			q->next = p;
			p = t;

			q = pAET;//回到头
		}

		//配对后填充颜色
		p = pAET->next;
		while (p && p->next != NULL)
		{
			for (float j = p->x; j <= p->next->x; j++)
			{
				//扫描线画点
				draw_a_point(j, i);
				//cout << "(" << j << ", " << i << ")" << endl;
			}
			p = p->next->next;//考虑端点情况
		}
	}
	glFlush();
}
```

![image](https://github.com/Polaris1491319352/Graphics/blob/main/image/work_4.1.jpg)  
  
![image](https://github.com/Polaris1491319352/Graphics/blob/main/image/work_4.2.jpg)
  
_实验体会:算法流程大概是
1.使用鼠标逐个输入多边形的定点，并且使用数组vertexes记录点的位置；
2.构建边表：
初始化边表数组的长度为绘图区域的高度；
由始至终遍历数组，分别将获取的顶点写入相应的边表位置：
若该点的相邻点在该点上方，则淘汰；
若该点的相邻点在该点的下方，则左下方点的边表元素应在右下方点所对应边表元素的右侧；
遍历完成，边表创建完成。
3.逐行构建活化边表并填充：
创建活化边表，初始化为空，仅包含首指针元素；
行遍历边表，并将全部得到的顶点写入活化边表；
活化边表中的数据项应随着扫描线的下移，在本层所有操作开始之前将dY递减、将x值逐层加上dX，并删除dY为0的节点；
当活化边表被清空时，遍历结束。_
