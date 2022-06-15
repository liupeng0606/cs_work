# 实验六 二维几何变换实验
## 时间：2022年4月20 日 地点：信息学院2202机房
### 实验内容：教材P161，二维几何变换算法（平移、比例、旋转、对称）   实验目的：验证二维几何变换，熟悉变换矩阵。 

```  
void matrixpreMultiply(Matrix3x3 m1, Matrix3x3 m2) {
    GLint row, col;
    Matrix3x3 tmp;
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            tmp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] *
                m2[1][col] + m1[row][2] * m2[2][col];
        }
    }
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            m2[row][col] = tmp[row][col];
        }
    }
}
//平移
void translate2D(GLfloat tx, GLfloat ty) {
    Matrix3x3 matTransl;
    matrix3x3SetIdentity(matTransl);//设置为单位矩阵
    matTransl[0][2] = tx;
    matTransl[1][2] = ty;
    matrixpreMultiply(matTransl, matComposite);

}
//旋转
void rotate2D(int x, int y, float theta) {
    theta = theta / 180 * PI;
    Matrix3x3 matRot;
    matrix3x3SetIdentity(matRot);
    matRot[0][0] = cos(theta);
    matRot[0][1] = -sin(theta);
    matRot[0][2] = x * (1 - cos(theta)) + y * sin(theta);
    matRot[1][0] = sin(theta);
    matRot[1][1] = cos(theta);
    matRot[1][2] = y * (1 - cos(theta)) - x * sin(theta);
    matrixpreMultiply(matRot, matComposite);
}

//缩放
void scale2D(GLfloat sx, GLfloat sy, int x, int y) {
    Matrix3x3 matScale;
    matrix3x3SetIdentity(matScale);
    matScale[0][0] = sx;
    matScale[0][2] = (1 - sx) * x;
    matScale[1][1] = sy;
    matScale[1][2] = (1 - sy) * y;
    matrixpreMultiply(matScale, matComposite);
}
//复合矩阵
void transformVerts2D() {
    GLfloat tmp;
    for (int i = 0; i < xy.size(); i++) {
        tmp = matComposite[0][0] * xy[i].x + matComposite[0][1] * xy[i].y + matComposite[0][2];
        xy[i].y = matComposite[1][0] * xy[i].x + matComposite[1][1] * xy[i].y + matComposite[1][2];
        xy[i].x = tmp;
    }
    DrawPolygon();
    matrix3x3SetIdentity(matComposite);
}


//绘制多边形
void DrawPolygon() {
    //  glEnable(GL_POLYGON_STIPPLE);
    glPolygonMode(GL_BACK, GL_LINE);//设置反面为线性模式
    glPolygonMode(GL_FRONT, GL_LINE);//设置正面为线性模式
    glClear(GL_COLOR_BUFFER_BIT);//清除窗口显示内容
    glBegin(GL_POLYGON);
    for (unsigned int i = 0; i < xy.size(); i++) {
        glVertex2f(xy[i].x, xy[i].y);
    }
    glEnd();
    glFlush();
}
```  
![image](https://github.com/Polaris1491319352/Graphics/blob/main/image/work6.jpg)  
_实验体会：图形的几何变换是指对图形的几何信息经过平移、比例、旋转、反射和错切等变换后产生新的图形，是图形在方向、尺寸和形状方面的变换。以上变换可用统一的变换矩阵形式来实现，只需利用特定的变换矩阵即可。而复合变换可以通过上面基础变换得到。几何变换均可表示成P’=P*T的形式（规范化齐次矩阵）。_


