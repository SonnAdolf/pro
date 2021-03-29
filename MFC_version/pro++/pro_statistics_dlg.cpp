//////////////////////////////////////////////////////////////////////////  
/// @file    pro_statistics_dlg.cpp    
/// @brief   统计pro值的界面类的实现文件  
///  
/// 本文件為统计pro值的界面类的实现代码  
///  
/// @version 1.0     
/// @author  无名    
/// @date    2019/12/19
///   
///  
///  修订说明：  
///           2021-03-08 添加計算機科學與技術研究相關時間管理
///           2021-03-17 實現界面與邏輯分離
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "pro_statistics_dlg.h"
#include "afxdialogex.h"
#include "sqlite_utils.h"
#include "pro.h"


// CProStatisticsDlg 对话框
extern HANDLE g_hObject;
IMPLEMENT_DYNAMIC(CProStatisticsDlg, CDialogEx)

CProStatisticsDlg::CProStatisticsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRO_TODAY_DIALOG, pParent)
{
}

CProStatisticsDlg::~CProStatisticsDlg()
{
}


BOOL CProStatisticsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*设置大图标*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*设置小图标*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);

	statitics();

	return TRUE;
}


void CProStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRO_STATISTICS_EDIT, m_pro_statistics_edit);
}

void CProStatisticsDlg::statitics()
{
	std::wstring pro_sum_info = CProStatisticsServ::get_inst().get_statistics_inf();
	m_pro_statistics_edit.SetWindowTextW(pro_sum_info.c_str());
}


BEGIN_MESSAGE_MAP(CProStatisticsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CProStatisticsDlg::on_refresh_btn_clicked)
END_MESSAGE_MAP()


void CProStatisticsDlg::on_refresh_btn_clicked()
{
	statitics();
}
