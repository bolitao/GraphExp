// Exp01Doc.cpp: CExp01Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Exp01.h"
#endif

#include "Exp01Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CExp01Doc

IMPLEMENT_DYNCREATE(CExp01Doc, CDocument)

BEGIN_MESSAGE_MAP(CExp01Doc, CDocument)
END_MESSAGE_MAP()


// CExp01Doc 构造/析构

CExp01Doc::CExp01Doc() noexcept {
    // TODO: 在此添加一次性构造代码

}

CExp01Doc::~CExp01Doc() {
}

BOOL CExp01Doc::OnNewDocument() {
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: 在此添加重新初始化代码
    // (SDI 文档将重用该文档)

    return TRUE;
}


// CExp01Doc 序列化

void CExp01Doc::Serialize(CArchive &ar) {
    if (ar.IsStoring()) {
        // TODO:  在此添加存储代码
    }
    else {
        // TODO:  在此添加加载代码
    }
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CExp01Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CExp01Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CExp01Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CExp01Doc 诊断

#ifdef _DEBUG
void CExp01Doc::AssertValid() const {
    CDocument::AssertValid();
}

void CExp01Doc::Dump(CDumpContext &dc) const {
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CExp01Doc 命令
void CExp01Doc::AddLine(CPoint pt1, CPoint pt2) {
    CLine *pLine = new CLine(pt1, pt2);
    // int *p = new int[5];
    //新建一条线段对象
    m_LineArray.Add(pLine); //将该线段加到动态数组
}

CLine *CExp01Doc::GetLine(int nIndex) {
    if (nIndex < 0 || nIndex > m_LineArray.GetUpperBound())
        //判断是否越界
        return NULL;
    return m_LineArray.GetAt(nIndex);
}

int CExp01Doc::GetNumLines() {
    return m_LineArray.GetSize();
    //返回线段的数量
}
