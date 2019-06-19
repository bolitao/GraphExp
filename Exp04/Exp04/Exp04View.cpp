// Exp04View.cpp: CExp04View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exp04.h"
#endif

#include "Exp04Doc.h"
#include "Exp04View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp04View

IMPLEMENT_DYNCREATE(CExp04View, CView)

BEGIN_MESSAGE_MAP(CExp04View, CView)
        // 标准打印命令
        ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExp04View::OnFilePrintPreview)
        ON_WM_CONTEXTMENU()
        ON_WM_RBUTTONUP()
        //	ON_COMMAND(ID_32772, &CExp04View::OnScanfill)
        ON_COMMAND(ID_32771, &CExp04View::OnScanfill)
        ON_COMMAND(ID_32772, &CExp04View::OnSeedfill)
        ON_WM_LBUTTONDBLCLK()
        ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CExp04View 构造/析构

CExp04View::CExp04View() noexcept {
    // TODO: 在此处添加构造代码

}

CExp04View::~CExp04View() {
}

BOOL CExp04View::PreCreateWindow(CREATESTRUCT &cs) {
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CView::PreCreateWindow(cs);
}

// CExp04View 绘图

void CExp04View::OnDraw(CDC *pDC) {
    CExp04Doc *pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    CPen newpen(PS_SOLID, 1, RGB(255, 0, 0));
    CPen *old = pDC->SelectObject(&newpen);
    LPCWSTR text1 = TEXT("双击鼠标左键, 出现需填充的多边形, 点击相关功能菜单实现区域填充");
    pDC->TextOut(20, 20, text1, lstrlen(text1));
    LPCWSTR text2 = TEXT("进行种子填充, 需用鼠标右键, 单击多边形内一点, 作为开始填充的种子点");
    pDC->TextOut(20, 50, text2, lstrlen(text2));
    pDC->SelectObject(old);
    // TODO: 在此处为本机数据添加绘制代码
}


// CExp04View 打印


void CExp04View::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL CExp04View::OnPreparePrinting(CPrintInfo *pInfo) {
    // 默认准备
    return DoPreparePrinting(pInfo);
}

void CExp04View::OnBeginPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加额外的打印前进行的初始化过程
}

void CExp04View::OnEndPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加打印后进行的清理过程
}

