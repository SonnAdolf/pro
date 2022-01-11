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
	//virtual void Update();

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void on_clicked_add_book_btn();
private:
	CEdit m_tags_edit;
	CEdit m_name_edit;
	CEdit m_author_edit;
	CEdit m_translator_edit;
	CEdit m_publisher_edit;
	CEdit m_publis_year_edit;
	CEdit m_page_num_edit;
	int m_score_val;
	CDateTimeCtrl m_date_ctrl;
	int m_page_num_val;
	CEdit m_note_edit;
	CString m_note_str;
	CString m_tags_str;
	CString m_author_str;
	CString m_book_name_str;
	CString m_translators_str;
	int m_publish_year_val;
	CString m_publisher_str;
};
