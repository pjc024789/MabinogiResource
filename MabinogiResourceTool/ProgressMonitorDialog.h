#pragma once


// CProgressMonitorDialog 对话框

class CProgressMonitorDialog : public CDialog
{
	DECLARE_DYNAMIC(CProgressMonitorDialog)

public:
	CProgressMonitorDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgressMonitorDialog();

// 对话框数据
	enum { IDD = IDD_PROGRESSMONITORDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
