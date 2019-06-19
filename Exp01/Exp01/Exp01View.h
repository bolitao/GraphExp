﻿// Exp01View.h: CExp01View 类的接口
//

#pragma once


class CExp01View : public CView {
protected: // 仅从序列化创建
    CExp01View() noexcept;
    CPoint m_ptOrigin; // 起始点坐标
    bool m_bDragging; // 拖拽标记	
    HCURSOR m_hCross; // 光标句柄

DECLARE_DYNCREATE(CExp01View)

    // 特性
public:
    CExp01Doc *GetDocument() const;

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
    virtual ~CExp01View();
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
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exp01View.cpp 中的调试版本
inline CExp01Doc* CExp01View::GetDocument() const
   { return reinterpret_cast<CExp01Doc*>(m_pDocument); }
#endif
