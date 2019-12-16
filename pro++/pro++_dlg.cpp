
// pro++_dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "pro++.h"
#include "pro++_dlg.h"
#include "afxdialogex.h"
#include "skin_h.h"
#include "sqlite_utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"lib\\SkinHu.lib")
#pragma comment(lib,"lib\\sqlite3.lib")

// CProPlusPlusDlg 对话框



CProPlusPlusDlg::CProPlusPlusDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProPlusPlusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProPlusPlusDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PRO_TODAY_BTN, &CProPlusPlusDlg::on_pro_today_btn_clicked)
END_MESSAGE_MAP()


BOOL CProPlusPlusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	SkinH_Attach();
	sqlite_conn();
	create_tables();

	m_pro_today_dlg.Create(CProTodayDlg::IDD,this);

	return TRUE; 
}


void CProPlusPlusDlg::OnPaint()
{
	CImage image;
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_PIC_STATIC);
	CDC* pDC = pWnd->GetDC();
	HDC hDC = pDC->m_hDC;
	CRect rect_frame;
	pWnd->GetClientRect(&rect_frame);
	image.Load(L"pics\\Kafka.jpg");
	::SetStretchBltMode(hDC, HALFTONE);
	::SetBrushOrgEx(hDC, 0, 0, NULL);
	image.Draw(hDC, rect_frame);
	ReleaseDC(pDC);
	image.Destroy();

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProPlusPlusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProPlusPlusDlg::on_pro_today_btn_clicked()
{
	this->m_pro_today_dlg.ShowWindow(SW_SHOW);
	return;
}
