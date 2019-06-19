// Exp04View.h: CExp04View 类的接口
//

#pragma once

//建立边表结构
typedef struct {
    int num, ymin, ymax;
    float xmin, xmax, dx;
} Edge;


class CExp04View : public CView {
protected: // 仅从序列化创建
    CExp04View() noexcept;
DECLARE_DYNCREATE(CExp04View)

    // 特性
public:
    CExp04Doc *GetDocument() const;
    CPoint spt[7], s_point;
    Edge edge[7], edge1[7], newedge[1];

    // 操作
public:

    // 重写
public:
    virtual void OnDraw(CDC *pDC); // 重写以绘制该视图
    virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo *pInfo);
    virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

    // 实现
public:
    virtual ~CExp04View();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext &dc) const;
#endif

protected:

    // 生成的消息映射函数
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd *pWnd, CPoint point);
DECLARE_MESSAGE_MAP()
public:
    //	afx_msg void OnScanfill();
    afx_msg void OnScanfill();
    afx_msg void OnSeedfill();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exp04View.cpp 中的调试版本
inline CExp04Doc* CExp04View::GetDocument() const
   { return reinterpret_cast<CExp04Doc*>(m_pDocument); }
#endif
