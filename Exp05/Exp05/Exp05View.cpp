// Exp05View.cpp: CExp05View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exp05.h"
#endif

#include "Exp05Doc.h"
#include "Exp05View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp05View

IMPLEMENT_DYNCREATE(CExp05View, CView)

BEGIN_MESSAGE_MAP(CExp05View, CView)
        // 标准打印命令
        ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExp05View::OnFilePrintPreview)
        ON_WM_CONTEXTMENU()
        ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CExp05View 构造/析构

CExp05View::CExp05View() noexcept {
    // TODO: 在此处添加构造代码

}

CExp05View::~CExp05View() {
}

BOOL CExp05View::PreCreateWindow(CREATESTRUCT &cs) {
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CView::PreCreateWindow(cs);
}

// CExp05View 绘图

void CExp05View::OnDraw(CDC * /*pDC*/) {
    CExp05Doc *pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
	OnDrawRose();
	OnDrawLeaf();
    // TODO: 在此处为本机数据添加绘制代码
}


// CExp05View 打印


void CExp05View::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL CExp05View::OnPreparePrinting(CPrintInfo *pInfo) {
    // 默认准备
    return DoPreparePrinting(pInfo);
}

void CExp05View::OnBeginPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加额外的打印前进行的初始化过程
}

void CExp05View::OnEndPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加打印后进行的清理过程
}

void CExp05View::OnRButtonUp(UINT /* nFlags */, CPoint point) {
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CExp05View::OnContextMenu(CWnd * /* pWnd */, CPoint point) {
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp05View 诊断

#ifdef _DEBUG
void CExp05View::AssertValid() const {
    CView::AssertValid();
}

void CExp05View::Dump(CDumpContext &dc) const {
    CView::Dump(dc);
}

CExp05Doc *CExp05View::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp05Doc)));
    return (CExp05Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp05View 消息处理程序

void CExp05View::OnDrawRose() {
    CDC *pDC = GetDC();
    int d, k, x1, x2, y1, y2;
    float pi, a, e;
    CPen pen;
    pen.CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0));
    CPen *pOldPen = pDC->SelectObject(&pen);
    pi = 3.1415926;
    d = 80;
    for (a = 0; a <= 2 * pi; a += pi / 360) {
        e = d * (1 + 0.25 * sin(4 * a));
        e = e * (1 + sin(8 * a));
        x1 = int(320 + e * cos(a));
        x2 = int(320 + e * cos(a + pi / 8));
        y1 = int(200 + e * sin(a));
        y2 = int(200 + e * sin(a + pi / 8));
        pDC->MoveTo(x1, y1);
        pDC->LineTo(x2, y2);
    }
}

void CExp05View::OnDrawLeaf() {
    CDC *pDc = GetDC();
    CPen pen;
    pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0xff));
    CPen *pOldPen = pDc->SelectObject(&pen);

    int a, n, cx, cy, gx, gy, flag, k;
    double r, p, th, x, y, pi;
    a = 160;
    n = 2;
    pi = 3.1415926;
    cx = 700;
    cy = 500;
    flag = 0;
    k = 200;
    for (p = 1; p >= 0.2; p -= 0.2) {
        for (th = 0; th <= 2 * pi + 0.1; th += pi / k) {
            r = fabs(a * cos(n * th) * p);
            x = r * cos(th);
            y = r * sin(th);
            gx = int(cx + x);
            gy = int(cy + y);
            if (flag == 0) {
                pDc->MoveTo(gx, gy);
            }
            flag = 1;
            pDc->LineTo(gx, gy);
        }
        flag = 0;
    }
    pDc->SelectObject(pOldPen);
}
