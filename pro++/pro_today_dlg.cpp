//////////////////////////////////////////////////////////////////////////  
/// @file    pro_today_dlg.cpp    
/// @brief   ��ӽ���proֵ�����ʵ���ļ�  
///  
/// ���ļ�Ϊ��ӽ���proֵ�����ʵ�ִ���  
///  
/// @version 1.0     
/// @author  ����    
/// @date    2019/12/16
///   
///  
///  �޶�˵����  
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "pro_today_dlg.h"
#include "afxdialogex.h"


// CProTodayDlg �Ի���
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
	/*���ô�ͼ��*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*����Сͼ��*/
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


