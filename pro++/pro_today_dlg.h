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
};
