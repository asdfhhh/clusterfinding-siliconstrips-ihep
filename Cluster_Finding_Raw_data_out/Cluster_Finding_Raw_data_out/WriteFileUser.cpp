#include "StdAfx.h"
#include "WriteFileUser.h"
#include "Constant.h"
WriteFileUser::WriteFileUser(void)
{
}

WriteFileUser::~WriteFileUser(void)
{
}

int WriteFileUser::OpenDataFile(CString name)
{
	char* pBuf = (char*)name.GetBuffer(0);
	int len = wcslen (name); //the length of "salut"
	wcstombs (pBuf,name,len); //conversion to char *	
	pBuf[len] = '\0';	 //don't forget to put the caracter of terminated string	


	data_out.open(pBuf);
	if(data_out.is_open())return 1;
	return 0;
}

int WriteFileUser::OpenTruthFile(CString name)
{
	name=_T("truth_")+name;
	char* pBuf = (char*)name.GetBuffer(0);
	int len = wcslen (name); //the length of "salut"
	wcstombs (pBuf,name,len); //conversion to char *	
	pBuf[len] = '\0';	 //don't forget to put the caracter of terminated string	
	truth_out.open(pBuf);
	if(truth_out.is_open())
	{
		truth_out<<"Charge\tX\tY\tZ\tV-X\tV-Y\tV-Z\n";
		return 1;
	}
	return 0;
}

int WriteFileUser::AddData(double* data)
{
	int ch_num=STRIP_NUM;/*sizeof(data)/sizeof(double);*/
	int tmp_data=0;
	for(int i=0;i<ch_num;i++)
	{
		if(data[i]>0)tmp_data=int(data[i]);
		else tmp_data=0;
		data_out<<tmp_data<<endl;
	}
	return 0;
}

int WriteFileUser::AddTruth(int charge,unsigned int x,unsigned int y,double vx, double vy,double vz)
{
	truth_out<<charge<<"\t"<<x<<"\t"<<y<<"\t"<<0<<"\t"<<vx<<"\t"<<vy<<"\t"<<vz<<endl;
	return 0;
}

int WriteFileUser::CloseDataFile(void)
{
	data_out.close();
	return 0;
}

int WriteFileUser::CloseTruth(void)
{
	truth_out.close();
	return 0;
}
