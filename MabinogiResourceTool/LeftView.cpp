
// LeftView.cpp : CLeftView 类的实现
//

#include "stdafx.h"
#include "MabinogiResourceTool.h"

#include "MabinogiResourceToolDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CLeftView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CLeftView 构造/析构

CLeftView::CLeftView()
{
	// TODO: 在此处添加构造代码
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT;
	return CTreeView::PreCreateWindow(cs);
}




void CLeftView::OnInitialUpdate()
{
	// 获取和设置系统图标
	SHFILEINFO shFilefo;
	HIMAGELIST hImgList = (HIMAGELIST)SHGetFileInfo(TEXT(""), 0, &shFilefo,sizeof(shFilefo), SHGFI_SYSICONINDEX|SHGFI_SMALLICON);
	GetTreeCtrl().SetImageList(CImageList::FromHandle(hImgList), TVSIL_NORMAL);

	SHGetFileInfo(TEXT("data\\"), FILE_ATTRIBUTE_DIRECTORY , &shFilefo,sizeof(shFilefo), SHGFI_SYSICONINDEX|SHGFI_USEFILEATTRIBUTES );
	m_iFolderCloseIcon = shFilefo.iIcon;

	SHGetFileInfo(TEXT("data\\"), FILE_ATTRIBUTE_DIRECTORY , &shFilefo,sizeof(shFilefo), SHGFI_SYSICONINDEX|SHGFI_USEFILEATTRIBUTES|SHGFI_OPENICON );
	m_iFolderOpenIcon = shFilefo.iIcon;

	CTreeView::OnInitialUpdate();
}


// CLeftView 诊断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMabinogiResourceToolDoc* CLeftView::GetDocument() // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMabinogiResourceToolDoc)));
	return (CMabinogiResourceToolDoc*)m_pDocument;
}
#endif //_DEBUG


void CLeftView::OnUpdate(CView* pSender, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	if (pSender != this)
	{
		GetTreeCtrl().LockWindowUpdate();

		// 注意这里的实现对多次刷新支持不佳
		m_keyMap.clear();
		m_nodeMap.clear();
		GetTreeCtrl().DeleteAllItems();

		HTREEITEM root = GetTreeCtrl().InsertItem( TEXT("Data"), m_iFolderCloseIcon, m_iFolderOpenIcon,TVI_ROOT, TVI_LAST);

		for (auto iter = GetDocument()->m_resContainerMap.begin();iter != GetDocument()->m_resContainerMap.end();++iter)
		{
			CString path = iter->first;
			HTREEITEM hItem = CreateTreeNode(root, path);
		}

		GetTreeCtrl().UnlockWindowUpdate();
	}

}


HTREEITEM CLeftView::CreateTreeNode(HTREEITEM root, LPCTSTR path)
{
	// 获取文件夹图标
	HTREEITEM ret = root;
	CString fullpath = path;
	CString currentPath;
	int curPost = 0;

	static LPCTSTR TOKEN = TEXT("\\");
	CString sep = fullpath.Tokenize(TOKEN, curPost);
	while(!sep.IsEmpty())
	{
		currentPath += sep;
		HTREEITEM fined = m_nodeMap[currentPath];
		if ( fined == NULL )
		{
			// 创建新节点
			ret = GetTreeCtrl().InsertItem(sep , m_iFolderCloseIcon, m_iFolderOpenIcon,ret, TVI_LAST);
			m_nodeMap[currentPath] = ret;
			m_keyMap[ret] = currentPath;
		}
		else
		{
			ret = fined;
		}

		currentPath += TEXT("\\");
		sep = fullpath.Tokenize(TOKEN, curPost);
	}

	return ret;
}


void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	CString key = m_keyMap[pNMTreeView->itemNew.hItem];
	GetDocument()->m_strDir = key;
	GetDocument()->UpdateAllViews(this);

	*pResult = 0;
}
