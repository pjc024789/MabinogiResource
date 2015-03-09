
// MabinogiResourceToolView.cpp : CMabinogiResourceToolView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MabinogiResourceTool.h"
#endif

#include "MabinogiResourceToolDoc.h"
#include "MabinogiResourceToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <commoncontrols.h>
// CMabinogiResourceToolView

IMPLEMENT_DYNCREATE(CMabinogiResourceToolView, CListView)

BEGIN_MESSAGE_MAP(CMabinogiResourceToolView, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_OPEN, &CMabinogiResourceToolView::OnEditOpen)
	ON_UPDATE_COMMAND_UI(ID_EDIT_OPEN, &CMabinogiResourceToolView::OnUpdateEditOpen)
	ON_COMMAND(ID_EDIT_OPENAS, &CMabinogiResourceToolView::OnEditOpenas)
	ON_UPDATE_COMMAND_UI(ID_EDIT_OPENAS, &CMabinogiResourceToolView::OnUpdateEditOpenas)
	ON_COMMAND(ID_EDIT_UNCOMPRESS, &CMabinogiResourceToolView::OnEditUncompress)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNCOMPRESS, &CMabinogiResourceToolView::OnUpdateEditUncompress)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CMabinogiResourceToolView::OnLvnColumnclick)
END_MESSAGE_MAP()

// CMabinogiResourceToolView 构造/析构

CMabinogiResourceToolView::CMabinogiResourceToolView()
{
	m_bIsAscSort = true;
	m_nLastSortColumnIndex = -1;
}

CMabinogiResourceToolView::~CMabinogiResourceToolView()
{
}

BOOL CMabinogiResourceToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= LVS_REPORT | LVS_SHAREIMAGELISTS;
	return CListView::PreCreateWindow(cs);
}

void CMabinogiResourceToolView::OnInitialUpdate()
{
	int nIndex = 0;
	GetListCtrl().InsertColumn(nIndex++, TEXT("文件名"), LVCFMT_LEFT, 120);
	GetListCtrl().InsertColumn(nIndex++, TEXT("版本"), LVCFMT_LEFT, 60);
	GetListCtrl().InsertColumn(nIndex++, TEXT("类型说明"), LVCFMT_LEFT, 150);
	GetListCtrl().InsertColumn(nIndex++, TEXT("大小"), LVCFMT_LEFT, 80);
	GetListCtrl().InsertColumn(nIndex++, TEXT("压缩后大小"), LVCFMT_LEFT, 80);
	GetListCtrl().InsertColumn(nIndex++, TEXT("文件时间1"), LVCFMT_LEFT, 140);
	GetListCtrl().InsertColumn(nIndex++, TEXT("文件时间2"), LVCFMT_LEFT, 140);
	GetListCtrl().InsertColumn(nIndex++, TEXT("文件时间3"), LVCFMT_LEFT, 140);

	HIMAGELIST hImgList;// = (HIMAGELIST)SHGetFileInfo(TEXT(""), 0, &shFilefo,sizeof(shFilefo), SHGFI_SYSICONINDEX|SHGFI_LARGEICON);
	SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void**) &hImgList);
	GetListCtrl().SetImageList(CImageList::FromHandle(hImgList), TVSIL_NORMAL);

	SHGetImageList(SHIL_SMALL, IID_IImageList, (void**) &hImgList);
	GetListCtrl().SetImageList(CImageList::FromHandle(hImgList), LVSIL_SMALL);


	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_HEADERDRAGDROP);

	LVTILEVIEWINFO lvtvi = { sizeof(LVTILEVIEWINFO), LVTVIM_COLUMNS };

	lvtvi.cLines = 2;
	lvtvi.dwFlags = LVTVIF_AUTOSIZE;
	GetListCtrl().SetTileViewInfo ( &lvtvi );

	CListView::OnInitialUpdate();


}

void CMabinogiResourceToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMabinogiResourceToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMabinogiResourceToolView 诊断

#ifdef _DEBUG
void CMabinogiResourceToolView::AssertValid() const
{
	CListView::AssertValid();
}

void CMabinogiResourceToolView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMabinogiResourceToolDoc* CMabinogiResourceToolView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMabinogiResourceToolDoc)));
	return (CMabinogiResourceToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMabinogiResourceToolView 消息处理程序
void CMabinogiResourceToolView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: 添加代码以响应用户对窗口视图样式的更改	
	CListView::OnStyleChanged(nStyleType,lpStyleStruct);	
}

CString GetFileSizeDesc( unsigned long size )
{
	CString desc;

	if (size < 1024)
	{
		desc.Format( TEXT("%d 字节"), size);
	}
	else if ( size < 1024 * 1024)
	{
		desc.Format( TEXT("%d KB"), (int)(size / 1024) );
	}
	else if ( size < 1024 * 1024 * 1024)
	{
		desc.Format( TEXT("%d MB"), (int)(size / 1024 / 1024) );
	}
	else
	{
		desc.Format( TEXT("%d GB"), (int)(size / 1024 / 1024 / 1024) );
	}

	return desc;
}

