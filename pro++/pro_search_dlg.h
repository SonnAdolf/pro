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
};
