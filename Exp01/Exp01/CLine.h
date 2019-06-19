#pragma once
#include <afx.h>

class CLine :
    public CObject {
private:
    // 定义成员变量，表示一条直线起点和终点的坐标
    CPoint m_pt1;
    CPoint m_pt2;
public:
    CLine(CPoint pt1, CPoint pt2); // 构造函数
    void DrawLine(CDC *pDC); // 绘制线段
};
