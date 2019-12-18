//////////////////////////////////////////////////////////////////////////  
/// @file    pro_today_dlg.cpp    
/// @brief   ���ӽ���proֵ�����ʵ���ļ�  
///  
/// ���ļ�Ϊ���ӽ���proֵ�����ʵ�ִ���  
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
#include "sqlite_utils.h"


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
	CDialogEx::OnInitDialog();
	/*���ô�ͼ��*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*����Сͼ��*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
	return TRUE;
}


void CProTodayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRO_WRITING_EDIT, m_pro_writing_edit);
	DDX_Control(pDX, IDC_PRO_READING_EDIT, m_pro_reading_edit);
	DDX_Control(pDX, IDC_PRO_ART_LEARNING_EDIT, m_pro_art_learning_edit);
	DDX_Control(pDX, IDC_NOTE_EDIT, m_note_edit);
}


BEGIN_MESSAGE_MAP(CProTodayDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_INPT_TODAY_PRO_BTN, &CProTodayDlg::on_clicked_inpt_today_pro_btn)
END_MESSAGE_MAP()




void CProTodayDlg::on_clicked_inpt_today_pro_btn()
{
	WCHAR buf1[6],buf2[6],buf3[6],buf4[201];
	m_pro_writing_edit.GetWindowTextW(buf1,5);
	m_pro_reading_edit.GetWindowTextW(buf2, 5);
	m_pro_art_learning_edit.GetWindowTextW(buf3, 5);
	m_note_edit.GetWindowTextW(buf4, 200);
	add_pro_today(buf1,buf2,buf3,buf4);
	return;
}