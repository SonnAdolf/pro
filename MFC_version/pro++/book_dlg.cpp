//////////////////////////////////////////////////////////////////////////  
/// @file    book_dlg.cpp    
/// @brief   impl file about BOOK  
///  
/// impl code about BOOK
///  
/// @version 1.0     
/// @author  ÎÞÃû    
/// @date    2021/09/03
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "book_dlg.h"
#include "afxdialogex.h"
#include "sqlite_utils.h"


// CBookDlg dialog
IMPLEMENT_DYNAMIC(CBookDlg, CDialogEx)

CBookDlg::CBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOK_DIALOG, pParent)
{
}

CBookDlg::~CBookDlg()
{
}


BOOL CBookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*set big icon*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*set small icon*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
	m_book_add_dlg.Create(CBookAddDlg::IDD, this);
	//m_date_ctrl.SetFormat(L"yyyy-MM-dd");
	return TRUE;
}


void CBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);/*
	DDX_Control(pDX, IDC_PRO_WRITING_EDIT, m_pro_writing_edit);
	DDX_Control(pDX, IDC_PRO_READING_EDIT, m_pro_reading_edit);
	DDX_Control(pDX, IDC_PRO_ART_LEARNING_EDIT, m_pro_art_learning_edit);
	DDX_Control(pDX, IDC_NOTE_EDIT, m_note_edit);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date_ctrl);
	DDX_Control(pDX, IDC_PRO_COMPUTER_EDIT, m_pro_computer_edit);*/
}


BEGIN_MESSAGE_MAP(CBookDlg, CDialogEx)
	ON_WM_PAINT()
	//ON_BN_CLICKED(IDC_INPT_TODAY_PRO_BTN, &CProTodayDlg::on_clicked_inpt_today_pro_btn)
	ON_BN_CLICKED(IDC_ADD_BOOK_BUTTON, &CBookDlg::on_book_add_btn_clicked)
END_MESSAGE_MAP()



void CBookDlg::on_book_add_btn_clicked()
{
	m_book_add_dlg.ShowWindow(SW_SHOW);
	return;
}
