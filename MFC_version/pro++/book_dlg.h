#pragma once

#include "resource.h"
#include "book_add_dlg.h"
#include "book_edit_dlg.h"

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

public:
	afx_msg void on_book_add_btn_clicked();
private:
	CBookAddDlg m_book_add_dlg;
	CBookEditDlg m_book_edit_dlg;
	std::list<CBook> m_book_review_list;
public:
	afx_msg void on_bn_clicked_search_book_button();
private:
	void init_list_control();
private:
	CListCtrl m_booklist_ctrl;
	const int BOOK_LIST_COL_NUM;
public:
	afx_msg void on_bn_clicked_edit_button();
};
