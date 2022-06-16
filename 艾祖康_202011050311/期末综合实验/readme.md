## 本段代码实现了绘制一个3D渲染茶壶增加了太阳光照
## 实验要求
利用Visual C++, OpenGL, Java等工具，实现三维图形渲染，自定义三维图形，三维图形不能仅仅是简单的茶壶、球体、圆柱体、圆锥体等图形，渲染过程须加入纹理、色彩、光照、阴影、透明等效果，可采用光线跟踪、光照明模型、纹理贴图、纹理映射等算法。
## 实验过程：
首先：main函数中，我们初始化 GLUT 库，从 main 函数获取其两个参数.对应main 函数的形式应是:int main(int argc,char* argv[]);接下来定义窗口的大小为宽640，高480.定义初始化窗口的位置，并且在在创建窗口的时候，指定其显示模式的类型。建立一个窗口名称为GLUT Shape的窗口。调用初始化函数，对最初的光照进行一系列的操作：首先我们利用GLfloat ambien[]以及GLfloat diffuse[]、GLfloat position[] 对光源的颜色和位置进行定义，通过利用light_specular设置我们的高亮反色光，同时通过glLightfv()我们可以选择不同的光照模型，使用GLfloat mat（）我们可以定义材料属性，利用glMaterialfv（）我们可以指定材料的属性，最后我们可以利用glLightfv（）创建光源，并且利用glEnable()启动光源  。设置完光照之后我们可以通过glutReshapeFunc函数达到自适应窗口大小的改变的效果。在resize函数中，默认情况下，视口被设置为占据打开窗口的整个像素矩形，窗口大小和设置视口大小相同，所以为了选择一个更小的绘图区域，我们就可以用glViewport函数来实现这一变换。同时我们调用调用glLoadIdentity()，恢复初始坐标系。最后我们通过gluPerspective 函数指定世界坐标系的查看图面。之后我们调用glutDisplayFunc（）函数配合glutReshapeFunc函数进行窗口的重绘。在display函数中，我们调用了glutSolidTeapot函数完成茶壶的绘制，利用glRotatef函数完成茶壶的旋转操作等之后我们利用glutKeyboardFunc进行键盘的控制，我们定义+、-按键分别为左右旋转并且按键q可以实现程序的退出。并最终完成了整个程序。

## 实验结果

![image](https://github.com/kiritoazk/Computer_Graphics/blob/main/%E8%89%BE%E7%A5%96%E5%BA%B7_202011050311/img/capture_20220608184853769.bmp)

![image](https://github.com/kiritoazk/Computer_Graphics/blob/main/%E8%89%BE%E7%A5%96%E5%BA%B7_202011050311/img/capture_20220612171700545.bmp)

## 实验总结

经过本次实验，我们实现了绘制一个茶壶并且指定其材质并添加光照的功能。在实验的过程中，我们对于三维几何物体如何添加光照、设置光照模型、定义光源的颜色以及位置等操作有了一定的了解，并且在具体的操作实践中，我们还学会了如何给自己的茶壶选择材料属性、定义自己茶壶的材质等一系列操作。对于真实感图形的实现有了初步的了解