void CMabinogiResourceToolView::OnUpdate(CView* pSender, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	if (pSender != this)
	{

		GetListCtrl().LockWindowUpdate();

		SHFILEINFO shFilefo;

		GetListCtrl().DeleteAllItems();
		int index = 0;
		pair<ResourceContainerMap::const_iterator, ResourceContainerMap::const_iterator> valueRange = 
			GetDocument()->m_resContainerMap.equal_range(GetDocument()->m_strDir);
		for (auto iter = valueRange.first; iter!=valueRange.second; ++iter)
		{
			//ZeroMemory(&shFilefo, sizeof(SHFILEINFO));
			SHGetFileInfo( iter->second->name , FILE_ATTRIBUTE_NORMAL , 
				&shFilefo,sizeof(shFilefo), SHGFI_SYSICONINDEX|SHGFI_USEFILEATTRIBUTES );

			int row = GetListCtrl().InsertItem(index++, iter->second->name, shFilefo.iIcon);
			GetListCtrl().SetItemData(row, (DWORD_PTR)iter->second.get());

			int col = 1;
			CString strText;

			// 版本
			strText.Format(TEXT("%d"), iter->second->pResource->GetVersion());
			GetListCtrl().SetItemText(row, col++, strText);

			// 类型说明
			SHFILEINFO shFilefo;
			SHGetFileInfo( iter->second->pResource->GetName() ,FILE_ATTRIBUTE_NORMAL , &shFilefo, sizeof(shFilefo),
				SHGFI_TYPENAME|SHGFI_USEFILEATTRIBUTES );


			GetListCtrl().SetItemText(row, col++, shFilefo.szTypeName);

			// 压缩前大小
			GetListCtrl().SetItemText(row, col++, GetFileSizeDesc(iter->second->pResource->GetDecompressedSize()) );

			// 压缩后大小
			GetListCtrl().SetItemText(row, col++, GetFileSizeDesc(iter->second->pResource->GetCompressedSize()) );


			CTime time;
			// 文件时间1
			GetListCtrl().SetItemText(row, col++, CTime(iter->second->pResource->GetCreationTime()).Format(TEXT("%Y/%m/%d %H:%M:%S")) );

			// 文件时间2
			GetListCtrl().SetItemText(row, col++, CTime(iter->second->pResource->GetLastAccessTime()).Format(TEXT("%Y/%m/%d %H:%M:%S")) );

			// 文件时间3
			GetListCtrl().SetItemText(row, col++, CTime(iter->second->pResource->GetLastWriteTime()).Format(TEXT("%Y/%m/%d %H:%M:%S")) );


			UINT aCols[] = {3,2};
			LVTILEINFO lvti = { sizeof(LVTILEINFO), row, 2, aCols };

			GetListCtrl().SetTileInfo ( &lvti );
		}


		GetListCtrl().UnlockWindowUpdate();
	}
}


void CMabinogiResourceToolView::OnEditOpen()
{
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
	if (pos)
	{
		int index = GetListCtrl().GetNextSelectedItem(pos);
		ResourceHandle * pRes = (ResourceHandle*)GetListCtrl().GetItemData(index);
		
	}
}


void CMabinogiResourceToolView::OnUpdateEditOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount() == 1);
}


void CMabinogiResourceToolView::OnEditOpenas()
{
	// TODO: 在此添加命令处理程序代码
}


void CMabinogiResourceToolView::OnUpdateEditOpenas(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount() == 1);
}


void CMabinogiResourceToolView::OnEditUncompress()
{
	AfxMessageBox(L"test");
}


void CMabinogiResourceToolView::OnUpdateEditUncompress(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetListCtrl().GetSelectedCount() >= 1);
}

struct SCompareData
{
	bool bIsAscSort;
	int nColumnIndex;
	CListCtrl* pList;
};

int CALLBACK ListViewCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	SCompareData * pCd = (SCompareData*)lParamSort;
	ResourceHandle * pRes1 = (ResourceHandle *)pCd->pList->GetItemData(lParam1);
	ResourceHandle * pRes2 = (ResourceHandle *)pCd->pList->GetItemData(lParam2);

	int result = 0;
	switch (pCd->nColumnIndex)
	{
	case 1: // 版本
		result = pRes1->pResource->GetVersion() - pRes2->pResource->GetVersion();
		break;
	case 3:
		result = pRes1->pResource->GetDecompressedSize() - pRes2->pResource->GetDecompressedSize();
		break;
	case 4:
		result = pRes1->pResource->GetCompressedSize() - pRes2->pResource->GetCompressedSize();
		break;
	default:
		result = pCd->pList->GetItemText((int)lParam1, pCd->nColumnIndex).CompareNoCase(
			pCd->pList->GetItemText((int)lParam2, pCd->nColumnIndex));
	}


	return result * (pCd->bIsAscSort ? 1 : -1);
}
void CMabinogiResourceToolView::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// 如果点击的是之前相同的列，则转换排序方式
	if (m_nLastSortColumnIndex == pNMLV->iSubItem)
	{
		m_bIsAscSort = !m_bIsAscSort;
	}
	
	m_nLastSortColumnIndex = pNMLV->iSubItem;

	// 点击标题栏排序所有项目
	SCompareData cd;
	cd.bIsAscSort = m_bIsAscSort;
	cd.nColumnIndex = pNMLV->iSubItem;
	cd.pList = &GetListCtrl();
	GetListCtrl().SortItemsEx(ListViewCompareFunc, (DWORD_PTR)&cd);
	*pResult = 0;
}
