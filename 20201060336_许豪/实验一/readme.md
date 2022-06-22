# 实验一 直线段生成算法
## 信息学院2202机房 2022年3月16日
## OpenGL glut的安装；  初步熟悉OpenGL编程及其编程框架；  熟悉OpenGL，通过示例程序生成直线段等图元；  
```  
void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT);// 清空显示窗口

    glColor3f(0.0, 0.4, 0.2);// 指定前景色（当前绘制颜色）为蓝色
    glBegin(GL_LINES);
    glVertex2i(180, 15);// 指定顶点
    glVertex2i(10, 145);
    glEnd();
    glFlush();// 使绘制立即反映到屏幕上
}  
```



![image](https://github.com/Polaris1491319352/Graphics/blob/main/image/work_1.jpg)
_这个实验主要是根据书上的一个实例来体会opengl的操作，实现画线算法以及后面的各种图形图像算法的主要部分就是利用glut.h这个包中的函数来实现，所以我们需要了解其中函数的功能和使用方法。如main中第一步要glutInit(&argc, argv); // 初始GLUT，可以使用 glutCreateWindow("An Example OpenGL Program");在窗口创建时给一个标题，利用glutDisplayFunc(lineSegment);// 指定绘制的回调函数，在窗口中显示，然后利用glutMainLoop(); // 进入无穷循环，等待事件处理，将已创建的显示窗口连同其中的图形内容激活，这个函数语句必须是最后一条。到此main函数的基本形式已经确定下来了，后序只需更改回调函数。在visual studio运行opengl的时候，每次必定出现LNK1104 无法打开文件“freeglutd.lib”的错误，必须在每个程序包中安装：项目->管理NuGet程序包->浏览->搜索 NupenGL 安装第一个即可。_
