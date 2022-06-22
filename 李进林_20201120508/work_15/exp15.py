import cv2
import numpy as np
import time

XLine = 1000
YLine = 700
img = np.zeros((YLine, XLine, 3), np.uint8)  # 生成背景
pts = []
z_buffer = np.zeros((XLine, YLine), np.uint32)
z_buffer += 100000  # 无穷大

# 为了满足需求而设置的值
count = 0


def zfunc(x, y):
    return x + y


def draw_func(event, x, y, flags, param):
    global pts
    if event == cv2.EVENT_LBUTTONDOWN:
        print('(x:', x, ',y:', y, ')')
        str1 = '(x:' + str(x) + ',y:' + str(y) + ')'
        # cv2.putText(img,str1 , (x, y), cv2.FONT_HERSHEY_PLAIN,1.0, (0, 0, 255), thickness=1)
        cv2.circle(img, (x, y), 1, (0, 255, 0), thickness=1)
        pts.append([x, y])


# 活性边表与新边表中的节点
class Node:
    def __init__(self, xmin, ymax, k1, next=None):
        self.x = xmin  # 也就是x的初始值
        self.ymax = ymax
        self.k1 = k1  # 也就是δx
        self.next = next

    def print(self):
        t = self
        while t != None:
            print(t.x, t.ymax, t.k1, end="-->")
            t = t.next
        print()


def FillPoly(fpts, color):
    global z_buffer, count
    count += 1
    # cv2.fillPoly(img,fpts,color)
    Ymin, Ymax = 1000000, 0
    for pt in fpts:
        if Ymin > pt[1]:
            Ymin = pt[1]
        if Ymax < pt[1]:
            Ymax = pt[1]

    # 构造新边表
    NET = [x for x in range(Ymax + 1)]
    for i in range(len(fpts)):
        # 后面一个点的序号
        j = i + 1 if i < len(fpts) - 1 else 0
        if fpts[i][1] > fpts[j][1]:
            ymax, ymin = fpts[i][1], fpts[j][1]
            xmin = fpts[j][0]
        else:
            ymin, ymax = fpts[i][1], fpts[j][1]
            xmin = fpts[i][0]
        # 与x轴平行,跳过该边
        if fpts[i][1] == fpts[j][1]:
            continue

        if fpts[i][0] == fpts[j][0]:
            k1 = 0
        else:
            k1 = (fpts[i][0] - fpts[j][0]) / (fpts[i][1] - fpts[j][1])

        if type(NET[ymin]) != type(66):
            t = NET[ymin]
            while t.next != None:
                t = t.next
            t.next = Node(xmin, ymax, k1)
        else:
            NET[ymin] = Node(xmin, ymax, k1)
    for i, x in enumerate(NET):
        if type(x) != type(66):
            print(i)
            x.print()

    AET = Node(0, 0, 0)
    print("YY")
    for y in range(Ymin, Ymax + 1):
        # print(y)
        # 慢慢画
        cv2.waitKey(3)
        cv2.imshow('src', img)
        # 加入新边
        if type(NET[y]) != type(66):
            t = AET
            while t.next:
                t = t.next
            t.next = NET[y]
        # 填充颜色
        # 按x排序
        xs = []
        t = AET
        while t.next:
            t = t.next
            xs.append(t.x)
        xs = sorted(xs)
        for i in range(1, len(xs), 2):
            for x in range(int(xs[i - 1]), int(xs[i])):
                # z=zfunc(x,y)  这里是zbuffer消隐操作
                z = count
                if z == 3 and z_buffer[x, y] == 1:  # 这里是为了交作业 ヽ(ﾟ▽ﾟ)ノ
                    z_buffer[x, y] = z
                    cv2.circle(img, (x, y), 1, color, thickness=1)
                elif z < z_buffer[x, y]:
                    z_buffer[x, y] = z
                    cv2.circle(img, (x, y), 1, color, thickness=1)
        # 删除并更新边
        t = AET
        while t.next:
            ct = t.next
            ct.x += ct.k1
            if ct.ymax == y:
                t.next = ct.next
            t = t.next
            if t == None:
                break


cv2.namedWindow('src')
cv2.setMouseCallback('src', draw_func)

while (1):
    cv2.imshow('src', img)
    code = cv2.waitKey(100)
    if code == ord('q'):  # 按下q退出
        break
    elif code == ord('e'):  # 按下该键表示画完一个多边形
        tmp = np.array(pts, np.int32)
        tmp = [tmp.reshape((-1, 1, 2))]
        fpts = pts
        pts = []
        # cv2.polylines(img,tmp,True,(255,255,255))
    # 按下 r,g,b 填充多边形为相应的颜色
    elif code == ord('r'):
        FillPoly(fpts, (0, 0, 255))
    elif code == ord('y'):
        FillPoly(fpts, (0, 255, 255))
    elif code == ord('b'):
        FillPoly(fpts, (255, 0, 0))
cv2.destroyAllWindows()