void CExp04View::OnRButtonUp(UINT /* nFlags */, CPoint point) {
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CExp04View::OnContextMenu(CWnd * /* pWnd */, CPoint point) {
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp04View 诊断

#ifdef _DEBUG
void CExp04View::AssertValid() const {
    CView::AssertValid();
}

void CExp04View::Dump(CDumpContext &dc) const {
    CView::Dump(dc);
}

CExp04Doc *CExp04View::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp04Doc)));
    return (CExp04Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp04View 消息处理程序


void CExp04View::OnScanfill() {
    // TODO: 在此添加命令处理程序代码
    CDC *pDC = GetDC();
    CPen newpen(PS_SOLID, 1, RGB(0, 255, 0));
    CPen *old = pDC->SelectObject(&newpen);
    int j, k, s = 0;
    int p[5]; //每根扫描线交点
    int pmin, pmax;
    for (int i = 0; i < 6; i++) //建立边表
    {
        edge[i].dx = (float)(spt[i + 1].x - spt[i].
            x) / (spt[i + 1].y - spt[i].y);
        if (spt[i].y <= spt[i + 1].y) {
            edge[i].num = i;
            edge[i].ymin = spt[i].y;
            edge[i].ymax = spt[i + 1].y;
            edge[i].xmin = (float)spt[i].x;
            edge[i].xmax = (float)spt[i + 1].x;
            pmax = spt[i + 1].y;
            pmin = spt[i].y;

        }
        else {
            edge[i].num = i;
            edge[i].ymin = spt[i + 1].y;
            edge[i].ymax = spt[i].y;
            edge[i].xmax = (float)spt[i].x;
            edge[i].xmin = (float)spt[i + 1].x;
            pmax = spt[i].y;
            pmin = spt[i + 1].y;
        }
    }
    for (int r = 1; r < 6; r++) //排序edge(yUpper，xIntersect)
    {
        for (int q = 0; q < 6 - r; q++) {
            if (edge[q].ymin < edge[q + 1].ymin) {
                newedge[0] = edge[q];
                edge[q] = edge[q + 1];
                edge[q + 1] = newedge[0];
            }
        }
    }
    for (int scan = pmax - 1; scan > pmin + 1; scan--) {
        int b = 0;
        k = s;
        for (j = k; j < 6; j++) {
            if ((scan > edge[j].ymin) && (scan <= edge[j].ymax)) //判断与线段相交
            {
                if (scan == edge[j].ymax) {
                    if (spt[edge[j].num + 1].y < edge[j].ymax) {
                        b++;
                        p[b] = (int)edge[j].xmax;
                    }
                    if (spt[edge[j].num - 1].y < edge[j].ymax) {
                        b++;
                        p[b] = (int)edge[j].xmax;
                    }
                }
                if ((scan > edge[j].ymin) && (scan < edge[j].ymax)) {
                    b++;
                    p[b] = (int)(edge[j].xmax + edge[j].dx * (scan - edge[j].
                        ymax));
                }
            }
            //pDC->LineTo(spt[edge[0].num].x,spt[edge[0].num].y);
            if (scan <= edge[j].ymin) //
                s = j;
        }
        if (b > 1) {
            for (int u = 1; u < b; u++) {
                pDC->MoveTo(p[u] + 3, scan);
                u++;
                pDC->LineTo(p[u], scan);
            }
        }
    }
    pDC->SelectObject(old);
}


void CExp04View::OnSeedfill() {
    // TODO: 在此添加命令处理程序代码
    CWindowDC dc(this);
    int fill = RGB(0, 255, 0);
    int boundary = RGB(255, 0, 0);
    CPoint pt = s_point;
    int x, y, p0, pmin, pmax;
    //求多边形的最大最小值
    for (int m = 1; m < 7; m++) {
        for (int n = 0; n < 7 - m; n++) {
            if (spt[n].y < spt[n + 1].y) {
                p0 = spt[n].y;
                spt[n] = spt[n + 1];
                spt[n + 1] = p0;
            }
        }
    }
    pmax = spt[0].y, pmin = spt[6].y;

    x = s_point.x;
    y = s_point.y;
    for (; y < pmax + 1; y++) {
        int current = dc.GetPixel(x, y);
        while ((current != boundary) && (current != fill)) {
            dc.SetPixel(x, y, fill);
            x++;
            current = dc.GetPixel(x, y);
        }
        x = s_point.x;
        x--;
        current = dc.GetPixel(x, y);
        while ((current != boundary) && (current != fill)) {
            dc.SetPixel(x, y, fill);
            x--;
            current = dc.GetPixel(x, y);
        }
        x = s_point.x;
    }
    x = s_point.x;
    y = s_point.y - 1;
    for (; y > pmin - 2; y--) {
        int current = dc.GetPixel(x, y);
        while ((current != boundary) && (current != fill)) {
            dc.SetPixel(x, y, fill);
            x++;
            current = dc.GetPixel(x, y);
        }
        x = s_point.x;
        x--;
        current = dc.GetPixel(x, y);
        while ((current != boundary) && (current != fill)) {
            dc.SetPixel(x, y, fill);
            x--;
            current = dc.GetPixel(x, y);
        }
        x = s_point.x;
    }
}


void CExp04View::OnLButtonDblClk(UINT nFlags, CPoint point) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    RedrawWindow();
    CDC *pDC = GetDC();
    CPen newpen(PS_SOLID, 1, RGB(255, 0, 0));
    CPen *old = pDC->SelectObject(&newpen);
    spt[0] = CPoint(100, 100); //绘制多边形区域
    spt[1] = CPoint(300, 100);
    spt[2] = CPoint(250, 250);
    spt[3] = CPoint(100, 250);
    spt[4] = CPoint(150, 200);
    spt[5] = CPoint(90, 180);
    spt[6] = CPoint(150, 150);
    spt[7] = CPoint(100, 100);
    pDC->Polyline(spt, 8);
    pDC->SelectObject(old);
    ReleaseDC(pDC);
    CView::OnLButtonDblClk(nFlags, point);
}


void CExp04View::OnRButtonDown(UINT nFlags, CPoint point) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    s_point = point; //选择种子点
    CView::OnRButtonDown(nFlags, point);
}
