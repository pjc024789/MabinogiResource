
// MabinogiResourceToolView.h : CMabinogiResourceToolView 类的接口
//

#pragma once


class CMabinogiResourceToolView : public CListView
{
protected: // 仅从序列化创建
	CMabinogiResourceToolView();
	DECLARE_DYNCREATE(CMabinogiResourceToolView)

// 特性
public:
	CMabinogiResourceToolDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMabinogiResourceToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_bIsAscSort;
	int m_nLastSortColumnIndex;
// 生成的消息映射函数
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnEditOpen();
	afx_msg void OnUpdateEditOpen(CCmdUI *pCmdUI);
	afx_msg void OnEditOpenas();
	afx_msg void OnUpdateEditOpenas(CCmdUI *pCmdUI);
	afx_msg void OnEditUncompress();
	afx_msg void OnUpdateEditUncompress(CCmdUI *pCmdUI);
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // MabinogiResourceToolView.cpp 中的调试版本
inline CMabinogiResourceToolDoc* CMabinogiResourceToolView::GetDocument() const
   { return reinterpret_cast<CMabinogiResourceToolDoc*>(m_pDocument); }
#endif

