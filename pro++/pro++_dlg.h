// pro++_dlg.h: 头文件
//

#pragma once
#include "pro_today_dlg.h"
#include "pro_search_dlg.h"
#include "pro_statistics_dlg.h"

// CProPlusPlusDlg 对话框
class CProPlusPlusDlg : public CDialogEx
{
// 构造
public:
	CProPlusPlusDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void on_pro_today_btn_clicked();
private:
	CProTodayDlg m_pro_today_dlg;
	CProSearchDlg m_pro_search_dlg;
	CProStatisticsDlg m_pro_statistics_dlg;
public:
	afx_msg void on_pro_search_btn_clicked();
	afx_msg void on_pro_statistics_btn_clicked();
};
