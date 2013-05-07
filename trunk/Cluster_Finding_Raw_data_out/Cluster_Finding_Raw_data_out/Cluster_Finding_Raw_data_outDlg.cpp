// Cluster_Finding_Raw_data_outDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Cluster_Finding_Raw_data_out.h"
#include "Cluster_Finding_Raw_data_outDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCluster_Finding_Raw_data_outDlg 对话框




CCluster_Finding_Raw_data_outDlg::CCluster_Finding_Raw_data_outDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCluster_Finding_Raw_data_outDlg::IDD, pParent)
{
	//给出各选项的初始化值
	StrFileName="data.txt";
	m_layer=5;
	m_charge=4;
	m_hit=5;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCluster_Finding_Raw_data_outDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1,StrFileName);
	DDX_CBIndex(pDX, IDC_COMBO1, m_layer);
	DDX_CBIndex(pDX, IDC_COMBO2, m_charge);
	DDX_CBIndex(pDX, IDC_COMBO3, m_hit);
}

BEGIN_MESSAGE_MAP(CCluster_Finding_Raw_data_outDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCluster_Finding_Raw_data_outDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCluster_Finding_Raw_data_outDlg 消息处理程序

BOOL CCluster_Finding_Raw_data_outDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCluster_Finding_Raw_data_outDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CCluster_Finding_Raw_data_outDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCluster_Finding_Raw_data_outDlg::OnBnClickedOk()
{
	UpdateData();
	// TODO: Add your control notification handler code here
	//初始化入射粒子
	v_incident.GetPosition(&p_x,&p_y);
	v_incident.GetDirection(&v_x,&v_y,&v_z);
	f_out.Open(StrFileName,CFile::modeCreate|CFile::modeReadWrite,NULL);
	f_out.Close();
}

