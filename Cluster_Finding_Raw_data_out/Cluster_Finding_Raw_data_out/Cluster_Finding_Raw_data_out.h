// Cluster_Finding_Raw_data_out.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCluster_Finding_Raw_data_outApp:
// �йش����ʵ�֣������ Cluster_Finding_Raw_data_out.cpp
//

class CCluster_Finding_Raw_data_outApp : public CWinApp
{
public:
	CCluster_Finding_Raw_data_outApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCluster_Finding_Raw_data_outApp theApp;