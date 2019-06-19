// Exp02View.cpp: CExp02View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exp02.h"
#endif

#include "Exp02Doc.h"
#include "Exp02View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp02View

IMPLEMENT_DYNCREATE(CExp02View, CView)

BEGIN_MESSAGE_MAP(CExp02View, CView)
        // 标准打印命令
        ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExp02View::OnFilePrintPreview)
        ON_WM_CONTEXTMENU()
        ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CExp02View 构造/析构

CExp02View::CExp02View() noexcept {
    // TODO: 在此处添加构造代码

}

CExp02View::~CExp02View() {
}

BOOL CExp02View::PreCreateWindow(CREATESTRUCT &cs) {
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CView::PreCreateWindow(cs);
}

// CExp02View 绘图

void CExp02View::OnDraw(CDC *pDC) {
    CExp02Doc *pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    MidpointEllise(pDC, 430, 220, 100, 40, RGB(255, 0, 0));
    MidpointEllise(pDC, 430, 220, 40, 100, RGB(255, 0, 0));
    PositiveNegativeParabola(pDC, -0.7, -20, 3, RGB(255, 0, 0));
    PositiveNegativeParabola(pDC, -0.1, -20, 3, RGB(255, 0, 0));
    // TODO: 在此处为本机数据添加绘制代码
}


// CExp02View 打印


void CExp02View::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL CExp02View::OnPreparePrinting(CPrintInfo *pInfo) {
    // 默认准备
    return DoPreparePrinting(pInfo);
}

void CExp02View::OnBeginPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加额外的打印前进行的初始化过程
}

void CExp02View::OnEndPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加打印后进行的清理过程
}

void CExp02View::OnRButtonUp(UINT /* nFlags */, CPoint point) {
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CExp02View::OnContextMenu(CWnd * /* pWnd */, CPoint point) {
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp02View 诊断

#ifdef _DEBUG
void CExp02View::AssertValid() const {
    CView::AssertValid();
}

void CExp02View::Dump(CDumpContext &dc) const {
    CView::Dump(dc);
}

CExp02Doc *CExp02View::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp02Doc)));
    return (CExp02Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp02View 消息处理程序


void CExp02View::OnDdaline() {
    CDC *pDC = GetDC(); // 获得设备指针

    //CDC *pDC=GetDocument();

    int x0 = 100, y0 = 100, x1 = 300, y1 = 200, c = RGB(255, 0, 0); // 定义直线两端点和直线颜色（红色）
    float x, y, i;
    float dx, dy, k;
    dx = (float)(x1 - x0);
    dy = (float)(y1 - y0);
    k = dy / dx;
    y = y0;
    x = x0;
    if (abs(k) < 1) {
        for (; x <= x1; x++) {
            pDC->SetPixel(x, int(y + 0.5), c);
            y = y + k;
        }
    }
    if (abs(k) >= 1) {
        for (; y <= y1; y++) {
            pDC->SetPixel(int(x + 0.5), y, c);
            x = x + 1 / k;
        }
    }
    ReleaseDC(pDC); //释放设备指针
}

void CExp02View::MidpointEllise(CDC *pDC, int x0, int y0, int a, int b, COLORREF color) {
    int x, y;
    float d1, d2;
    x = 0;
    y = b;
    d1 = b * b + a * a * (-b + 0.25);
    pDC->SetPixel(x + x0, y + y0, color);
    while (b * b * (x + 1) < a * a * (y - 0.5)) {
        if (d1 < 0) {
            d1 += b * b * (2 * x + 3);
            x++;
        }
        else {
            d1 += (b * b * (2 * x + 3) + a * a * (-2 * y + 2));
            x++;
            y--;
        }
        pDC->SetPixel(x0 + x, y0 + y, color);
        pDC->SetPixel(x0 + x, y0 - y, color);
        pDC->SetPixel(x0 - x, y0 + y, color);
        pDC->SetPixel(x0 - x, y0 - y, color);
    } //  上半部分
    d2 = (b * (x + 0.5)) * (b * (x + 0.5)) + (a * (y - 1)) * (a * (y - 1)) - (a * b) * (a * b);
    while (y > 0) {
        if (d2 < 0) {
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
            y--;
        }
        else {
            d2 += a * a * (-2 * y + 3);
            y--;
        }
        pDC->SetPixel(x0 + x, y0 + y, color);
        pDC->SetPixel(x0 + x, y0 - y, color);
        pDC->SetPixel(x0 - x, y0 + y, color);
        pDC->SetPixel(x0 - x, y0 - y, color);
    } //下半部分
}

void CExp02View::PositiveNegativeParabola(CDC *pDC, float a, float b, float c, int color) {
    int x, y, d;
    x = 0;
    y = 0;
    pDC->SetPixel(x + 450 + b, y + 225 + c, color);
    if (a > 0) {
        y = 1;
        pDC->SetPixel(x + 450 + b, y + 225 + c, color);
        d = 1;
        while (y <= 30) {
            if (d >= 0) {
                d = d - 2 * a * x - a;
                x++;
            }
            else {
                d = d + 1;
                y++;
            }
            pDC->SetPixel(-x + 450 + b, y + 225 + c, color);
            pDC->SetPixel(x + 450 + b, y + 225 + c, color);
        }
    }
    else if (a < 0) {
        x = 1;
        pDC->SetPixel(x + 450 + b, y + 225 + c, color);
        d = 1;
        while (y >= -35) {
            if (d >= 0) {
                d = d - 1;
                y--;
            }
            else {
                d = d - 2 * a * x - a;
                x++;
            }
            pDC->SetPixel(-x + 450 + b, y + 225 + c, color);
            pDC->SetPixel(x + 450 + b, y + 225 + c, color);
        }
    }
    else {
        printf("this is not a Parabola!\n");
    }
}
