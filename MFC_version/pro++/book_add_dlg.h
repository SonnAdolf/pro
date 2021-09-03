#pragma once

#include "resource.h"
#include "book_serv.h"

// CBookDlg dialog

class CBookAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookAddDlg)

public:
	CBookAddDlg(CWnd* pParent = nullptr);
	virtual ~CBookAddDlg();

	// 对话框数据
	enum { IDD = IDD_BOOK_ADD_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV suport

	DECLARE_MESSAGE_MAP()

private:
	CDateTimeCtrl m_date_ctrl;
public:
	afx_msg void on_clicked_add_book_btn();
private:
	CEdit m_tags_edit;
};
