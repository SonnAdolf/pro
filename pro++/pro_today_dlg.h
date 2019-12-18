#pragma once

#include "resource.h"

// CProTodayDlg �Ի���

class CProTodayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProTodayDlg)

public:
	CProTodayDlg(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CProTodayDlg();

	// �Ի�������
	enum { IDD = IDD_PRO_TODAY_DIALOG};

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
public:
	afx_msg void on_clicked_inpt_today_pro_btn();
private:
	CEdit m_pro_art_learning_edit;
	CEdit m_pro_reading_edit;
	CEdit m_pro_writing_edit;
	CEdit m_note_edit;
	CDateTimeCtrl m_date_ctrl;
};
