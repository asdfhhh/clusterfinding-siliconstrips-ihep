// Cluster_Finding_Raw_data_outDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cluster_Finding_Raw_data_out.h"
#include "Cluster_Finding_Raw_data_outDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCluster_Finding_Raw_data_outDlg �Ի���




CCluster_Finding_Raw_data_outDlg::CCluster_Finding_Raw_data_outDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCluster_Finding_Raw_data_outDlg::IDD, pParent)
{
	//������ѡ��ĳ�ʼ��ֵ
	StrFileName="data.txt";
	loop_str="10";
	m_layer=5;
	m_charge=5;
	m_hit=5;
	truth_flag=false;
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


// CCluster_Finding_Raw_data_outDlg ��Ϣ�������

BOOL CCluster_Finding_Raw_data_outDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCluster_Finding_Raw_data_outDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
	// TODO: Add your control notification handler code here
	//��ʼ����������

	loop=_tstoi(loop_str);
	m_Progress.SetPos(0);
	m_Progress.SetRange(0,loop);
	m_Progress.SetStep(1);

	switch(m_charge)
	{
	case 0:
		particle_charge=1;
		break;
	case 1:
		particle_charge=2;
		break;
	case 2:
		particle_charge=3;
		break;
	case 3:
		particle_charge=25;
		break;
	case 4:
		particle_charge=26;
		break;
	case 5:
		particle_charge=0;
		break;
	default:
		break;
	}
	switch(m_hit)
	{
	case 0:
		particle_num=1;
		break;
	case 1:
		particle_num=2;
		break;
	case 2:
		particle_num=3;
		break;
	case 3:
		particle_num=10;
		break;
	case 4:
		particle_num=100;
		break;
	case 5:
		particle_num=0;
		break;
	default:
		break;
	}
	for(int i=0;i<loop;i++)
	{
		if(!particle_num)particle_num=rnd.Poisson(1);
		for(int ii=0;ii<particle_num;ii++)
		{
			v_incident.GetPosition(&p_x,&p_y);
			p_z=0;
			v_incident.GetDirection(&v_x,&v_y,&v_z);
			if(!particle_charge)particle_charge=rnd.CosmicRandom();
			if(truth_flag)fileout.AddTruth(particle_charge,p_x,p_y,v_x,v_y,v_z);
			sig.SetCharge(particle_charge);
			for(int iii=0;iii<(m_layer+1);iii++)
			{
				if(Det_Check(p_x,p_y,p_z))
				{
					sig.SetStart(p_x,p_y);
					Track(DET_THICKNESS);
					sig.SetEnd(p_x,p_y);
				}
				else sig.AddNoise(data_energy);
				int chhhh=sizeof(data_energy);
				sig.SignalGen(data_energy);
				fileout.AddData(data_energy);
				Track(DET_DIS);
			}
		}
		m_Progress.StepIt();
		Sleep(1);
	}
	fileout.CloseDataFile();
	if(truth_flag)fileout.CloseTruth();
}
void CCluster_Finding_Raw_data_outDlg::Track(int z)
{
	p_x=z*v_x/v_z+p_x;//�п������������� doubleתint
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
