
// MabinogiResourceToolDoc.h : CMabinogiResourceToolDoc 类的接口
//


#pragma once

#include <map>
#include <vector>
#include <memory>
using namespace std;
using namespace std::tr1;

#include "../MabinogiResource/IResourceSet.h"
#pragma comment(lib, "MabinogiResource")


class ResourceHandle
{
public:
	ResourceHandle(IResource * pRes)
	{
		name = pRes->GetName();
		int lastSep = name.ReverseFind('\\');
		if (lastSep >= 0)
		{
			path = name.Mid(0, lastSep);
			name = name.Mid(lastSep + 1);
			
		}
		pResource = pRes;
	}

	CString name;
	CString path;
	IResource * pResource;

};
typedef multimap<CString, shared_ptr<ResourceHandle> > ResourceContainerMap;
typedef pair<CString, shared_ptr<ResourceHandle> > ResourceContainerPair;

class CMabinogiResourceToolDoc : public CDocument
{
protected: // 仅从序列化创建
	CMabinogiResourceToolDoc();
	DECLARE_DYNCREATE(CMabinogiResourceToolDoc)

// 特性
public:
	CString m_strDir;
	ResourceContainerMap m_resContainerMap;
// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMabinogiResourceToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	IResourceSet * m_pResourceSet;


// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
	void IndexResources(void);
};
