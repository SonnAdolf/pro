//////////////////////////////////////////////////////////////////////////  
/// @file    pro_statistics_dlg.cpp    
/// @brief   ͳ��proֵ�����ʵ���ļ�  
///  
/// ���ļ�Ϊͳ��proֵ�����ʵ�ִ���  
///  
/// @version 1.0     
/// @author  ����    
/// @date    2019/12/19
///   
///  
///  �޶�˵����  
////////////////////////////////////////////////////////////////////////// 
#include "pch.h"
#include "pro_statistics_dlg.h"
#include "afxdialogex.h"
#include "sqlite_utils.h"
#include "pro.h"


// CProStatisticsDlg �Ի���
extern HANDLE g_hObject;
IMPLEMENT_DYNAMIC(CProStatisticsDlg, CDialogEx)

CProStatisticsDlg::CProStatisticsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRO_TODAY_DIALOG, pParent)
{
}

CProStatisticsDlg::~CProStatisticsDlg()
{
}


BOOL CProStatisticsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	/*���ô�ͼ��*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
	/*����Сͼ��*/
	SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);

	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	//��ȡ��ǰ���
	int this_year = 1900 + p->tm_year;
	//��ȡ��ǰ�·�
	int this_month = 1 + p->tm_mon;
	int month_num;

	int i,j = 0;
	float tmp_writing_pro_sum, tmp_reading_pro_sum,
		  tmp_art_learning_pro_sum, tmp_total_pro_sum=0;

	std::wstring pro_sum_info;
	wchar_t wz_temp[20] = { 0 };

	//�ӵ�ǰ��ݵ�2020
	for (i = 2019; i <= this_year; i++)
	{
		month_num = 12;
		if (i == this_year)
		{
			month_num = this_month;
		}
		_itow(i, wz_temp, 10);
		pro_sum_info.append(wz_temp).append(L"��:").append(L"\r\n");
		for (j = 1; j <= month_num; j++)
		{
			_itow(j, wz_temp, 10);
			pro_sum_info.append(wz_temp).append(L"��:  ");
			get_pro_sum_by_month(&tmp_writing_pro_sum, &tmp_reading_pro_sum, &tmp_art_learning_pro_sum, &tmp_total_pro_sum, i, j);
			swprintf_s(wz_temp, L"%.2f", tmp_writing_pro_sum);
			pro_sum_info.append(L"С˵д��Pro��ֵΪ:").append(wz_temp).append(L"   ").append(L"�Ķ�����Pro��ֵΪ:");
			swprintf_s(wz_temp, L"%.2f", tmp_reading_pro_sum);
			pro_sum_info.append(wz_temp).append(L"   ").append(L"����ѧϰPro��ֵΪ:");
			swprintf_s(wz_temp, L"%.2f", tmp_art_learning_pro_sum);
			pro_sum_info.append(wz_temp).append(L"   ").append(L"Pro��ֵΪ:");
			swprintf_s(wz_temp, L"%.2f", tmp_total_pro_sum);
			pro_sum_info.append(wz_temp).append(L"\r\n");
		}
		pro_sum_info.append(L"----------------------\r\n\r\n");
	}
	m_pro_statistics_edit.SetWindowTextW(pro_sum_info.c_str());

	return TRUE;
}


void CProStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRO_STATISTICS_EDIT, m_pro_statistics_edit);
}


BEGIN_MESSAGE_MAP(CProStatisticsDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


