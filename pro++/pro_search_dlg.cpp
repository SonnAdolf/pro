//////////////////////////////////////////////////////////////////////////  
/// @file    pro_search_dlg.cpp    
/// @brief   ��ѯproֵ�����ʵ���ļ�  
///  
/// ���ļ�Ϊ��ѯproֵ�����ʵ�ִ���  
///  
/// @version 1.0     
/// @author  ����    
/// @date    2019/12/19
///   
///  
///  �޶�˵����  
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "pro_search_dlg.h"
#include "afxdialogex.h"
#include "sqlite_utils.h"
#include "pro.h"


// CProSearchDlg �Ի���
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
	/*���ô�ͼ��*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*����Сͼ��*/
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
