
// LeftView.h : CLeftView 类的接口
//


#pragma once

#include <map>

using namespace std;

typedef map<HTREEITEM, CString> TreeKeyMap;
typedef map<CString, HTREEITEM> TreeNodeMap;

class CMabinogiResourceToolDoc;

class CLeftView : public CTreeView
{
protected: // 仅从序列化创建
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// 特性
public:
	CMabinogiResourceToolDoc* GetDocument();

// 操作
public:

// 重写
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	TreeKeyMap m_keyMap;
	TreeNodeMap m_nodeMap;

	int m_iFolderCloseIcon;
	int m_iFolderOpenIcon;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	HTREEITEM CreateTreeNode(HTREEITEM root, LPCTSTR path);
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // LeftView.cpp 中的调试版本
inline CMabinogiResourceToolDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CMabinogiResourceToolDoc*>(m_pDocument); }
#endif

