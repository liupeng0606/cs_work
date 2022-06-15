# 实验三
## 时间：2022年3月30日  地点：信息学院2202机房
## 1.实验内容：  熟悉OPENGL，通过Bresenham中点、改进Bresenham算法生成直线段  参考课本代码，了解Bresenham算法的原理。
```  
void lineBres(int x0,int y0,int xEnd,int yEnd)
{
    int dx = abs(xEnd-x0),dy=abs(yEnd-y0);
    int p=2*dy-dx;
    int twoDY=2*dy;
    int twoDyMinusDx=2*(dy-dx);
    int x,y;

    if(x0>xEnd)
    {
        x=xEnd;
        y=yEnd;
        xEnd=x0;
    }
    else
    {
        x=x0;
        y=y0;
    }
    setPixel(x,y);
    while(x<xEnd)
    {
        x++;
        if(p<0)
            p+=twoDY;
        else
        {
            y++;
            p+=twoDyMinusDx;
        }
        setPixel(x,y);
    }
}
```

![image](https://github.com/Polaris1491319352/Graphics/blob/main/image/work_3.jpg)

_Bresenham画直线的算法主要解决的问题是如何判断下一点的位置：它也是采用递推步进的办法，令每次最大变化方向的坐标步进一个象素，同时另一个方向的坐标依据误差判别式的符号来决定是否也要步进一个象素。总得来说，此算法是利用光栅网格上的点到真实直线上的点的距离（成为误差项），来标定下一个点的位置初始值。利用d的判定函数来判断是否方向要递增。Bresenham算法对任意斜率的直线段具有通用性，对于斜率为整且大于1的直线段，只需要交换x和y之间的规则。对于负斜率，除了一个坐标递减而另一个坐标地政外，其余程序是类似的。_
