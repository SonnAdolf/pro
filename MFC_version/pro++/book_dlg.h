#pragma once

#include "resource.h"

// CBookDlg dialog

class CBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookDlg)

public:
	CBookDlg(CWnd* pParent = nullptr);   
	virtual ~CBookDlg();

	// 对话框数据
	enum { IDD = IDD_BOOK_DIALOG};

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV suport

	DECLARE_MESSAGE_MAP()

};
