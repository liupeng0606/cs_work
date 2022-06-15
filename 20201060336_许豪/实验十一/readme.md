# 实验十一 交互控制实验
## 实验内容：实验opengl，完成鼠标、键盘交互操作。 实验目的：熟悉鼠标键盘交互。 
### 时间：2022年5月17 日  地点：信息学院2202机房





![image](https://github.com/Polaris1491319352/Graphics/blob/main/image/work11.jpg)  
_OpenGL中通过鼠标和键盘跟程序交互的实现需要实现注册鼠标和键盘响应事件，在一定条件下，该事件被触发，事件里的程序被执行，达到交互的目的。
通过glutMouseFunc(&OnMouse)注册鼠标事件，OnMouse是鼠标事件的响应，函数格式是void OnMouse(int button,int state,int x,int y)；
通过glutKeyboardFunc(&KeyBoards)注册键盘事件，KeyBoards是键盘事件的响应，函数格式void KeyBoards(unsigned char key,int x,int y)；
对于鼠标func:形如void func(int button, int state, int x, int y);
button:鼠标的按键,为以下定义的常量 
  GLUT_LEFT_BUTTON:鼠标左键 
  GLUT_MIDDLE_BUTTON:鼠标中键 
  GLUT_RIGHT_BUTTON:鼠标右键 
state:鼠标按键的动作,为以下定义的常量 
  GLUT_UP:鼠标释放 
  GLUT_DOWN:鼠标按下 
x,y:鼠标按下式,光标相对于窗口左上角的位置
当点击鼠标时调用._
