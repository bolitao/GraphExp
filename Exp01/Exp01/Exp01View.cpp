// Exp01View.cpp: CExp01View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exp01.h"
#endif

#include "Exp01Doc.h"
#include "Exp01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExp01View

IMPLEMENT_DYNCREATE(CExp01View, CView)

BEGIN_MESSAGE_MAP(CExp01View, CView)
        // 标准打印命令
        ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExp01View::OnFilePrintPreview)
        ON_WM_CONTEXTMENU()
        ON_WM_RBUTTONUP()
        ON_WM_LBUTTONDOWN()
        ON_WM_MOUSEMOVE()
        ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CExp01View 构造/析构

CExp01View::CExp01View() noexcept {
    // TODO: 在此处添加构造代码
    m_bDragging = false; // 初始化拖拽标记	
    // 获得十字光标句柄
    m_hCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
}

CExp01View::~CExp01View() {
}

BOOL CExp01View::PreCreateWindow(CREATESTRUCT &cs) {
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CView::PreCreateWindow(cs);
}

// CExp01View 绘图

void CExp01View::OnDraw(CDC *pDC) {
    CExp01Doc *pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    int nIndex = pDoc->GetNumLines(); // 取得线段的数量
    // 循环画出每一段线段
    while (nIndex--) // 数组下标从0到nIndex-1
    {
        pDoc->GetLine(nIndex)->DrawLine(pDC);
        // 类CLine的成员函数
    }
    // TODO: 在此处为本机数据添加绘制代码
}


// CExp01View 打印


void CExp01View::OnFilePrintPreview() {
#ifndef SHARED_HANDLERS
    AFXPrintPreview(this);
#endif
}

BOOL CExp01View::OnPreparePrinting(CPrintInfo *pInfo) {
    // 默认准备
    return DoPreparePrinting(pInfo);
}

void CExp01View::OnBeginPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加额外的打印前进行的初始化过程
}

void CExp01View::OnEndPrinting(CDC * /*pDC*/, CPrintInfo * /*pInfo*/) {
    // TODO: 添加打印后进行的清理过程
}

void CExp01View::OnRButtonUp(UINT /* nFlags */, CPoint point) {
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CExp01View::OnContextMenu(CWnd * /* pWnd */, CPoint point) {
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExp01View 诊断

#ifdef _DEBUG
void CExp01View::AssertValid() const {
    CView::AssertValid();
}

void CExp01View::Dump(CDumpContext &dc) const {
    CView::Dump(dc);
}

CExp01Doc *CExp01View::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExp01Doc)));
    return (CExp01Doc*)m_pDocument;
}
#endif //_DEBUG


// CExp01View 消息处理程序


void CExp01View::OnLButtonDown(UINT nFlags, CPoint point) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    SetCapture(); // 捕捉鼠标
    ::SetCursor(m_hCross); // 设置十字光标
    m_ptOrigin = point;
    m_bDragging = TRUE; // 设置拖拽标记	
    // CView::OnLButtonDown(nFlags, point);
}


void CExp01View::OnMouseMove(UINT nFlags, CPoint point) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    // CView::OnMouseMove(nFlags, point);
    if (m_bDragging) {
        CExp01Doc *pDoc = GetDocument(); //获得文档对象指针
        ASSERT_VALID(pDoc); //测试文档对象是否运行有效
        pDoc->AddLine(m_ptOrigin, point); //加入线段到指针数组
        CClientDC dc(this);
        dc.MoveTo(m_ptOrigin);
        dc.LineTo(point); // 绘制线段
        m_ptOrigin = point; // 新的起始点
    }

}


void CExp01View::OnLButtonUp(UINT nFlags, CPoint point) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (m_bDragging) {
        m_bDragging = false; // 清拖拽标记	
        ReleaseCapture(); // 释放鼠标，还原鼠标形状
    }
    // CView::OnLButtonUp(nFlags, point);
}
