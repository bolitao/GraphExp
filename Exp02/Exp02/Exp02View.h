// Exp02View.h: CExp02View 类的接口
//

#pragma once


class CExp02View : public CView {
protected: // 仅从序列化创建
    CExp02View() noexcept;
DECLARE_DYNCREATE(CExp02View)

    // 特性
public:
    CExp02Doc *GetDocument() const;
    void OnDdaline();
    void MidpointEllise(CDC *pDC, int x0, int y0, int a, int b, COLORREF color);
    void PositiveNegativeParabola(CDC *pDC, float a, float b, float c, int color);
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
    virtual ~CExp02View();
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
};

#ifndef _DEBUG  // Exp02View.cpp 中的调试版本
inline CExp02Doc* CExp02View::GetDocument() const
   { return reinterpret_cast<CExp02Doc*>(m_pDocument); }
#endif
