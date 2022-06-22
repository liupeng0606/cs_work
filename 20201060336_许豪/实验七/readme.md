# 实验七 GLUT鼠标函数实验和反走样实验
## 时间：2022年4月27 日  地点：信息学院2202机房
### 实验内容：教材P458，GLUT鼠标函数使用opengl，实现任一反走样技术。实验目的：调用鼠标函数完成相应功能，2~3个程序。







![image](https://github.com/Polaris1491319352/Graphics/blob/main/image/work7_1.jpg)  
![image](https://github.com/Polaris1491319352/Graphics/blob/main/image/work7_2.jpg)  
_实验体会：在OpenGL中处理鼠标事件非常的方便，GLUT已经注册好了函数，只要调用方法即可。使用函数glutMouseFunc,就可以注册函数，这样当发生鼠标事件时就会自动调用我们的方法。GLUT提供鼠标动作检测能力。有两种GLUT处理的motion：active motion和passive motion。Active motion是指鼠标移动并且有一个鼠标键被按下。Passive motion是指当鼠标移动时，并有没鼠标键按下。如果一个程序正在追踪鼠标，那么鼠标移动期间，每一帧将产生一个结果。
绘制的物体边缘部分出现锯齿的现象称之为走样。反走样是减轻这种现象的方法。有前滤波和后滤波。_
