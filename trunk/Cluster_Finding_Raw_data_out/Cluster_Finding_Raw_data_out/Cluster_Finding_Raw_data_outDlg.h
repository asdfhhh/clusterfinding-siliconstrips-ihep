// Cluster_Finding_Raw_data_outDlg.h : ͷ�ļ�
//

#pragma once
#include "Incident_vector.h"

// CCluster_Finding_Raw_data_outDlg �Ի���
class CCluster_Finding_Raw_data_outDlg : public CDialog
{
// ����
public:
	CCluster_Finding_Raw_data_outDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CFile f_out;
	CString StrFileName;
	int m_layer;
	int m_charge;
	int m_hit;
	int p_x;
	int p_y;
	double v_x;
	double v_y;
	double v_z;

// �Ի�������
	enum { IDD = IDD_CLUSTER_FINDING_RAW_DATA_OUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	Incident_vector v_incident;

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
};
