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
	DDX_Control(pDX, IDC_PRO_WRITING_SEARCH_EDIT, m_pro_writing_search_edit);
	DDX_Control(pDX, IDC_PRO_READING_SEARCH_EDIT, m_pro_reading_search_edit);
	DDX_Control(pDX, IDC_PRO_SEARCH_DATE, m_pro_search_date_ctrl);
	DDX_Control(pDX, IDC_PRO_ART_LEARN_SEARCH_EDIT, m_pro_art_learn_search_edit);
	DDX_Control(pDX, IDC_PRO_TOTAL_SEARCH_EDIT, m_pro_total_search_edit);
	DDX_Control(pDX, IDC_NOTE_SEARCH_EDIT, m_pro_note_search_edit);
}


BEGIN_MESSAGE_MAP(CProSearchDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PRO_SEARCH_BTN, &CProSearchDlg::on_pro_search_btn_clicked)
END_MESSAGE_MAP()




void CProSearchDlg::on_pro_search_btn_clicked()
{
	wchar_t buf[12];
	m_pro_search_date_ctrl.GetWindowTextW(buf, 12);
	CPro pro;
	get_pro(buf,&pro);
	this->m_pro_art_learn_search_edit.SetWindowTextW(pro.get_art_learning_pro_str().c_str());
	this->m_pro_reading_search_edit.SetWindowTextW(pro.get_reading_pro_str().c_str());
	this->m_pro_total_search_edit.SetWindowTextW(pro.get_total_pro_str().c_str());
	this->m_pro_writing_search_edit.SetWindowTextW(pro.get_writing_pro_str().c_str());
	this->m_pro_note_search_edit.SetWindowTextW(pro.get_note().c_str());
}
