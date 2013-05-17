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
	loop_str="10";
	m_layer=5;
	m_charge=5;
	m_hit=5;
	truth_flag=false;
	particle_charge_flag=true;
	particle_num_flag=true;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCluster_Finding_Raw_data_outDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1,StrFileName);
	DDX_Text(pDX, IDC_EDIT2,loop_str);
	DDX_CBIndex(pDX, IDC_COMBO1, m_layer);
	DDX_CBIndex(pDX, IDC_COMBO2,  m_hit);
	DDX_CBIndex(pDX, IDC_COMBO3,m_charge);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);

}

BEGIN_MESSAGE_MAP(CCluster_Finding_Raw_data_outDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCluster_Finding_Raw_data_outDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CCluster_Finding_Raw_data_outDlg::OnBnClickedCheck1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CCluster_Finding_Raw_data_outDlg::OnNMCustomdrawProgress1)
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
	fileout.OpenDataFile(StrFileName);
	if(truth_flag)fileout.OpenTruthFile(StrFileName);
	p_x=0;
	p_y=0;
	p_z=0;
	double data_energy[6][STRIP_NUM];
	// TODO: Add your control notification handler code here
	//初始化入射粒子

	loop=_tstoi(loop_str);
	m_Progress.SetPos(0);
	m_Progress.SetRange(0,loop);
	m_Progress.SetStep(1);

	switch(m_charge)
	{
	case 0:
		particle_charge=1;
		particle_charge_flag=true;
		break;
	case 1:
		particle_charge=2;
		particle_charge_flag=true;
		break;
	case 2:
		particle_charge=3;
		particle_charge_flag=true;
		break;
	case 3:
		particle_charge=25;
		particle_charge_flag=true;
		break;
	case 4:
		particle_charge=26;
		particle_charge_flag=true;
		break;
	case 5:
		particle_charge=0;
		particle_charge_flag=false;
		break;
	default:
		break;
	}
	switch(m_hit)
	{
	case 0:
		particle_num=1;
		particle_num_flag=true;
		break;
	case 1:
		particle_num=2;
		particle_num_flag=true;
		break;
	case 2:
		particle_num=3;
		particle_num_flag=true;
		break;
	case 3:
		particle_num=10;
		particle_num_flag=true;
		break;
	case 4:
		particle_num=100;
		particle_num_flag=true;
		break;
	case 5:
		particle_num=0;
		particle_num_flag=false;
		break;
	default:
		break;
	}
	for(int i=0;i<loop;i++)
	{
		if(!particle_num_flag)particle_num=rnd.Poisson(1);
		for(int ii=0;ii<(m_layer+1);ii++)
		{
			sig.AddNoise(data_energy[ii]);
		}
		for(int ii=0;ii<particle_num;ii++)
		{
			int iii=0;
			v_incident.GetPosition(&p_x,&p_y);
			p_z=0;
			v_incident.GetDirection(&v_x,&v_y,&v_z);
			if(!particle_charge_flag)particle_charge=rnd.CosmicRandom();
			if(truth_flag)fileout.AddTruth(i,particle_charge,p_x,p_y,v_x,v_y,v_z);
			sig.SetCharge(particle_charge);
			while(Det_Check(p_x,p_y,p_z))
			{
				sig.SetStart(p_x,p_y);
				Track(DET_THICKNESS);
				sig.SetEnd(p_x,p_y);
				sig.SignalGen(data_energy[iii]);
				Track(DET_DIS);
				iii++;
			}
		}
		for(int ii=0;ii<(m_layer+1);ii++)
		{
			fileout.AddData(data_energy[ii]);
		}
		m_Progress.StepIt();
		Sleep(0.1);
	}
	m_Progress.SetPos(0);
	fileout.CloseDataFile();
	if(truth_flag)fileout.CloseTruth();
}
void CCluster_Finding_Raw_data_outDlg::Track(int z)
{
	p_x=z*v_x/v_z+p_x;//有可能造成数据误差 double转int
	p_y=z*v_y/v_z+p_y;
	p_z+=z;
}
int CCluster_Finding_Raw_data_outDlg::Det_Check(int x, int y, int z)
{
	if((x<MAX_X)&&(y<MAX_Y)&&(z<((m_layer+1)*DET_THICKNESS+m_layer*DET_DIS)))return 1;
	else return 0;
}

void CCluster_Finding_Raw_data_outDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	if(truth_flag)truth_flag=false;
	else truth_flag=true;
}

void CCluster_Finding_Raw_data_outDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
