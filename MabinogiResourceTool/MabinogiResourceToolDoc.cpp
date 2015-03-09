
// MabinogiResourceToolDoc.cpp : CMabinogiResourceToolDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MabinogiResourceTool.h"
#endif

#include "MabinogiResourceToolDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMabinogiResourceToolDoc

IMPLEMENT_DYNCREATE(CMabinogiResourceToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMabinogiResourceToolDoc, CDocument)
END_MESSAGE_MAP()


// CMabinogiResourceToolDoc 构造/析构

CMabinogiResourceToolDoc::CMabinogiResourceToolDoc()
{
	m_pResourceSet = NULL;
}

CMabinogiResourceToolDoc::~CMabinogiResourceToolDoc()
{
}

BOOL CMabinogiResourceToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	return TRUE;
}




// CMabinogiResourceToolDoc 序列化

void CMabinogiResourceToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		m_pResourceSet = IResourceSet::CreateResourceSetFromFile(ar.GetFile()->GetFilePath());
		IndexResources();
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMabinogiResourceToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMabinogiResourceToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMabinogiResourceToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMabinogiResourceToolDoc 诊断

#ifdef _DEBUG
void CMabinogiResourceToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMabinogiResourceToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMabinogiResourceToolDoc 命令
void CMabinogiResourceToolDoc::DeleteContents()
{
	if (m_pResourceSet != NULL)
	{
		m_pResourceSet->Release();
		m_pResourceSet = NULL;
	}
	CDocument::DeleteContents();
}

void CMabinogiResourceToolDoc::IndexResources(void)
{
	m_resContainerMap.clear();
	for (size_t i = 0;i < m_pResourceSet->GetResourceCount(); i++)
	{
		auto hRes = shared_ptr<ResourceHandle>(new ResourceHandle(m_pResourceSet->GetResource(i)));
		m_resContainerMap.insert(ResourceContainerPair(hRes->path, hRes));
	}
}
