//////////////////////////////////////////////////////////////////////////  
/// @file    book_add_dlg.cpp    
/// @brief   impl file about BOOK ADDING 
///  
/// impl code about BOOK ADDING
///  
/// @version 1.0     
/// @author  ÎÞÃû    
/// @date    2021/09/03
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "book_add_dlg.h"
#include "afxdialogex.h"
#include "sqlite_utils.h"


// CBookAddDlg dialog
IMPLEMENT_DYNAMIC(CBookAddDlg, CDialogEx)

CBookAddDlg::CBookAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOK_DIALOG, pParent)
{
}

CBookAddDlg::~CBookAddDlg()
{
}


BOOL CBookAddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*set big icon*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*set small icon*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
	m_date_ctrl.SetFormat(L"yyyy-MM-dd");
	return TRUE;
}


void CBookAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK_DATE_DATETIMEPICKER, m_date_ctrl);
	DDX_Control(pDX, IDC_BOOK_TAGS_EDIT, m_tags_edit);
}


BEGIN_MESSAGE_MAP(CBookAddDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_BOOK_ADD, &CBookAddDlg::on_clicked_add_book_btn)
END_MESSAGE_MAP()



void CBookAddDlg::on_clicked_add_book_btn()
{
	wchar_t buf1[50];

	m_tags_edit.GetWindowTextW(buf1, 200);
	CBookServ::get_inst().add_tag_ret_id(buf1);
}
