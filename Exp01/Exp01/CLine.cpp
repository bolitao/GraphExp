#include "pch.h"
#include "CLine.h"

CLine::CLine(CPoint pt1, CPoint pt2) {
    m_pt1 = pt1;
    m_pt2 = pt2;
}

void CLine::DrawLine(CDC *pDC) {
    pDC->MoveTo(m_pt1);
    pDC->LineTo(m_pt2);
}
