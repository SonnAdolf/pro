//////////////////////////////////////////////////////////////////////////  
/// @file    pro_today_dlg.cpp    
/// @brief   添加今日pro值的类的实现文件  
///  
/// 本文件为添加今日pro值的类的实现代码  
///  
/// @version 1.0     
/// @author  无名    
/// @date    2019/12/16
///   
///  
///  修订说明：  
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "pro_today_dlg.h"
#include "afxdialogex.h"


// CProTodayDlg 对话框
extern HANDLE g_hObject;
IMPLEMENT_DYNAMIC(CProTodayDlg, CDialogEx)

CProTodayDlg::CProTodayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRO_TODAY_DIALOG, pParent)
{
}

CProTodayDlg::~CProTodayDlg()
{
}


BOOL CProTodayDlg::OnInitDialog()
{
	/*设置大图标*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*设置小图标*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
	return 0;
}


void CProTodayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	return;
}


BEGIN_MESSAGE_MAP(CProTodayDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


