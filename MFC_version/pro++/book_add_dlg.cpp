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
#include "str_utils.h"


// CBookAddDlg dialog
IMPLEMENT_DYNAMIC(CBookAddDlg, CDialogEx)

CBookAddDlg::CBookAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOK_DIALOG, pParent)
	, m_score_val(0)
	, m_page_num_val(0)
	, m_note_str(_T(""))
	, m_tags_str(_T(""))
	, m_author_str(_T(""))
	, m_book_name_str(_T(""))
	, m_translators_str(_T(""))
	, m_publish_year_val(0)
	, m_publisher_str(_T(""))
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
	DDX_Control(pDX, IDC_BOOK_NAME_EDIT, m_name_edit);
	DDX_Control(pDX, IDC_BOOK_AUTHOR_EDIT, m_author_edit);
	DDX_Control(pDX, IDC_BOOK_TRANSLATOR_EDIT, m_translator_edit);
	DDX_Control(pDX, IDC_BOOK_PUBLISHER_EDIT, m_publisher_edit);
	DDX_Control(pDX, IDC_BOOK_PUB_YEAR_EDIT, m_publis_year_edit);
	DDX_Control(pDX, IDC_BOOK_PAGE_NUM_EDIT, m_page_num_edit);
	DDX_Text(pDX, IDC_BOOK_SCORE_EDIT, m_score_val);
	DDV_MinMaxInt(pDX, m_score_val, 0, 100);
	DDX_Text(pDX, IDC_BOOK_PAGE_NUM_EDIT, m_page_num_val);
	DDV_MinMaxInt(pDX, m_page_num_val, 1, 100000000);
	DDX_Control(pDX, IDC_BOOK_NOTE_EDIT, m_note_edit);
	DDX_Text(pDX, IDC_BOOK_NOTE_EDIT, m_note_str);
	DDX_Text(pDX, IDC_BOOK_TAGS_EDIT, m_tags_str);
	DDX_Text(pDX, IDC_BOOK_AUTHOR_EDIT, m_author_str);
	DDX_Text(pDX, IDC_BOOK_NAME_EDIT, m_book_name_str);
	DDX_Text(pDX, IDC_BOOK_TRANSLATOR_EDIT, m_translators_str);
	DDX_Text(pDX, IDC_BOOK_PUB_YEAR_EDIT, m_publish_year_val);
	DDV_MinMaxInt(pDX, m_publish_year_val, 0, 2992);
	DDX_Text(pDX, IDC_BOOK_PUBLISHER_EDIT, m_publisher_str);
}


BEGIN_MESSAGE_MAP(CBookAddDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_BOOK_ADD, &CBookAddDlg::on_clicked_add_book_btn)
END_MESSAGE_MAP()



void CBookAddDlg::on_clicked_add_book_btn()
{
	CWnd::UpdateData();
	int temp_id;
	if (m_book_name_str.GetLength()<=0)
	{
		MessageBox(L"PLEASE INPUT THE NAME OF THE BOOK.", L"NOTE");
		return;
	}

	if (m_tags_str.GetLength() <= 0)
	{
		MessageBox(L"PLEASE INPUT AUTHOR.", L"NOTE");
		return;
	}
	wchar_t buf1[12];
	std::wstring tag_str = m_tags_str;
	std::vector<std::wstring> tag_strs = split(tag_str, L"_");
	// should delete the repeating string 

	std::vector<int> tags_ids;
	for (int i = 0; i < tag_strs.size(); i++) 
	{
		tags_ids.push_back(CBookServ::get_inst().add_tag_ret_id(tag_strs[i]));
		if (tags_ids[i] < 0)
		{
			MessageBox(L"ERROR HAPPENED WHEN INSERTING INTO DATABASE.", L"NOTE");
			return;
		}
	}

	std::wstring author_str = m_author_str;
	std::vector<std::wstring> author_strs = split(author_str, L"_");
	std::vector<int> authors_ids;
	for (int i = 0; i < author_strs.size(); i++)
	{
		authors_ids.push_back(CBookServ::get_inst().add_author_ret_id(author_strs[i]));
		if (authors_ids[i] < 0)
		{
			MessageBox(L"ERROR HAPPENED WHEN INSERTING INTO DATABASE.", L"NOTE");
			return;
		}
	}
	std::wstring translator_str = m_translators_str;
	std::vector<std::wstring> translator_strs = split(translator_str, L"_");
	std::vector<int> translators_ids;
	for (int i = 0; i < translator_strs.size(); i++)
	{
		translators_ids.push_back(CBookServ::get_inst().add_translator_ret_id(translator_strs[i]));
		if (translators_ids[i] < 0)
		{
			MessageBox(L"ERROR HAPPENED WHEN INSERTING INTO DATABASE.", L"NOTE");
			return;
		}
	}

	std::wstring publisher_str = m_publisher_str;
	int publisher_id = CBookServ::get_inst().add_publisher_ret_id(publisher_str);
	if (publisher_id < 0)
	{
		MessageBox(L"ERROR HAPPENED WHEN INSERTING INTO DATABASE.", L"NOTE");
		return;
	}

	m_date_ctrl.GetWindowTextW(buf1, 12);

	WCHAR buf_page_num[10];
	WCHAR buf_score[10];
	WCHAR buf_publish_year[10];
	WCHAR buf_publish_id[10];
	_itow(m_score_val, buf_score, 10);
	_itow(m_page_num_val, buf_page_num, 10);
	_itow(m_publish_year_val, buf_publish_year, 10);
	_itow(publisher_id, buf_publish_id, 10);

	wchar_t buf_date[12];
	m_date_ctrl.GetWindowTextW(buf_date, 12);
	std::wstring str_date = buf_date;
	int pos;
	pos = str_date.find(L"/");
	while (pos != -1) {
		str_date.replace(pos, std::wstring(L"/").length(), L"-");
		pos = str_date.find(L"/");
	}

	temp_id = CBookServ::get_inst().add_book_review_ret_id(static_cast<std::wstring>(m_book_name_str), buf_score, buf_publish_id,
		static_cast<std::wstring>(m_note_str), buf_page_num, str_date, buf_publish_year);
	if (temp_id < 0)
	{
		MessageBox(L"ERROR HAPPENED WHEN INSERTING INTO DATABASE.", L"NOTE");
		return;
	}
	WCHAR buf_book_id[10];
	_itow(temp_id, buf_book_id, 10);
	WCHAR buf_tag_id[10];
	for (int i = 0; i < tags_ids.size(); i++)
	{
		_itow(tags_ids[i], buf_tag_id, 10);
		CBookServ::get_inst().add_tag_book_relation(buf_tag_id, buf_book_id);
	}
	WCHAR buf_author_id[10];
	for (int i = 0; i < authors_ids.size(); i++)
	{
		_itow(authors_ids[i], buf_author_id, 10);
		CBookServ::get_inst().add_author_book_relation(buf_author_id, buf_book_id);
	}
	WCHAR buf_translator_id[10];
	for (int i = 0; i < translators_ids.size(); i++)
	{
		_itow(translators_ids[i], buf_translator_id, 10);
		CBookServ::get_inst().add_translator_book_relation(buf_translator_id, buf_book_id);
	}
	MessageBox(L"HAVE ADDED THE BOOK REVIEW.", L"NOTE");
}
