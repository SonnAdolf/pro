#pragma once

#include "resource.h"

// CProSearchDlg �Ի���

class CProSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProSearchDlg)

public:
	CProSearchDlg(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CProSearchDlg();

	// �Ի�������
	enum { IDD = IDD_PRO_SEARCH_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void on_pro_search_btn_clicked();
private:
	CEdit m_pro_writing_search_edit;
	CEdit m_pro_reading_search_edit;
	CDateTimeCtrl m_pro_search_date_ctrl;
	CEdit m_pro_art_learn_search_edit;
	CEdit m_pro_total_search_edit;
	CEdit m_pro_note_search_edit;
	CEdit m_pro_computer_learn_search_edit;
};
