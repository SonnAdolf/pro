#pragma once

#include "resource.h"

// CProStatisticsDlg �Ի���

class CProStatisticsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProStatisticsDlg)

public:
	CProStatisticsDlg(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~CProStatisticsDlg();

	// �Ի�������
	enum { IDD = IDD_PRO_STATISTICS_DIALOG};

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

};
