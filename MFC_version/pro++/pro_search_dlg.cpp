//////////////////////////////////////////////////////////////////////////  
/// @file    pro_search_dlg.cpp    
/// @brief   ��ѯproֵ�����ʵ���ļ�  
///  
/// ���ļ�Ϊ��ѯproֵ�����ʵ�ִ���  
///  
/// @version 1.0     
/// @author  ����    
/// @date    2019/12/19
///          2021/04-05
///   
///  
///  �޶�˵����  
///           2021-03-08 ���Ӌ��C�ƌW�c���g�о����P�r�g����
///           2021/04-05 �����һ�졢��һ��Ŀ�ݲ�ԃ
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
	wchar_t* cha = (wchar_t*)str.data();                 // ��stringת����char*��
	tm tm_;                                              // ����tm�ṹ�塣
	int year, month, day;                                // ����ʱ��ĸ���int��ʱ������
														 // ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
	int ret = swscanf(cha, L"%d-%d-%d", &year, &month, &day);      
	tm_.tm_year = year - 1900;                           // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��
	tm_.tm_mon = month - 1;                              // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
	tm_.tm_mday = day;                                   // �ա�
	tm_.tm_hour = 0;                                     // ʱ��
	tm_.tm_min = 0;                                      // �֡�
	tm_.tm_sec = 0;                                      // �롣
	tm_.tm_isdst = 0;                                    // ������ʱ��
	time_t t_ = mktime(&tm_);                            // ��tm�ṹ��ת����time_t��ʽ��
	return t_;                                           // ����ֵ��
}

std::wstring datetime_to_string(time_t time)
{
	tm* tm_ = localtime(&time);                          // ��time_t��ʽת��Ϊtm�ṹ��
	int year, month, day;                                // ����ʱ��ĸ���int��ʱ������
	year = tm_->tm_year + 1900;                          // ��ʱ�������꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬������ʱ����intΪtm_year����1900��
	month = tm_->tm_mon + 1;                             // ��ʱ�������£�����tm�ṹ����·ݴ洢��ΧΪ0-11��������ʱ����intΪtm_mon����1��
	day = tm_->tm_mday;                                  // ��ʱ�������롣
	wchar_t yearStr[5], monthStr[3], dayStr[3];          // ����ʱ��ĸ���char*������
	wsprintf(yearStr, L"%d", year);                      // �ꡣ
	wsprintf(monthStr, L"%d", month);                    // �¡�
	wsprintf(dayStr, L"%d", day);                        // �ա�
	wchar_t s[20]; 
	// ����������ʱ��char*������
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
		wsprintf(s, L"%s-%s-%s", yearStr, monthStr, dayStr);// ��������ʱ����ϲ���
	}
	std::wstring str(s);                                    // ����string����������������ʱ��char*������Ϊ���캯���Ĳ������롣
	return str;                                             // ����ת������ʱ����string������
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
