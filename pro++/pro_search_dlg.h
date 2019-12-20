#pragma once

#include "resource.h"

// CProSearchDlg 对话框

class CProSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProSearchDlg)

public:
	CProSearchDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProSearchDlg();

	// 对话框数据
	enum { IDD = IDD_PRO_SEARCH_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void on_pro_search_btn_clicked();
};
