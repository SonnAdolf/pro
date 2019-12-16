#pragma once

#include "resource.h"

// CProTodayDlg 对话框

class CProTodayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProTodayDlg)

public:
	CProTodayDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProTodayDlg();

	// 对话框数据
	enum { IDD = IDD_PRO_TODAY_DIALOG};

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
};
