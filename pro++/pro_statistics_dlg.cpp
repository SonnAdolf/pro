//////////////////////////////////////////////////////////////////////////  
/// @file    pro_statistics_dlg.cpp    
/// @brief   ͳ��proֵ�Ľ������ʵ���ļ�  
///  
/// ���ļ���ͳ��proֵ�Ľ������ʵ�ִ���  
///  
/// @version 1.0     
/// @author  ����    
/// @date    2019/12/19
///   
///  
///  �޶�˵����  
///           2021-03-08 ���Ӌ��C�ƌW�c���g�о����P�r�g����
///           2021-03-17 ���F�����c߉݋���x
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "pro_statistics_dlg.h"
#include "afxdialogex.h"
#include "sqlite_utils.h"
#include "pro.h"


// CProStatisticsDlg �Ի���
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
	/*���ô�ͼ��*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*����Сͼ��*/
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
