//////////////////////////////////////////////////////////////////////////  
/// @file    book_dlg.cpp    
/// @brief   impl file about BOOK  
///  
/// impl code about BOOK
///  
/// @version 1.0     
/// @author  无名    
/// @date    2021/09/03
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "book_dlg.h"
#include "afxdialogex.h"
#include "sqlite_utils.h"


// CBookDlg dialog
IMPLEMENT_DYNAMIC(CBookDlg, CDialogEx)

CBookDlg::CBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOK_DIALOG, pParent), BOOK_LIST_COL_NUM(8)
{
}

CBookDlg::~CBookDlg()
{
}

void CBookDlg::init_list_control()
{
	// TODO: 在此添加额外的初始化代码	
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_booklist_ctrl.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_booklist_ctrl.SetExtendedStyle(m_booklist_ctrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加三列   
	m_booklist_ctrl.InsertColumn(0, _T("Title"), LVCFMT_CENTER, rect.Width() / BOOK_LIST_COL_NUM, 0);
	m_booklist_ctrl.InsertColumn(1, _T("Author"), LVCFMT_CENTER, rect.Width() / BOOK_LIST_COL_NUM, 1);
	m_booklist_ctrl.InsertColumn(2, _T("Translator"), LVCFMT_CENTER, rect.Width() / BOOK_LIST_COL_NUM, 2);
	m_booklist_ctrl.InsertColumn(3, _T("Publisher"), LVCFMT_CENTER, rect.Width() / BOOK_LIST_COL_NUM, 3);
	m_booklist_ctrl.InsertColumn(4, _T("Year of publication"), LVCFMT_CENTER, rect.Width() / BOOK_LIST_COL_NUM, 4);
	m_booklist_ctrl.InsertColumn(5, _T("Number of pages"), LVCFMT_CENTER, rect.Width() / BOOK_LIST_COL_NUM, 5);
	m_booklist_ctrl.InsertColumn(6, _T("My score"), LVCFMT_CENTER, rect.Width() / BOOK_LIST_COL_NUM, 6);
	m_booklist_ctrl.InsertColumn(7, _T("Date of review"), LVCFMT_CENTER, rect.Width() / BOOK_LIST_COL_NUM, 7);

	// 在列表视图控件中插入列表项，并设置列表子项文本   
	//m_booklist_ctrl.InsertItem(0, _T("Java"));
	//m_booklist_ctrl.SetItemText(0, 1, _T("1"));
	//m_booklist_ctrl.SetItemText(0, 2, _T("1"));
	//m_booklist_ctrl.InsertItem(1, _T("C"));
	//m_booklist_ctrl.SetItemText(1, 1, _T("2"));
	//m_booklist_ctrl.SetItemText(1, 2, _T("2"));
	//m_booklist_ctrl.InsertItem(2, _T("C#"));
	//m_booklist_ctrl.SetItemText(2, 1, _T("3"));
	//m_booklist_ctrl.SetItemText(2, 2, _T("6"));
	//m_booklist_ctrl.InsertItem(3, _T("C++"));
	//m_booklist_ctrl.SetItemText(3, 1, _T("4"));
	//m_booklist_ctrl.SetItemText(3, 2, _T("3"));

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
	init_list_control();

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
	DDX_Control(pDX, IDC_BOOK_LIST, m_booklist_ctrl);
}


BEGIN_MESSAGE_MAP(CBookDlg, CDialogEx)
	ON_WM_PAINT()
	//ON_BN_CLICKED(IDC_INPT_TODAY_PRO_BTN, &CProTodayDlg::on_clicked_inpt_today_pro_btn)
	ON_BN_CLICKED(IDC_ADD_BOOK_BUTTON, &CBookDlg::on_book_add_btn_clicked)
	ON_BN_CLICKED(IDC_SEARCH_BOOK_BUTTON, &CBookDlg::on_bn_clicked_search_book_button)
END_MESSAGE_MAP()



void CBookDlg::on_book_add_btn_clicked()
{
	m_book_add_dlg.ShowWindow(SW_SHOW);
	return;
}


void CBookDlg::on_bn_clicked_search_book_button()
{
	this->m_booklist_ctrl.DeleteAllItems();
	std::list<CBook> book_review_list;
	CBookServ::get_inst().get_book_reviews(book_review_list);
	m_booklist_ctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	std::list<CBook>::iterator book_review_inter;

	for (book_review_inter = book_review_list.begin(); book_review_inter != book_review_list.end(); book_review_inter++)
	{
		int n_row = m_booklist_ctrl.InsertItem(0, book_review_inter->get_name().c_str());
		if (book_review_inter->get_authors().size() > 0)
		{
			std::wstring author_strs = book_review_inter->get_authors()[0];
			for (int i = 1; i < book_review_inter->get_authors().size(); i++)
			{
				author_strs.append(L",");
				author_strs.append(book_review_inter->get_authors()[i]);
			}
			m_booklist_ctrl.SetItemText(n_row, 1, author_strs.c_str());
		}
		if (book_review_inter->get_translators().size() > 0)
		{
			std::wstring translators_strs = book_review_inter->get_translators()[0];
			for (int i = 1; i < book_review_inter->get_translators().size(); i++)
			{
				translators_strs.append(L",");
				translators_strs.append(book_review_inter->get_translators()[i]);
			}
			m_booklist_ctrl.SetItemText(n_row, 2, translators_strs.c_str());
		}
		m_booklist_ctrl.SetItemText(n_row, 3, book_review_inter->get_publisher().c_str());
		m_booklist_ctrl.SetItemText(n_row, 4, book_review_inter->get_pub_year().c_str());
		m_booklist_ctrl.SetItemText(n_row, 5, book_review_inter->get_page_num().c_str());
		m_booklist_ctrl.SetItemText(n_row, 6, book_review_inter->get_score().c_str());
		m_booklist_ctrl.SetItemText(n_row, 7, book_review_inter->get_review_date().c_str());
	}
}
