﻿// Exp05View.h: CExp05View 类的接口
//

#pragma once


class CExp05View : public CView {
protected: // 仅从序列化创建
    CExp05View() noexcept;
DECLARE_DYNCREATE(CExp05View)

    // 特性
public:
    CExp05Doc *GetDocument() const;
	void OnDrawRose();
	void OnDrawLeaf();

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
    virtual ~CExp05View();
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

#ifndef _DEBUG  // Exp05View.cpp 中的调试版本
inline CExp05Doc* CExp05View::GetDocument() const
   { return reinterpret_cast<CExp05Doc*>(m_pDocument); }
#endif
