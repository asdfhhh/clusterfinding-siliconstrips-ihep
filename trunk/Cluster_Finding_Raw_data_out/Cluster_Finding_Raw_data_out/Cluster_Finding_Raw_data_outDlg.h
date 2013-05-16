// Cluster_Finding_Raw_data_outDlg.h : ͷ�ļ�
//

#pragma once
#include "Incident_vector.h"
#include "WriteFileUser.h"
#include "RandomUser.h"
#include "Constant.h"
#include "Signal.h"
// CCluster_Finding_Raw_data_outDlg �Ի���
class CCluster_Finding_Raw_data_outDlg : public CDialog
{
	// ����
public:
	CCluster_Finding_Raw_data_outDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CString StrFileName; //�ļ���
	int m_layer; //̽��������ѡ��
	int m_charge; //���ӵ��ģʽѡ��
	int m_hit; //������������ѡ��
	unsigned int p_x;  //�������ӳ�ʼλ��x
	unsigned int p_y;  //�������ӳ�ʼλ��y
	unsigned int p_z;
	double v_x;//�������ӳ�ʼ����x,y,z
	double v_y;
	double v_z;
	int particle_charge;//�������ӵ��
	int particle_num;//������������
	bool particle_charge_flag;//�������ӵ��
	bool particle_num_flag;//������������
	int loop;//ѭ������
	double data_energy[STRIP_NUM];
	double data_out[DATA_NUM];

	CString loop_str;
	Incident_vector v_incident;
	WriteFileUser fileout;
	RandomUser rnd;
	Signal sig;
	CProgressCtrl	m_Progress;

	// �Ի�������
	enum { IDD = IDD_CLUSTER_FINDING_RAW_DATA_OUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void Track(int z);
	int Det_Check(int x,int y, int z);
	afx_msg void OnBnClickedCheck1();
	bool truth_flag;
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
};
