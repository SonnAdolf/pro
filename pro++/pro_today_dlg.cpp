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
#include "sqlite_utils.h"
#include "pro.h"


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
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date_ctrl);
}


BEGIN_MESSAGE_MAP(CProTodayDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_INPT_TODAY_PRO_BTN, &CProTodayDlg::on_clicked_inpt_today_pro_btn)
END_MESSAGE_MAP()


void CProTodayDlg::on_clicked_inpt_today_pro_btn()
{
	wchar_t buf1[6], buf2[6], buf3[6];
	wchar_t* buf4 = new wchar_t[402];
	wchar_t buf5[12];

	m_pro_writing_edit.GetWindowTextW(buf1,5);
	m_pro_reading_edit.GetWindowTextW(buf2, 5);
	m_pro_art_learning_edit.GetWindowTextW(buf3, 5);
	m_note_edit.GetWindowTextW(buf4, 401);
	m_date_ctrl.GetWindowTextW(buf5, 12);

	CPro pro(buf1,buf2,buf3,buf4);

	if (pro.get_note().length() > 400)
	{
		MessageBox(L"��ע����", L"��ʾ");
		return;
	}
	if (pro.get_total_pro() > 16)
	{
		MessageBox(L"�ܸ�16Сʱ���ϣ��𳶵�", L"��ʾ");
		return;
	}
	if (!check_if_pro_of_date_exist(buf5))
	{
		add_pro(pro, buf5);
	}
	else
	{
		update_pro(pro, buf5);
	}
	MessageBox(L"pro++ yeah", L"��ʾ");
	delete[] buf4;
	return;
}
