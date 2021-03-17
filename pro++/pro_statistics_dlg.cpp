//////////////////////////////////////////////////////////////////////////  
/// @file    pro_statistics_dlg.cpp    
/// @brief   ͳ��proֵ�����ʵ���ļ�  
///  
/// ���ļ���ͳ��proֵ�����ʵ�ִ���  
///  
/// @version 1.0     
/// @author  ����    
/// @date    2019/12/19
///   
///  
///  �޶�˵����  
///           2021-03-08 ���Ӌ��C�ƌW�c���g�о����P�r�g����
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

	statitics();

	return TRUE;
}


void CProStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRO_STATISTICS_EDIT, m_pro_statistics_edit);
}

void CProStatisticsDlg::statitics()
{
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	//��ȡ��ǰ���
	int this_year = 1900 + p->tm_year;
	//��ȡ��ǰ�·�
	int this_month = 1 + p->tm_mon;
	int month_num;

	int i, j = 0;
	float tmp_writing_pro_sum, tmp_reading_pro_sum,
		tmp_art_learning_pro_sum, tmp_computer_learning_pro_sum, tmp_total_pro_sum = 0;

	std::wstring pro_sum_info;
	wchar_t wz_temp[20] = { 0 };
	float day_num = 0.00;
	int tmp_day_num = 0;
	float average_w_pro,average_r_pro,average_a_pro, average_c_pro,average_t_pro = 0.00;

	//��2019��12�¿�ʼͳ��
	for (i = 2019; i <= this_year; i++)
	{
		month_num = 12;
		if (i == this_year)
		{
			month_num = this_month;
		}

		j = 1;
		if (i == 2019)
			j = 12;

		//ÿ��ͳ��
		for (; j <= month_num; j++)
		{
			_itow(j, wz_temp, 10);
			pro_sum_info.append(wz_temp).append(L"��:  ");
			CSqliteUtils::get_inst().get_pro_sum_by_month(&tmp_writing_pro_sum, &tmp_reading_pro_sum, &tmp_art_learning_pro_sum, &tmp_computer_learning_pro_sum, &tmp_total_pro_sum, i, j);
			swprintf_s(wz_temp, L"%.2f", tmp_writing_pro_sum);
			pro_sum_info.append(L"�����Õr:").append(wz_temp).append(L"   ").append(L"��x�{���Õr:");
			swprintf_s(wz_temp, L"%.2f", tmp_reading_pro_sum);
			pro_sum_info.append(wz_temp).append(L"   ").append(L"ˇ�g�W���Õr:");
			swprintf_s(wz_temp, L"%.2f", tmp_art_learning_pro_sum);
			pro_sum_info.append(wz_temp).append(L"   ").append(L"Ӌ��C�ƌW���g�����Õr:");
			swprintf_s(wz_temp, L"%.2f", tmp_computer_learning_pro_sum);
			pro_sum_info.append(wz_temp).append(L"   ").append(L"�G�Õr:");
			swprintf_s(wz_temp, L"%.2f", tmp_total_pro_sum);
			pro_sum_info.append(wz_temp);

			CSqliteUtils::get_inst().count_pro_by_month(&tmp_day_num, i,j);
			day_num = tmp_day_num;
			average_t_pro = tmp_total_pro_sum / day_num;
			average_w_pro = tmp_writing_pro_sum / day_num;
			average_a_pro = tmp_art_learning_pro_sum / day_num;
			average_c_pro = tmp_computer_learning_pro_sum / day_num;
			average_r_pro = tmp_reading_pro_sum / day_num;
			swprintf_s(wz_temp, L"%.2f", average_w_pro);
			pro_sum_info.append(L"   ").append(L"ƽ��ֵ(��-�x-ˇ-��-��):").append(wz_temp).append(L"-");
			swprintf_s(wz_temp, L"%.2f", average_r_pro);
			pro_sum_info.append(wz_temp).append(L"-");
			swprintf_s(wz_temp, L"%.2f", average_a_pro);
			pro_sum_info.append(wz_temp).append(L"-");
			swprintf_s(wz_temp, L"%.2f", average_c_pro);
			pro_sum_info.append(wz_temp).append(L"-");
			swprintf_s(wz_temp, L"%.2f", average_t_pro);
			pro_sum_info.append(wz_temp).append(L"\r\n");;
		}
		//ÿ��ͳ��
		pro_sum_info.append(L"----------------------\r\n");
		_itow(i, wz_temp, 10);
		pro_sum_info.append(wz_temp).append(L"��:");
		CSqliteUtils::get_inst().get_pro_sum_by_year(&tmp_writing_pro_sum, &tmp_reading_pro_sum, &tmp_art_learning_pro_sum, &tmp_computer_learning_pro_sum, &tmp_total_pro_sum, i);
		swprintf_s(wz_temp, L"%.2f", tmp_writing_pro_sum);
		pro_sum_info.append(L"�����Õr:").append(wz_temp).append(L"   ").append(L"��x�{���Õr:");
		swprintf_s(wz_temp, L"%.2f", tmp_reading_pro_sum);
		pro_sum_info.append(wz_temp).append(L"   ").append(L"ˇ�g�W���Õr:");
		swprintf_s(wz_temp, L"%.2f", tmp_art_learning_pro_sum);
		pro_sum_info.append(wz_temp).append(L"   ").append(L"Ӌ��C�ƌW���g�����Õr:");
		swprintf_s(wz_temp, L"%.2f", tmp_computer_learning_pro_sum);
		pro_sum_info.append(wz_temp).append(L"   ").append(L"�G�Õr:");
		swprintf_s(wz_temp, L"%.2f", tmp_total_pro_sum);
		pro_sum_info.append(wz_temp);

		CSqliteUtils::get_inst().count_pro_by_year(&tmp_day_num,i);
		day_num = tmp_day_num;
		average_t_pro = tmp_total_pro_sum / day_num;
		average_w_pro = tmp_writing_pro_sum / day_num;
		average_a_pro = tmp_art_learning_pro_sum / day_num;
		average_c_pro = tmp_computer_learning_pro_sum / day_num;
		average_r_pro = tmp_reading_pro_sum / day_num;
		swprintf_s(wz_temp, L"%.2f", average_w_pro);
		pro_sum_info.append(L"   ").append(L"ƽ��ֵ(��-�x-ˇ-��-��):").append(wz_temp).append(L"-");
		swprintf_s(wz_temp, L"%.2f", average_r_pro);
		pro_sum_info.append(wz_temp).append(L"-");
		swprintf_s(wz_temp, L"%.2f", average_a_pro);
		pro_sum_info.append(wz_temp).append(L"-");
		swprintf_s(wz_temp, L"%.2f", average_c_pro);
		pro_sum_info.append(wz_temp).append(L"-");
		swprintf_s(wz_temp, L"%.2f", average_t_pro);
		pro_sum_info.append(wz_temp).append(L"\r\n");;

		pro_sum_info.append(L"----------------------\r\n\r\n");
	}
	//�ܼ�
	pro_sum_info.append(L"��Ӌ:");
	CSqliteUtils::get_inst().get_pro_sum(&tmp_writing_pro_sum, &tmp_reading_pro_sum, &tmp_art_learning_pro_sum, &tmp_computer_learning_pro_sum, &tmp_total_pro_sum);
	swprintf_s(wz_temp, L"%.2f", tmp_writing_pro_sum);
	pro_sum_info.append(L"�����Õr:").append(wz_temp).append(L"   ").append(L"��x�{���Õr:");
	swprintf_s(wz_temp, L"%.2f", tmp_reading_pro_sum);
	pro_sum_info.append(wz_temp).append(L"   ").append(L"ˇ�g�W���Õr:");
	swprintf_s(wz_temp, L"%.2f", tmp_art_learning_pro_sum);
	pro_sum_info.append(wz_temp).append(L"   ").append(L"Ӌ��C�ƌW���g�����Õr:");
	swprintf_s(wz_temp, L"%.2f", tmp_computer_learning_pro_sum);
	pro_sum_info.append(wz_temp).append(L"   ").append(L"�G�Õr:");
	swprintf_s(wz_temp, L"%.2f", tmp_total_pro_sum);
	pro_sum_info.append(wz_temp);

	CSqliteUtils::get_inst().count_pro(&tmp_day_num);
	day_num = tmp_day_num;
	average_t_pro = tmp_total_pro_sum / day_num;
	average_w_pro = tmp_writing_pro_sum / day_num;
	average_a_pro = tmp_art_learning_pro_sum / day_num;
	average_c_pro = tmp_computer_learning_pro_sum / day_num;
	average_r_pro = tmp_reading_pro_sum / day_num;
	swprintf_s(wz_temp, L"%.2f", average_w_pro);
	pro_sum_info.append(L"   ").append(L"ƽ��ֵ(��-�x-ˇ-��-��):").append(wz_temp).append(L"-");
	swprintf_s(wz_temp, L"%.2f", average_r_pro);
	pro_sum_info.append(wz_temp).append(L"-");
	swprintf_s(wz_temp, L"%.2f", average_a_pro);
	pro_sum_info.append(wz_temp).append(L"-");
	swprintf_s(wz_temp, L"%.2f", average_c_pro);
	pro_sum_info.append(wz_temp).append(L"-");
	swprintf_s(wz_temp, L"%.2f", average_t_pro);
	pro_sum_info.append(wz_temp);

	m_pro_statistics_edit.SetWindowTextW(pro_sum_info.c_str());
}


BEGIN_MESSAGE_MAP(CProStatisticsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_REFRESH_BTN, &CProStatisticsDlg::on_refresh_btn_clicked)
END_MESSAGE_MAP()




void CProStatisticsDlg::on_refresh_btn_clicked()
{
	statitics();
}
