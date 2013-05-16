// Cluster_Finding_Raw_data_outDlg.h : 头文件
//

#pragma once
#include "Incident_vector.h"
#include "WriteFileUser.h"
#include "RandomUser.h"
#include "Constant.h"
#include "Signal.h"
// CCluster_Finding_Raw_data_outDlg 对话框
class CCluster_Finding_Raw_data_outDlg : public CDialog
{
	// 构造
public:
	CCluster_Finding_Raw_data_outDlg(CWnd* pParent = NULL);	// 标准构造函数
	CString StrFileName; //文件名
	int m_layer; //探测器层数选择
	int m_charge; //粒子电荷模式选择
	int m_hit; //入射粒子数量选择
	unsigned int p_x;  //入射粒子初始位置x
	unsigned int p_y;  //入射粒子初始位置y
	unsigned int p_z;
	double v_x;//入射粒子初始方向x,y,z
	double v_y;
	double v_z;
	int particle_charge;//入射粒子电荷
	int particle_num;//入射粒子数量
	bool particle_charge_flag;//入射粒子电荷
	bool particle_num_flag;//入射粒子数量
	int loop;//循环次数
	double data_energy[STRIP_NUM];
	double data_out[DATA_NUM];

	CString loop_str;
	Incident_vector v_incident;
	WriteFileUser fileout;
	RandomUser rnd;
	Signal sig;
	CProgressCtrl	m_Progress;

	// 对话框数据
	enum { IDD = IDD_CLUSTER_FINDING_RAW_DATA_OUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

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
	void Track(int z);
	int Det_Check(int x,int y, int z);
	afx_msg void OnBnClickedCheck1();
	bool truth_flag;
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
};
