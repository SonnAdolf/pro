//////////////////////////////////////////////////////////////////////////  
/// @file    pro_search_dlg.cpp    
/// @brief   查询pro值的类的实现文件  
///  
/// 本文件为查询pro值的类的实现代码  
///  
/// @version 1.0     
/// @author  无名    
/// @date    2019/12/19
///          2021/04-05
///   
///  
///  修订说明：  
///           2021-03-08 添加計算機科學與技術研究相關時間管理
///           2021/04-05 添加下一天、上一天的快捷查詢
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
	m_pro_search_date_ctrl.SetFormat(L"yyyy-MM-dd");
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
	DDX_Control(pDX, IDC_PRO_COMPUTER_LEARN_SEARCH_EDIT, m_pro_computer_learn_search_edit);
}


BEGIN_MESSAGE_MAP(CProSearchDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PRO_SEARCH_BTN, &CProSearchDlg::on_pro_search_btn_clicked)
	ON_BN_CLICKED(IDC_DAY_NEXT_BUT, &CProSearchDlg::on_bn_clicked_day_next_but)
	ON_BN_CLICKED(IDC_BUTTON2, &CProSearchDlg::on_bn_clicked_day_pre_but)
END_MESSAGE_MAP()




void CProSearchDlg::on_pro_search_btn_clicked()
{
	wchar_t buf[12];
	m_pro_search_date_ctrl.GetWindowTextW(buf, 12);
	CPro pro;
	CSqliteUtils::get_inst().get_pro(buf,&pro);
	this->m_pro_art_learn_search_edit.SetWindowTextW(pro.get_art_learning_pro_str().c_str());
	this->m_pro_reading_search_edit.SetWindowTextW(pro.get_reading_pro_str().c_str());
	this->m_pro_total_search_edit.SetWindowTextW(pro.get_total_pro_str().c_str());
	this->m_pro_writing_search_edit.SetWindowTextW(pro.get_writing_pro_str().c_str());
	this->m_pro_note_search_edit.SetWindowTextW(pro.get_note().c_str());
	this->m_pro_computer_learn_search_edit.SetWindowTextW(pro.get_computer_learning_pro_str().c_str());
}

time_t string_to_datetime(std::wstring str)
{
	wchar_t* cha = (wchar_t*)str.data();                 // 将string转换成char*。
	tm tm_;                                              // 定义tm结构体。
	int year, month, day;                                // 定义时间的各个int临时变量。
														 // 将string存储的日期时间，转换为int临时变量。
	int ret = swscanf(cha, L"%d-%d-%d", &year, &month, &day);      
	tm_.tm_year = year - 1900;                           // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
	tm_.tm_mon = month - 1;                              // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
	tm_.tm_mday = day;                                   // 日。
	tm_.tm_hour = 0;                                     // 时。
	tm_.tm_min = 0;                                      // 分。
	tm_.tm_sec = 0;                                      // 秒。
	tm_.tm_isdst = 0;                                    // 非夏令时。
	time_t t_ = mktime(&tm_);                            // 将tm结构体转换成time_t格式。
	return t_;                                           // 返回值。
}

std::wstring datetime_to_string(time_t time)
{
	tm* tm_ = localtime(&time);                          // 将time_t格式转换为tm结构体
	int year, month, day;                                // 定义时间的各个int临时变量。
	year = tm_->tm_year + 1900;                          // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
	month = tm_->tm_mon + 1;                             // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
	day = tm_->tm_mday;                                  // 临时变量，秒。
	wchar_t yearStr[5], monthStr[3], dayStr[3];          // 定义时间的各个char*变量。
	wsprintf(yearStr, L"%d", year);                      // 年。
	wsprintf(monthStr, L"%d", month);                    // 月。
	wsprintf(dayStr, L"%d", day);                        // 日。
	wchar_t s[20]; 
	// 定义总日期时间char*变量。
	if (wcslen(monthStr) == 1 && wcslen(dayStr) == 1)
	{
		wsprintf(s, L"%s-0%s-0%s", yearStr, monthStr, dayStr);
	}
	else if (wcslen(monthStr) == 1)
	{
		wsprintf(s, L"%s-0%s-%s", yearStr, monthStr, dayStr);
	}
	else if (wcslen(dayStr) == 1)
	{
		wsprintf(s, L"%s-%s-0%s", yearStr, monthStr, dayStr);
	}
	else
	{
		wsprintf(s, L"%s-%s-%s", yearStr, monthStr, dayStr);// 将年月日时分秒合并。
	}
	std::wstring str(s);                                    // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
	return str;                                             // 返回转换日期时间后的string变量。
}

void CProSearchDlg::on_bn_clicked_day_next_but()
{
	wchar_t buf[12];
	m_pro_search_date_ctrl.GetWindowText(buf, 12);
	time_t next_date_time = string_to_datetime(buf);
	next_date_time = next_date_time + 24 * 60 * 60;
	std::wstring next_date_str = datetime_to_string(next_date_time);
	CPro pro;
	CSqliteUtils::get_inst().get_pro(next_date_str.c_str(), &pro);
	this->m_pro_art_learn_search_edit.SetWindowTextW(pro.get_art_learning_pro_str().c_str());
	this->m_pro_reading_search_edit.SetWindowTextW(pro.get_reading_pro_str().c_str());
	this->m_pro_total_search_edit.SetWindowTextW(pro.get_total_pro_str().c_str());
	this->m_pro_writing_search_edit.SetWindowTextW(pro.get_writing_pro_str().c_str());
	this->m_pro_note_search_edit.SetWindowTextW(pro.get_note().c_str());
	this->m_pro_computer_learn_search_edit.SetWindowTextW(pro.get_computer_learning_pro_str().c_str());
	m_pro_search_date_ctrl.SetWindowTextW(next_date_str.c_str());
	m_pro_search_date_ctrl.SetTime(next_date_time);
}


void CProSearchDlg::on_bn_clicked_day_pre_but()
{
	wchar_t buf[12];
	m_pro_search_date_ctrl.GetWindowText(buf, 12);
	time_t pre_date_time = string_to_datetime(buf);
	pre_date_time = pre_date_time - 24 * 60 * 60;
	std::wstring pre_date_str = datetime_to_string(pre_date_time);
	CPro pro;
	CSqliteUtils::get_inst().get_pro(pre_date_str.c_str(), &pro);
	this->m_pro_art_learn_search_edit.SetWindowTextW(pro.get_art_learning_pro_str().c_str());
	this->m_pro_reading_search_edit.SetWindowTextW(pro.get_reading_pro_str().c_str());
	this->m_pro_total_search_edit.SetWindowTextW(pro.get_total_pro_str().c_str());
	this->m_pro_writing_search_edit.SetWindowTextW(pro.get_writing_pro_str().c_str());
	this->m_pro_note_search_edit.SetWindowTextW(pro.get_note().c_str());
	this->m_pro_computer_learn_search_edit.SetWindowTextW(pro.get_computer_learning_pro_str().c_str());
	m_pro_search_date_ctrl.SetWindowTextW(pre_date_str.c_str());
	m_pro_search_date_ctrl.SetTime(pre_date_time);
}
