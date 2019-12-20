//////////////////////////////////////////////////////////////////////////  
/// @file    pro_search_dlg.cpp    
/// @brief   查询pro值的类的实现文件  
///  
/// 本文件为查询pro值的类的实现代码  
///  
/// @version 1.0     
/// @author  无名    
/// @date    2019/12/19
///   
///  
///  修订说明：  
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "pro_search_dlg.h"
#include "afxdialogex.h"
#include "sqlite_utils.h"
#include "pro.h"


// CProSearchDlg 对话框
extern HANDLE g_hObject;
IMPLEMENT_DYNAMIC(CProSearchDlg, CDialogEx)

CProSearchDlg::CProSearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRO_TODAY_DIALOG, pParent)
{
}

CProSearchDlg::~CProSearchDlg()
{
}


BOOL CProSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*设置大图标*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*设置小图标*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
	return TRUE;
}


void CProSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProSearchDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PRO_SEARCH_BTN, &CProSearchDlg::on_pro_search_btn_clicked)
END_MESSAGE_MAP()




void CProSearchDlg::on_pro_search_btn_clicked()
{
	// TODO: 在此添加控件通知处理程序代码
}
