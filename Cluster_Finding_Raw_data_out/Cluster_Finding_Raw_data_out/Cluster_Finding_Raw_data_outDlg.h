// Cluster_Finding_Raw_data_outDlg.h : 头文件
//

#pragma once
#include "Incident_vector.h"

// CCluster_Finding_Raw_data_outDlg 对话框
class CCluster_Finding_Raw_data_outDlg : public CDialog
{
// 构造
public:
	CCluster_Finding_Raw_data_outDlg(CWnd* pParent = NULL);	// 标准构造函数
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

// 对话框数据
	enum { IDD = IDD_CLUSTER_FINDING_RAW_DATA_OUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	Incident_vector v_incident;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
