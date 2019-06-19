// Exp03View.cpp: CExp03View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exp03.h"
#endif

#include "Exp03Doc.h"
#include "Exp03View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LEFT 1
#define	RIGHT 2
#define	BOTTOM 4
#define TOP	8

int WT;
int WB;
int WR;
int WL;

// CExp03View

IMPLEMENT_DYNCREATE(CExp03View, CView)

BEGIN_MESSAGE_MAP(CExp03View, CView)
        // 标准打印命令
        ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExp03View::OnFilePrintPreview)
        ON_WM_CONTEXTMENU()
        ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CExp03View 构造/析构

CExp03View::CExp03View() noexcept {
    WL = 100;
    WR = 400;
    WB = 100;
    WT = 300;
}

CExp03View::~CExp03View() {
}

BOOL CExp03View::PreCreateWindow(CREATESTRUCT &cs) {
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CView::PreCreateWindow(cs);
}

// CExp03View 绘图

void CExp03View::OnDraw(CDC *pDC) {
    CExp03Doc *pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    //定义三条直线的坐标
    int x11, y11, x21, y21, x12, y12, x22, y22, x13, y13, x23, y23;
    x11 = 50;
    y11 = 150;
    x21 = 450;
    y21 = 250;
    x12 = 150;
    y12 = 150;
    x22 = 350;
    y22 = 240;
    x13 = 50;
    y13 = 400;
    x23 = 500;
    y23 = 350;
    //定义画笔
    CPen PenRed(PS_SOLID, 1, RGB(255, 0, 0)); //定义红色笔
    CPen PenBlue(PS_SOLID, 1, RGB(0, 0, 255)); //定义蓝色笔
    CPen Penwhite(PS_SOLID, 1, RGB(255, 255, 255)); //定义白色笔
    //先画出窗口，用蓝色
    pDC->SelectObject(&PenBlue);
    pDC->Rectangle(WL, WB, WR, WT);
    //先画出三条直线,用红线
    pDC->SelectObject(&PenRed);
    pDC->MoveTo(x11, y11);
    pDC->LineTo(x21, y21);
    pDC->MoveTo(x12, y12);
    pDC->LineTo(x22, y22);
    pDC->MoveTo(x13, y13);
    pDC->LineTo(x23, y23);
    //画出剪裁后的窗口，用蓝色
    pDC->SelectObject(&PenBlue);
    pDC->Rectangle(WL + 350, WB, WR + 350, WT);
    //用蓝线，画出裁剪三条线
    pDC->SelectObject(&PenBlue);
    C_S_Line(pDC, x11, y11, x21, y21);
    C_S_Line(pDC, x12, y12, x22, y22);
    C_S_Line(pDC, x13, y13, x23, y23);
    // TODO: 在此处为本机数据添加绘制代码
}


// CExp03View 打印


void CExp03View::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL CExp03View::OnPreparePrinting(CPrintInfo *pInfo) {
    // 默认准备
    return DoPreparePrinting(pInfo);
}

void CExp03View::OnBeginPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加额外的打印前进行的初始化过程
}

void CExp03View::OnEndPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加打印后进行的清理过程
}

void CExp03View::OnRButtonUp(UINT /* nFlags */, CPoint point) {
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CExp03View::OnContextMenu(CWnd * /* pWnd */, CPoint point) {
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp03View 诊断

#ifdef _DEBUG
void CExp03View::AssertValid() const {
    CView::AssertValid();
}

void CExp03View::Dump(CDumpContext &dc) const {
    CView::Dump(dc);
}

CExp03Doc *CExp03View::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp03Doc)));
    return (CExp03Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp03View 消息处理程序

int CExp03View::C_S_Line(CDC *pDC, int x1, int y1, int x2, int y2) {
    int code1, code2, code, x, y;
    encode(x1, y1, &code1); //(x1,y1)处的编码
    encode(x2, y2, &code2); //(x2,y2)处的编码
    while (code1 != 0 || code2 != 0) //当 code1 不等于 0 或 code2 不等于 0
    {
        if ((code1 & code2) != 0) return 0; //当 code1 与 code2 不等于 0，在同侧；
        code = code1;
        if (code1 == 0) code = code2;
        if ((LEFT & code) != 0) //求交点
        {
            x = WL;
            y = y1 + (y2 - y1) * (WL - x1) / (x2 - x1);
        }
        else if ((RIGHT & code) != 0) {
            x = WR;
            y = y1 + (y2 - y1) * (WR - x1) / (x2 - x1);
        }
        else if ((BOTTOM & code) != 0) {
            y = WB;
            x = x1 + (x2 - x1) * (WB - y1) / (y2 - y1);
        }
        else if ((TOP & code) != 0) {
            y = WT;
            x = x1 + (x2 - x1) * (WT - y1) / (y2 - y1);
        }
        if (code == code1) {
            x1 = x;
            y1 = y;
            encode(x, y, &code1);
        }
        else {
            x2 = x;
            y2 = y;
            encode(x, y, &code2);
        }
    }
    //end while,表示 code1，code2 都为 0，其中的线段为可视部分
    pDC->MoveTo(x1 + 350, y1);
    pDC->LineTo(x2 + 350, y2);
}

void CExp03View::encode(int x, int y, int *code) {
    int c = 0;
    if (x < WL) c = c | LEFT;
    else if (x > WR) c = c | RIGHT;
    if (y < WB) c = c | BOTTOM;
    else if (y > WT) c = c | TOP;
    *code = c;
}
